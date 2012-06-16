/*
 * jmm_event.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_EVENT_H__
#define __48SLOTS_JMM_EVENT_H__

// 控制进程事件
typedef struct jmm_event
{
    struct event_base* base;
    struct event* term;
    struct event* usr1;
    struct event* ctrl_c;
    struct event* child;

    struct evconnlistener* listener;

}jmm_event;

// 子进程事件
typedef struct jmm_event_wf
{
    struct event_base* base;
    struct event* term;
    struct event* usr1;
    struct event* ctrl_c;

    struct event* cmm;   // 父进程通信

    int sock_num;
    struct bufferevent** sock; // socket事件

}jmm_event_wf;

typedef struct jmm_event_wf_thread
{
    int thr_num;
    struct event** cmm_thr; // 与线程通信
};

// 控制进程事件
int jmm_init_event(struct event_base* base);
int jmm_uninit_event();

// 子进程事件
int jmm_init_event_wf(struct event_base* base);
int jmm_uninit_event_wf();

// 子进程socket事件
int jmm_init_event_sock(int idx, int sfd);

// 线程事件
int jmm_init_event_wf_thread(struct event_base* base);
int jmm_uninit_event_wf_thread();


#endif /* __48SLOTS_JMM_EVENT_H__ */
