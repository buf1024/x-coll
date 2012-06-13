/*
 * jcc_event.c
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */

#include "jcc_cmmhdr.h"
#include "jcc_event.h"
#include "jcc_proc.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#define JCC_QUIT_CMD "exit"

static jcc_event event;
static int cmm_fd[2] = {0};

// 控制进程事件回调
static void jcc_ctrl_c_cb(evutil_socket_t fd, short what, void* ctx);
static void jcc_usr1_cb(evutil_socket_t fd, short what, void* ctx);

// socket 事件回调
static void jcc_sock_read_cb(struct bufferevent*, void *);
static void jcc_sock_write_cb(struct bufferevent*, void*);
static void jcc_sock_event_cb(struct bufferevent*, short, void*);

// 和子线程通信, 因为libevent不是线程安全的
static void jcc_cmm_read_cb(struct bufferevent*, void*);
static void jcc_cmm_event_cb(struct bufferevent*, short, void*);


int jcc_push_msg(const char* msg, int len)
{
    if(msg == NULL){
        return JCC_FAIL;
    }
    if(bufferevent_write(event.sock, msg, len) != 0){
        return JCC_FAIL;
    }
    return JCC_SUCCESS;
}

int jcc_quit_event_loop()
{
    if(write(cmm_fd[1], JCC_QUIT_CMD, strlen(JCC_QUIT_CMD)) > 0){
        return JCC_SUCCESS;
    }
    return JCC_FAIL;
}

int jcc_init_event(struct event_base* base, struct sockaddr* addr, int len)
{
    if (base && addr) {
        event.base = base;
        // SIGTERM
        event.term =
                evsignal_new(base, SIGTERM, jcc_ctrl_c_cb, (void *)base);
        if (!event.term || event_add(event.term, NULL) < 0) {
            return JCC_FAIL;
        }
        // CTRL-C
        event.ctrl_c = evsignal_new(base, SIGINT, jcc_ctrl_c_cb, (void *)base);
        if (!event.ctrl_c || event_add(event.ctrl_c, NULL) < 0) {
            return JCC_FAIL;
        }
        // USR1
        event.usr1 = evsignal_new(base, SIGUSR1, jcc_usr1_cb, (void *)base);
        if (!event.usr1 || event_add(event.usr1, NULL) < 0) {
            return JCC_FAIL;
        }

        // cmm
        if(socketpair(AF_UNIX, SOCK_STREAM, 0, cmm_fd) != 0){
            return JCC_FAIL;
        }
        event.cmm = bufferevent_socket_new(event.base, cmm_fd[0],
                BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(event.cmm, jcc_cmm_read_cb, NULL, jcc_cmm_event_cb,
                event.base);
        bufferevent_disable(event.cmm, EV_WRITE);
        bufferevent_enable(event.cmm, EV_READ);

        //sock
        event.sock = bufferevent_socket_new(event.base, -1,
                BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(event.sock, jcc_sock_read_cb, jcc_sock_write_cb,
                jcc_sock_event_cb, event.base);
        bufferevent_enable(event.sock, EV_WRITE);
        bufferevent_enable(event.sock, EV_READ);

        if(bufferevent_socket_connect (event.sock, addr, len) == -1){
            return JCC_FAIL;
        }

        return JCC_SUCCESS;
    }
    return JCC_FAIL;
}
int jcc_uninit_event()
{
    if(event.cmm){
        bufferevent_free(event.cmm);
        event.cmm = NULL;
        close(cmm_fd[0]);
        close(cmm_fd[1]);
    }
    if (event.sock) {
        bufferevent_free(event.sock);
        event.sock = NULL;
    }
    if(event.ctrl_c){
        event_free(event.ctrl_c);
        event.ctrl_c = NULL;
    }
    if(event.usr1){
        event_free(event.usr1);
        event.usr1 = NULL;
    }
    if(event.term){
        event_free(event.term);
        event.term = NULL;
    }

    return JCC_SUCCESS;
}


// 控制进程事件回调
static void jcc_ctrl_c_cb(evutil_socket_t fd, short what, void* ctx)
{
    printf("jcc_ctrl_c_cb\n");
    struct event_base* base = (struct event_base*)ctx;

    event_base_loopbreak(base);
}
static void jcc_usr1_cb(evutil_socket_t fd, short what, void* ctx)
{
    printf("jcc_ctrl_c_cb\n");
    const char* msg = "I am jcc.";
    bufferevent_write(event.sock, msg, strlen(msg));
}

// 子进程 socket 事件回调
static void jcc_sock_read_cb(struct bufferevent* bev, void* ctx)
{
    //static char buf[JCC_MAX_RECV_BUF_LEN] = "";
    //static int buf_len = 0;
    struct evbuffer *input = bufferevent_get_input(bev);
    if(evbuffer_get_length(input) > 0){
        int len = evbuffer_get_length(input);
        char data[1024] = "";
        evbuffer_remove(input, data, len);
        printf("get:%d, data:%s\n", len, data);
        jcc_add_buffer(data, len);
        jcc_unlock_buffer();
        /*const char* msg = "who are you?";
        bufferevent_write(bev, msg, strlen(msg))*/;

    }
}
static void jcc_sock_write_cb(struct bufferevent* bev, void* ctx)
{
    printf("jcc_sock_write_cb\n");
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        printf("flushed answer\n");
        //bufferevent_free(bev);
    }
}
static void jcc_sock_event_cb(struct bufferevent* bev, short what, void* ctx)
{
    if (what & BEV_EVENT_EOF) {
        fprintf(stdout, "connection closed.\n");
    } else if (what & BEV_EVENT_ERROR) {
        fprintf(stderr, "got an error on the connection: %s\n", strerror(errno));
    } else if (what & BEV_EVENT_CONNECTED){
        fprintf(stdout, "connection establish!\n");
    }
    if((what & BEV_EVENT_EOF) || (what & BEV_EVENT_ERROR)){
        struct event_base* base = (struct event_base*)ctx;
        event_base_loopbreak(base);
    }
}

static void jcc_cmm_read_cb(struct bufferevent* bev, void*ctx)
{
    struct evbuffer *input = bufferevent_get_input(bev);
    if(evbuffer_get_length(input) > 0){
        printf("quit\n");
        struct event_base* base = (struct event_base*)ctx;

        event_base_loopbreak(base);
    }

}
static void jcc_cmm_event_cb(struct bufferevent* bev, short what, void* ctx)
{
    fprintf(stdout, "unexpect event happen\n");
    if((what & BEV_EVENT_EOF) || (what & BEV_EVENT_ERROR)){
        struct event_base* base = (struct event_base*)ctx;
        event_base_loopbreak(base);
    }
}
