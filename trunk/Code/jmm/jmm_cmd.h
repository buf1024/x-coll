/*
 * jmm_cmd.h
 *
 *  Created on: 2012-6-9
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_CMD_H__
#define __48SLOTS_JMM_CMD_H__

#include "jmm_cmmhdr.h"
#include <sys/types.h>
#include "cJSON.h"

#define JMM_CMD_REQ                        "req"
#define JMM_CMD_RSP                        "rsp"
#define JMM_CMD_REQ_ARG                    "arg"
#define JMM_CMD_RSP_RES                    "res"

// TODO
//{"req":"newsock", "arg":{"ip":"192.168.1.101", "port":9999}}
#define JMM_CMD_NEWSOCK                    "newsock"
#define JMM_CMD_NEWSOCK_ARG_IP             "ip"
#define JMM_CMD_NEWSOCK_ARG_PORT           "port"

typedef int (*jmm_handler)(cJSON* args);

typedef struct jmm_list_item
{
    char name[JMM_MAX_NAME];
    jmm_handler handler;
    struct jmm_list_item* next;
}jmm_list_item;

typedef struct jmm_list
{
    int handler_num;
    jmm_list_item* item;
}jmm_list;

int jmm_init_list(jmm_list* list);
int jmm_uninit_list(jmm_list* list);
int jmm_add_handler(jmm_list* list, const char* name, jmm_handler handler);
int jmm_delete_handler(jmm_list* list, const char* name);
jmm_handler jmm_get_hanlder(jmm_list* list, const char* name);

int jmm_int_handler();
int jmm_unint_handler();

int jmm_int_handler_wf();
int jmm_unint_handler_wf();

char* jmm_cmd_get_string(cJSON* json);
int jmm_cmd_get_string_len(char* cmd_str);

int jmm_cmd_dispatch_wf(const char* cmd_str);

#endif /* __48SLOTS_JMM_CMD_H__ */
