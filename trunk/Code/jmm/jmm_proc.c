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
extern jmm_shm_wf*            shm_wf;
extern jmm_conf                 conf;
extern jmm_event               event;
extern jmm_event_wf         event_wf;

int jmm_find_free_wf()
{
    if(shm == NULL){
        return JMM_FAIL;
    }
    int lock = 0;
    int i = 0;
    int j = 0;
    for(i=0; i<shm->proc_num; i++){
        if(lock > 0 && i == shm->proc_num - 1){
            // 顽强的尝试
            i = 0;
            lock = 0;
            continue;
        }
        /*jmm_shm_wf* wf = (jmm_shm_wf*)((char*)&(shm->shm_wf) +
                        i*jmm_shm_wf_size(conf.proc_svr_num));*/
        jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf.proc_svr_num);

        if(pthread_mutex_trylock(&(wf->mutex)) == EBUSY){
            lock++;
            continue;
        }
        // 获得锁
        if(lock > 0) lock--;

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
int jmm_assign_wf(int wf_id, int sock_fd)
{
    if(shm == NULL){
        return JMM_FAIL;
    }
    printf("wf_id:%d\n", wf_id);
    jmm_shm_wf* wf = jmm_shm_get_wf(shm, wf_id, conf.proc_svr_num);
#ifdef DEBUG
    jmm_trace_shm_wf(wf, 4);
#endif
    // todo
    cJSON* js = cJSON_CreateObject();
    cJSON* js_arg = cJSON_CreateObject();

    cJSON_AddStringToObject(js, JMM_CMD_REQ, JMM_CMD_NEWSOCK);
    cJSON_AddNumberToObject(js_arg, JMM_CMD_NEWSOCK_SOCK, sock_fd);
    cJSON_AddItemToObject(js, JMM_CMD_REQ_ARG, js_arg);

    char* cmd_str = jmm_cmd_get_string(js);

    int nRet = jmm_send_fd(wf->father_fd, sock_fd);
    printf("sendfd:%d, event:%d, father:%d\n", nRet, (int)(event.cmm[wf_id]), wf->father_fd);
    //write
    //printf("wf_id: %d, write:%d, %s\n", wf_id, *(int*)cmd_str, cmd_str+sizeof(int));
    if(bufferevent_write(event.cmm[wf_id], cmd_str, jmm_cmd_get_string_len(cmd_str)) < 0){
        printf("bufferevent_write error\n");
    }
    //close(sock_fd);
    free(cmd_str);

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
        /*jmm_shm_wf* wf = (jmm_shm_wf*)((char*)&(shm->shm_wf) +
                i*jmm_shm_wf_size(conf->proc_svr_num));*/

        jmm_shm_wf* wf = jmm_shm_get_wf(shm, i, conf->proc_svr_num);

        int sf[2] = { 0 };
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sf) != 0) {
            ret = JMM_FAIL;
            break;
        }
        wf->boy_fd = sf[0];
        wf->girl_fd = sf[1];

        memset(sf, 0, sizeof(sf));
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sf) != 0) {
            ret = JMM_FAIL;
            break;
        }
        wf->father_fd = sf[0];
        wf->mother_fd = sf[1];
        //printf("father=%d, mother=%d\n", wf->father_fd, wf->mother_fd);

/*        int flags;
        if ((flags = fcntl(wf->boy_fd, F_GETFL, 0)) < 0 ||
            fcntl(wf->boy_fd, F_SETFL, flags | O_NONBLOCK) < 0) {
            perror("setting O_NONBLOCK");
            ret = JMM_FAIL;
            break;
        }

        if ((flags = fcntl(wf->girl_fd, F_GETFL, 0)) < 0
                || fcntl(wf->girl_fd, F_SETFL, flags | O_NONBLOCK) < 0) {
            perror("setting O_NONBLOCK");
            ret = JMM_FAIL;
            break;
        }*/

        if((pid = fork()) == 0){
            //TODO
            wf->pid = getpid();
            exit(jmm_proc_wf(i));
        }else if(pid > 0){
            //TODO
            //JMM_INFO("fork program i=%d\n", i);
        }else{
            //TODO
            JMM_ERROR("fail to fork program\n");
            ret = JMM_FAIL;
            break;
        }
    }
    if(JMM_FAIL == ret){
        //TODO
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
        return JMM_FAIL;
    }
    struct event_base* base = NULL;
    base = event_base_new();
    if(!base){
        JMM_FATAL("fail to call event_base_new\n");
        return JMM_FAIL;
    }
    // log
    // shm
    if(jmm_init_shm_wf(wf_id, conf.proc_svr_num) == JMM_FAIL){
        event_base_free(base);
        return JMM_FAIL;
    }
    // cmd handler
    if (jmm_int_handler_wf() == JMM_FAIL) {
        jmm_uninit_shm_wf();
        event_base_free(base);
        return JMM_FAIL;
    }
    // event
    if(jmm_init_event_wf(base) == JMM_FAIL){
        jmm_unint_handler_wf();
        jmm_uninit_shm_wf();
        event_base_free(base);
        return JMM_FAIL;
    }

    printf("child(%d) entering event loop...\n", wf_id);
    event_base_dispatch(base);
    jmm_uninit_event_wf();
    jmm_unint_handler_wf();
    jmm_uninit_shm_wf();
    event_base_free(base);

    return JMM_SUCCESS;
}
