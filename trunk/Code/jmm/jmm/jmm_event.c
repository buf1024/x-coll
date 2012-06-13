/*
 * jmm_event.c
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#include "jmm_cmmhdr.h"
#include "jmm_event.h"
#include "jmm_conf.h"
#include "jmm_proc.h"
#include "jmm_shm.h"
#include "jmm_cmd.h"
#include "jmm_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

jmm_event                    event = {0};
jmm_event_wf              event_wf = {0};
extern jmm_conf               conf;
extern jmm_shm*                shm;
extern jmm_shm_wf*          shm_wf;

// 控制进程事件回调
static void jmm_ctrl_c_cb(evutil_socket_t fd, short what, void* ctx);
static void jmm_usr1_cb(evutil_socket_t fd, short what, void* ctx);
static void jmm_child_cb(evutil_socket_t fd, short what, void* ctx);
static void jmm_listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
    struct sockaddr* sa, int socklen, void* user_data);

// 子进程事件回调
static void jmm_ctrl_c_wf_cb(evutil_socket_t fd, short what, void* ctx);
static void jmm_usr1_wf_cb(evutil_socket_t fd, short what, void* ctx);

// 控制进程和子进程通信事件回调
static void jmm_cmm_read_cb(struct bufferevent*, void *);
static void jmm_cmm_write_cb(struct bufferevent*, void*);
static void jmm_cmm_event_cb(struct bufferevent*, short, void*);

// 子进程和控制进程通信事件回调
static void jmm_cmm_read_wf_cb(struct bufferevent*, void *);
static void jmm_cmm_write_wf_cb(struct bufferevent*, void*);
static void jmm_cmm_event_wf_cb(struct bufferevent*, short, void*);

// 子进程 socket 事件回调
static void jmm_sock_read_wf_cb(struct bufferevent*, void *);
static void jmm_sock_write_wf_cb(struct bufferevent*, void*);
static void jmm_sock_event_wf_cb(struct bufferevent*, short, void*);


int jmm_init_event(struct event_base* base)
{
    if (base) {
        event.base = base;
        // SIGTERM
        event.term = evsignal_new(base, SIGTERM, jmm_ctrl_c_cb, (void *)base);
        if (!event.term || event_add(event.term, NULL) < 0) {
            return JMM_FAIL;
        }
        // CTRL-C
        event.ctrl_c = evsignal_new(base, SIGINT, jmm_ctrl_c_cb, (void *)base);
        if (!event.ctrl_c || event_add(event.ctrl_c, NULL) < 0) {
            return JMM_FAIL;
        }
        // USR1
        event.usr1 = evsignal_new(base, SIGUSR1, jmm_usr1_cb, (void *)base);
        if (!event.usr1 || event_add(event.usr1, NULL) < 0) {
            return JMM_FAIL;
        }
        // CHLD
        event.child = evsignal_new(base, SIGCHLD, jmm_child_cb, (void *)base);
        if (!event.child || event_add(event.child, NULL) < 0) {
            return JMM_FAIL;
        }

        //CMM 控制事件
        event.cmm_num = shm->proc_num;
        event.cmm = (struct bufferevent**)malloc(sizeof(struct bufferevent*)*event.cmm_num);
        int i = 0;
        for (i = 0; i < shm->proc_num; i++) {
            jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf.proc_svr_num);
            event.cmm[i] = bufferevent_socket_new(base, wf->boy_fd, BEV_OPT_CLOSE_ON_FREE);
            bufferevent_setcb(event.cmm[i], jmm_cmm_read_cb,
                    jmm_cmm_write_cb, jmm_cmm_event_cb, (void*)i);
            bufferevent_enable(event.cmm[i], EV_WRITE);
            bufferevent_enable(event.cmm[i], EV_READ);
        }


        // 监听接口
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_port = htons(conf.net_port);

        event.listener = evconnlistener_new_bind(base, jmm_listener_cb, (void *)base,
            LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE|LEV_OPT_CLOSE_ON_EXEC,
            conf.net_backlog, (struct sockaddr*)&sin, sizeof(sin));

        if (!event.listener) {
            return JMM_FAIL;
        }
        return JMM_SUCCESS;
    }
    return JMM_FAIL;
}
int jmm_uninit_event()
{
    if(event.cmm){
        int i = 0;
        for(i=0; i<event.cmm_num; i++){
            bufferevent_free(event.cmm[i]);
        }
        free(event.cmm);
        event.cmm = NULL;
        event.cmm_num = 0;
    }
    if(event.listener){
        evconnlistener_free(event.listener);
        event.listener = NULL;
    }
    if(event.child){
        event_free(event.child);
        event.child = NULL;
    }
    if(event.ctrl_c){
        event_free(event.ctrl_c);
        event.ctrl_c = NULL;
    }
    if(event.usr1){
        event_free(event.usr1);
        event.usr1 = NULL;
    }
    if (event.term) {
        event_free(event.term);
        event.term = NULL;
    }

    return JMM_SUCCESS;
}

int jmm_init_event_wf(struct event_base* base)
{
    if (base) {
        event_wf.base = base;
        // SIGTERM
        event_wf.term =
                evsignal_new(base, SIGTERM, jmm_ctrl_c_wf_cb, (void *)base);
        if (!event_wf.term || event_add(event_wf.term, NULL) < 0) {
            return JMM_FAIL;
        }
        // CTRL-C
        event_wf.ctrl_c = evsignal_new(base, SIGINT, jmm_ctrl_c_wf_cb, (void *)base);
        if (!event_wf.ctrl_c || event_add(event_wf.ctrl_c, NULL) < 0) {
            return JMM_FAIL;
        }
        // USR1
        event_wf.usr1 = evsignal_new(base, SIGUSR1, jmm_usr1_wf_cb, (void *)base);
        if (!event_wf.usr1 || event_add(event_wf.usr1, NULL) < 0) {
            return JMM_FAIL;
        }

        // CMM
        event_wf.cmm = bufferevent_socket_new(base, shm_wf->girl_fd,
                BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(event_wf.cmm, jmm_cmm_read_wf_cb, jmm_cmm_write_wf_cb,
                jmm_cmm_event_wf_cb, NULL);
        bufferevent_enable(event_wf.cmm, EV_WRITE);
        bufferevent_enable(event_wf.cmm, EV_READ);

        //sock
        event_wf.sock_num = conf.proc_svr_num;
        event_wf.sock = (struct bufferevent**)malloc(sizeof(struct bufferevent*)*event_wf.sock_num);
        memset(event_wf.sock, 0, sizeof(struct bufferevent*)*event_wf.sock_num);

        return JMM_SUCCESS;
    }
    return JMM_FAIL;
}
int jmm_uninit_event_wf()
{
    if (event_wf.sock) {
        int i = 0;
        for (i = 0; i < event_wf.sock_num; i++) {
            if (event_wf.sock[i] != NULL) {
                bufferevent_free(event_wf.sock[i]);
                event_wf.sock[i] = NULL;
            }
        }
        free(event_wf.sock);
        event_wf.sock = NULL;
        event_wf.sock_num = 0;
    }

    if(event_wf.cmm){
        bufferevent_free(event_wf.cmm);
        event.cmm = NULL;
    }
    if(event_wf.ctrl_c){
        event_free(event_wf.ctrl_c);
        event_wf.ctrl_c = NULL;
    }
    if(event.usr1){
        event_free(event_wf.usr1);
        event_wf.usr1 = NULL;
    }
    if(event.term){
        event_free(event_wf.term);
        event_wf.term = NULL;
    }

    return JMM_SUCCESS;
}

int jmm_init_event_sock(int idx, int sfd)
{
    if(event_wf.sock[idx] != NULL){
        return JMM_FAIL;
    }
    event_wf.sock[idx] = bufferevent_socket_new(event_wf.base, sfd,
            BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(event_wf.sock[idx], jmm_sock_read_wf_cb, jmm_sock_write_wf_cb,
            jmm_sock_event_wf_cb, (void*)idx);
    bufferevent_enable(event_wf.sock[idx], EV_WRITE);
    bufferevent_enable(event_wf.sock[idx], EV_READ);

    return JMM_SUCCESS;
}

// 控制进程CTRL-C
static void jmm_ctrl_c_cb(evutil_socket_t fd, short what, void* ctx)
{
    JMM_INFO("catch terminate signal.\n");

    struct event_base *base = ctx;
    if(shm){
        int i = 0;
        for(i=0; i<shm->proc_num; i++){
            // 结束子进程
            jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf.proc_svr_num);
            if (wf->pid != 0) {
                kill(wf->pid, SIGINT);
                waitpid(wf->pid, NULL, 0);
            }
        }
    }

    event_base_loopexit(base, NULL);
}
// 控制进程USR1
static void jmm_usr1_cb(evutil_socket_t fd, short what, void* ctx)
{
    JMM_INFO("catch usr1 signal.\n");
}
// 控制进程CHD
static void jmm_child_cb(evutil_socket_t fd, short what, void* ctx)
{
    // 除非主进程要子进程断，否则子进程不应该自己停止
    // 目前只将池减少一下
    JMM_INFO("catch child terminate signal.\n");
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0){
        JMM_INFO("child process exit, pid=%d\n", pid);
        // pid == 0, 表示不可用
        int i = 0;
        for (i = 0; i < shm->proc_num; i++) {
            jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf.proc_svr_num);
            if(wf->pid == pid){
                wf->pid = 0;
                break;
            }
        }
    }
}
// 控制进程监听网络
static void jmm_listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
    char ip_addr[JMM_MAX_ADDR] = "";
    int port = 0;
    if(socklen == sizeof(struct sockaddr_in)){
        struct sockaddr_in* sa_in = (struct sockaddr_in*)sa;
        inet_ntop(AF_INET, &(sa_in->sin_addr), ip_addr, sizeof(ip_addr));
        port = sa_in->sin_port;
        JMM_INFO("get connection: (%s, %d)\n", ip_addr, sa_in->sin_port);
    }else{
        struct sockaddr_in6* sa_in6 = (struct sockaddr_in6*)sa;
        inet_ntop(AF_INET6, &(sa_in6->sin6_addr), ip_addr, sizeof(ip_addr));
        port = sa_in6->sin6_port;
        JMM_INFO("get connection: (%s, %d)\n", ip_addr, sa_in6->sin6_port);
    }

    // 寻找可用的子进程
    int wf_id = jmm_find_free_wf();
    if(wf_id == JMM_FAIL){
        JMM_INFO("no available resource!\n");
    } else {
        if (jmm_assign_wf(wf_id, fd, ip_addr, port) == JMM_FAIL) {
            JMM_INFO("fail to assign program!\n");
        }
    }
    //如果不成功指派则关闭，但如果如果成功指派也要关闭，因为已经飞到子进程中了
    close(fd);
}

static void jmm_ctrl_c_wf_cb(evutil_socket_t fd, short what, void* ctx)
{
    struct event_base *base = ctx;

    printf("jmm_ctrl_c_wf_cb.\n");

    event_base_loopexit(base, NULL);
}
static void jmm_usr1_wf_cb(evutil_socket_t fd, short what, void* ctx)
{
    printf("jmm_usr1_wf_cb.\n");
}

static void jmm_cmm_read_cb(struct bufferevent* bev, void* ctx)
{
    //printf("jmm_cmm_read_cb.\n");
}
static void jmm_cmm_write_cb(struct bufferevent* bev, void* ctx)
{
   // int idx = (int)(ctx);
    //printf("jmm_cmm_write_cb(%d).\n", idx);
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        //printf("flushed answer(%d)\n", idx);
        //bufferevent_free(bev);
    }
}
static void jmm_cmm_event_cb(struct bufferevent* bev, short what, void* ctx)
{
    //printf("jmm_cmm_write_cb.\n");
}

static void jmm_cmm_read_wf_cb(struct bufferevent* bev, void* ctx)
{
    //buffer not good
    static int  js_len                      = 0;
    static int  len_flag                    = 0;
    static char js_data[JMM_MAX_CMD_STRING] = "";
    static int  data_flag                   = 0;

    int actual = 0;

    struct evbuffer *input = bufferevent_get_input(bev);
    while (evbuffer_get_length(input) != 0) {

        if(data_flag != 0){
            actual = evbuffer_remove(input, js_data + data_flag, js_len - data_flag);
            if (actual != js_len - data_flag) {
                data_flag += actual;
                break;
            }
            data_flag = 0;
            //printf("receive(%d):%s\n", js_len, js_data);
            if(jmm_cmd_dispatch_wf(js_data) != JMM_SUCCESS){
                JMM_ERROR("fail to dispatch cmd\n");
            }
        }

        actual = evbuffer_remove(input, ((char*)&js_len)+len_flag, sizeof(int)-len_flag);
        if(actual != sizeof(int)-len_flag){
            len_flag += actual;
            break;
        }
        len_flag = 0;

        actual = evbuffer_remove(input, js_data + data_flag, js_len - data_flag);
        if (actual != js_len - len_flag) {
            data_flag += actual;
            break;
        }
        data_flag = 0;
        //printf("receive(%d):%s\n", js_len, js_data);
        if (jmm_cmd_dispatch_wf(js_data) != JMM_SUCCESS) {
            JMM_ERROR("fail to dispatch cmd\n");
        }
    }

}
static void jmm_cmm_write_wf_cb(struct bufferevent* bev, void* ctx)
{
    //printf("jmm_cmm_write_wf_cb.\n");
}
static void jmm_cmm_event_wf_cb(struct bufferevent* bev, short what, void* ctx)
{
    //printf("jmm_cmm_event_wf_cb.\n");
}

static void jmm_sock_read_wf_cb(struct bufferevent* bev, void* ctx)
{
    struct evbuffer *input = bufferevent_get_input(bev);

    if(evbuffer_get_length(input) >0){
        int len = evbuffer_get_length(input);

        char data[1024] = "";
        evbuffer_remove(input, data, len);
        printf("get:%d, data:%s\n", len, data);
        const char* msg = "who are you?";
        bufferevent_write(bev, msg, strlen(msg));

    }

}
static void jmm_sock_write_wf_cb(struct bufferevent* bev, void* ctx)
{
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        //printf("flushed answer(%d)\n", idx);
        //bufferevent_free(bev);
    }
}
static void jmm_sock_event_wf_cb(struct bufferevent* bev, short what, void* ctx)
{
    if (what & BEV_EVENT_EOF) {
        JMM_INFO("connection closed.\n");
    } else if (what & BEV_EVENT_ERROR) {
        JMM_ERROR("got an error on the connection: %s\n", strerror(errno));
    }
    int idx = (int)(ctx);
    pthread_mutex_lock(&(shm_wf->mutex));
    bufferevent_free(event_wf.sock[idx]);
    event_wf.sock[idx] = NULL;
    jmm_shm_sock* sock = jmm_shm_get_sock(shm_wf, idx);
    sock->sock_fd = 0;
    pthread_mutex_unlock(&(shm_wf->mutex));
}
