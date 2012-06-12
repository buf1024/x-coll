/*
 * jmm_proc.c
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#include "jmm_cmmhdr.h"
#include "jmm_proc.h"
#include "jmm_shm.h"
#include "jmm_event.h"
#include "jmm_cmd.h"
#include "jmm_util.h"
#include "jmm_log.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <event2/event.h>
#include <event2/bufferevent.h>

extern jmm_shm*                  shm;
//extern jmm_shm_wf*            shm_wf;
extern jmm_conf                 conf;
extern jmm_event               event;
//extern jmm_event_wf         event_wf;

int jmm_find_free_wf()
{
    if(shm == NULL){
        return JMM_FAIL;
    }

    int i = 0;
    int j = 0;
    for(i=0; i<shm->proc_num; i++){

        jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf.proc_svr_num);
        if(wf->pid == 0){
            // 当前这个进程挂了，无视之
            continue;
        }

        if(pthread_mutex_trylock(&(wf->mutex)) == EBUSY){
            if (i == shm->proc_num - 1) {
                // 顽强的尝试
                JMM_INFO("resource is lock, trying later\n");
                i = 0;
                continue;
            }
        }
        // 获得锁
        for(j=0; j<wf->proc_svr_num; j++){
            /*jmm_shm_sock* sock = (jmm_shm_sock*)((char*)&wf->shm_sock + j*jmm_shm_sock_size());*/
            jmm_shm_sock* sock = jmm_shm_get_sock(wf, j);
            //if(!sock->status){
            if(sock->sock_fd == 0){
                // 让子程序解锁
                //pthread_mutex_unlock(&(wf->mutex));
                return i;
            }
        }
        pthread_mutex_unlock(&(wf->mutex));
    }
    return JMM_FAIL;
}
int jmm_assign_wf(int wf_id, int sock_fd, const char* ip, int port)
{
    if(shm == NULL || ip == NULL){
        return JMM_FAIL;
    }
    jmm_shm_wf* wf = jmm_shm_get_wf(shm, wf_id, conf.proc_svr_num);
#ifdef DEBUG
    jmm_trace_shm_wf(wf, 4);
#endif
    // TODO
    cJSON* js = cJSON_CreateObject();
    cJSON* js_arg = cJSON_CreateObject();

    cJSON_AddStringToObject(js, JMM_CMD_REQ, JMM_CMD_NEWSOCK);
    cJSON_AddStringToObject(js_arg, JMM_CMD_NEWSOCK_ARG_IP, ip);
    cJSON_AddNumberToObject(js_arg, JMM_CMD_NEWSOCK_ARG_PORT, port);
    cJSON_AddItemToObject(js, JMM_CMD_REQ_ARG, js_arg);

    // TODO
    char* cmd_str = jmm_cmd_get_string(js);
    if(cmd_str == NULL){
        return JMM_FAIL;
    }

    jmm_send_fd(wf->father_fd, sock_fd);

    if(bufferevent_write(event.cmm[wf_id], cmd_str, jmm_cmd_get_string_len(cmd_str)) < 0){
        JMM_ERROR("bufferevent_write error:%s\n", cmd_str);
    }
    free(cmd_str);
    cJSON_Delete(js);

    return JMM_SUCCESS;
}


int jmm_init_proc(jmm_conf* conf)
{
    if(conf == NULL){
        return JMM_FAIL;
    }
    int ret = JMM_SUCCESS;
    pid_t pid;
    int i = 0;
    for (i = 0; i < conf->proc_num; i++) {
        jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf->proc_svr_num);

        // 传递控制信息
        int sf[2] = { 0 };
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sf) != 0) {
            ret = JMM_FAIL;
            break;
        }
        wf->boy_fd = sf[0];
        wf->girl_fd = sf[1];

        // 传递文件描述符
        memset(sf, 0, sizeof(sf));
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sf) != 0) {
            ret = JMM_FAIL;
            break;
        }
        wf->father_fd = sf[0];
        wf->mother_fd = sf[1];

        if((pid = fork()) == 0){
            //TODO
            wf->pid = getpid();
            exit(jmm_proc_wf(i));
        }else if(pid > 0){
            //TODO
            //JMM_INFO("fork program i=%d\n", i);
        }else{
            ret = JMM_FAIL;
            break;
        }
    }
    if(JMM_FAIL == ret){
        //TODO
        JMM_FATAL("fail to fork program.\n");
        JMM_FATAL("you should adjust system configuration. proc_num: %d, proc_svr_num: %d\n",
                conf->proc_num, conf->proc_svr_num);
    }
    return ret;
}

int jmm_uninit_proc()
{

    return JMM_SUCCESS;
}

int jmm_proc_clear_env_wf()
{
    if(jmm_uninit_event() == JMM_FAIL){
        return JMM_FAIL;
    }
    return JMM_SUCCESS;
}

int jmm_proc_wf(int wf_id)
{
    if(jmm_proc_clear_env_wf() == JMM_FAIL){
        fprintf(stderr, "fail to cleanup process environment!\n");
        return JMM_FAIL;
    }
    struct event_base* base = NULL;
    base = event_base_new();
    if(!base){
        fprintf(stderr, "fail to call event_base_new\n");
        return JMM_FAIL;
    }
    // log
    if(jmm_init_log_wf() == JMM_FAIL){
        fprintf(stderr, "fail to init log!\n");
        event_base_free(base);
        return JMM_FAIL;
    }
    JMM_INFO("child(%d) logger is ready!\n", wf_id);
    // shm
    if(jmm_init_shm_wf(wf_id, conf.proc_svr_num) == JMM_FAIL){
        jmm_uninit_log_wf();
        event_base_free(base);
        return JMM_FAIL;
    }
    JMM_INFO("child(%d) share memory is ready!\n", wf_id);
    // cmd handler
    if (jmm_int_handler_wf() == JMM_FAIL) {
        jmm_uninit_shm_wf();
        jmm_uninit_log_wf();
        event_base_free(base);
        return JMM_FAIL;
    }
    JMM_INFO("child(%d) command handler is ready!\n", wf_id);
    // event
    if(jmm_init_event_wf(base) == JMM_FAIL){
        jmm_unint_handler_wf();
        jmm_uninit_shm_wf();
        jmm_uninit_log_wf();
        event_base_free(base);
        return JMM_FAIL;
    }
    JMM_INFO("child(%d) event is ready!\n", wf_id);
    JMM_INFO("child(%d) entering event loop...\n", wf_id);
    event_base_dispatch(base);

    JMM_INFO("free resource, exit\n");
    jmm_uninit_event_wf();
    jmm_unint_handler_wf();
    jmm_uninit_shm_wf();
    jmm_uninit_log_wf();
    event_base_free(base);

    return JMM_SUCCESS;
}
