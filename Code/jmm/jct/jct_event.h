/*
 * jct_event.h
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JCT_EVENT_H__
#define __48SLOTS_JCT_EVENT_H__

#include <sys/socket.h>

// 进程事件
typedef struct jct_event
{
    struct event_base* base;
    struct event* term;
    struct event* usr1;
    struct event* ctrl_c;
    struct bufferevent* cmm;
    struct bufferevent* sock;
}jct_event;

int jct_init_event(struct event_base* base, struct sockaddr* addr, int len);
int jct_uninit_event();

int jct_push_msg(const char* msg, int len);
int jct_quit_event_loop();

#endif /* __48SLOTS_JCT_EVENT_H__ */
