/*
 * jmm_cmd.c
 *
 *  Created on: 2012-6-9
 *      Author: buf1024@gmail.com
 */

#include "jmm_cmd.h"
#include "jmm_event.h"
#include "jmm_shm.h"
#include "jmm_util.h"
#include "jmm_log.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>


static jmm_list            handler    = {0};
static jmm_list            handler_wf = {0};
extern jmm_shm_wf*         shm_wf;

static int jmm_newsock_handler_wf(cJSON* js);

static jmm_list_item* jmm_list_item_alloc(const char* name, jmm_handler handler)
{
    if(!name || !handler){
        return NULL;
    }
    jmm_list_item* item = (jmm_list_item*) malloc(sizeof(jmm_list_item));
    strncpy(item->name, name, JMM_MAX_NAME - 1);
    item->handler = handler;
    item->next = NULL;
    return item;
}

int jmm_init_list(jmm_list* list)
{
    if(!list){
        return JMM_FAIL;
    }
    memset(list, 0, sizeof(jmm_list));
    return JMM_SUCCESS;
}
int jmm_uninit_list(jmm_list* list)
{
    if(!list){
        return JMM_FAIL;
    }
    jmm_list_item* item = list->item;
    while(item){
        jmm_list_item* tmp = item->next;
        free(item);
        item = tmp;
    }
    memset(list, 0, sizeof(jmm_list));
    return JMM_SUCCESS;
}
int jmm_add_handler(jmm_list* list, const char* name, jmm_handler handler)
{
    if(!list || !name || !handler){
        return JMM_FAIL;
    }
    jmm_list_item* item = list->item;
    if(item == NULL){
        list->item = jmm_list_item_alloc(name, handler);
    }else{
        jmm_list_item* item_pre = NULL;
        while(item){
            if(strcmp(item->name, name) == 0){
                return JMM_FAIL;
            }
            item_pre = item;
            item = item->next;
        }
        if(item_pre){
            item_pre->next = jmm_list_item_alloc(name, handler);
        }
    }
    list->handler_num++;
    return JMM_SUCCESS;
}
int jmm_delete_handler(jmm_list* list, const char* name)
{
    if(!list || !name){
        return JMM_FAIL;
    }
    jmm_list_item* item = list->item;
    jmm_list_item* item_pre = NULL;
    while (item) {
        if (strcmp(item->name, name) == 0) {
            break;
        }
        item_pre = item;
        item = item->next;
    }
    if(!item_pre){
        if(item){
            free(item);
        }else{
            return JMM_FAIL;
        }
    }else{
        if(item){
            item_pre->next = item->next;
            free(item);
        }else{
            return JMM_FAIL;
        }
    }
    return JMM_SUCCESS;
}
jmm_handler jmm_get_hanlder(jmm_list* list, const char* name)
{
    if(!list || !name){
        return NULL;
    }
    jmm_list_item* item = list->item;
    while (item) {
        if (strcmp(item->name, name) == 0) {
            return item->handler;
        }
        item = item->next;
    }
    return NULL;
}

int jmm_int_handler()
{
    if(jmm_init_list(&handler) == JMM_FAIL){
        return JMM_FAIL;
    }

    //TODO

    return JMM_SUCCESS;
}
int jmm_unint_handler()
{
    return jmm_uninit_list(&handler);
}

int jmm_int_handler_wf()
{
    if(jmm_init_list(&handler_wf) == JMM_FAIL){
        return JMM_FAIL;
    }
    //TODO
    jmm_add_handler(&handler_wf, JMM_CMD_NEWSOCK, jmm_newsock_handler_wf);

    return JMM_SUCCESS;
}
int jmm_unint_handler_wf()
{
    return jmm_uninit_list(&handler_wf);
}


static int jmm_newsock_handler_wf(cJSON* js)
{
    //TODO
    //event
    int i = 0;
    for (i = 0; i < shm_wf->proc_svr_num; i++) {
        jmm_shm_sock* shm_sock = jmm_shm_get_sock(shm_wf, i);
        if (shm_sock->sock_fd == 0) {
            int newsf=-1;
            jmm_recv_fd(shm_wf->mother_fd, &newsf);
            jmm_set_fd_opt(newsf, O_NONBLOCK);
            jmm_init_event_sock(i, newsf);

            shm_sock->sock_fd = newsf;
            // 子进程解父进程锁
            pthread_mutex_unlock(&(shm_wf->mutex));
            break;
        }
    }

    //TODO
    if(i == shm_wf->proc_svr_num){
        JMM_FATAL("logic error\n");
    }


    return JMM_SUCCESS;
}

char* jmm_cmd_get_string(cJSON* json)
{
    if(!json){
        return NULL;
    }
    char* json_str = cJSON_PrintUnformatted(json);
    if(!json_str){
        return NULL;
    }
    int json_len = strlen(json_str) + 1;
    char* cmd_str = malloc(sizeof(int) + json_len*sizeof(char));
    memcpy(cmd_str, &json_len, sizeof(int));
    memcpy(cmd_str+sizeof(int), json_str, json_len);
    free(json_str);
    return cmd_str;
}
int jmm_cmd_get_string_len(char* cmd_str)
{
    if(!cmd_str){
        return 0;
    }
    return sizeof(int) + strlen(cmd_str + sizeof(int)) + 1;
}


int jmm_cmd_dispatch_wf(const char* cmd_str)
{
    if(!cmd_str){
        return JMM_FAIL;
    }
    cJSON* js = cJSON_Parse(cmd_str);
    if(!js){
        return JMM_FAIL;
    }
    cJSON* js_cmd = cJSON_GetObjectItem(js, JMM_CMD_REQ);
    if(!js_cmd || js_cmd->type != cJSON_String){
        cJSON_Delete(js);
        return JMM_FAIL;
    }
    jmm_handler handler = jmm_get_hanlder(&handler_wf, js_cmd->valuestring);
    if(handler == NULL){
        cJSON_Delete(js);
        return JMM_FAIL;
    }
    if(handler(js) != JMM_SUCCESS){
        cJSON_Delete(js);
        return JMM_FAIL;
    }
    cJSON_Delete(js);
    return JMM_SUCCESS;
}
