/*
 * jmm_event.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_EVENT_H__
#define __48SLOTS_JMM_EVENT_H__

typedef struct jmm_event
{
    struct event_base* base;
    struct event* term;
    struct event* usr1;
    struct event* ctrl_c;
    struct event* child;

    struct evconnlistener* listener;

    int cmm_num;
    struct bufferevent** cmm;

}jmm_event;

typedef struct jmm_event_wf
{
    struct event_base* base;
    struct event* term;
    struct event* usr1;
    struct event* ctrl_c;

    struct bufferevent* cmm;
}jmm_event_wf;

int jmm_init_event(struct event_base* base);
int jmm_uninit_event();

int jmm_init_event_wf(struct event_base* base);
int jmm_uninit_event_wf();

#endif /* __48SLOTS_JMM_EVENT_H__ */
