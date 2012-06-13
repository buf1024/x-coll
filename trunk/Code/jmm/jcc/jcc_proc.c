/*
 * jcc_proc.c
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */


#include "jcc_cmmhdr.h"
#include "jcc_proc.h"
#include "jcc_event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static char recv_buf[JCC_MAX_RECV_BUF_LEN] = "";
static pthread_t thr_id;


static int jcc_getline(char* buf, int len);

static void* jcc_worker_thread(void* arg);

int jcc_lock_buffer()
{
    if(pthread_mutex_lock(&mutex) != 0){
        return JCC_FAIL;
    }
    return JCC_SUCCESS;
}
int jcc_unlock_buffer()
{
    if(pthread_mutex_unlock(&mutex) != 0){
        return JCC_FAIL;
    }
    return JCC_SUCCESS;
}

int jcc_add_buffer(const char* buf, int len)
{
    if(len > JCC_MAX_RECV_BUF_LEN - sizeof(int)){
        return JCC_FAIL;
    }

    memset(recv_buf, 0, JCC_MAX_RECV_BUF_LEN);
    memcpy(recv_buf, &len, sizeof(int));
    memcpy(recv_buf+sizeof(int), buf, len);

    return JCC_SUCCESS;
}

int jcc_init_worker()
{
    if (pthread_create(&thr_id, NULL, jcc_worker_thread, NULL) != 0) {
        return JCC_FAIL;
    }
    return JCC_SUCCESS;
}
int jcc_uninit_workder()
{
    jcc_unlock_buffer(&mutex);
    return JCC_SUCCESS;
}

static void* jcc_worker_thread(void* arg)
{
    printf("jcc_worker_thread\n");

    char buf[JCC_MAX_SEND_BUF_LEN] = "";
    int buf_len = 0;

    jcc_lock_buffer(&mutex);

    while(JCC_TRUE){

        // wait for data ready
        printf("input:");
        buf_len = jcc_getline(buf, JCC_MAX_SEND_BUF_LEN);
        if(buf_len < 0){
            fprintf(stderr, "invalid input\n");
            continue;
        }
        if(buf_len == 0){
            continue;
        }

        printf("len:%d, data=%s\n", buf_len, buf);
        if(strcmp(buf, "exit") == 0){
            // not thread safe
            jcc_quit_event_loop();
            pthread_exit(NULL);
            break;
        }
        jcc_push_msg(buf, buf_len);
        jcc_lock_buffer(&mutex);
        int len = *(int*)recv_buf;
        printf("get data, len:%d, data:%s\n", len, recv_buf+sizeof(int));
    }

    return NULL;
}

static int jcc_getline(char* buf, int len)
{
    int i_len = 0;
    memset(buf, 0, len);
    while(((*(buf+i_len)) = getc(stdin)) != '\n'){
        i_len++;
        if(i_len >= len -1 ){
            break;
        }
    }
    if(i_len >= len - 1){
        return -1;
    }
    buf[i_len] = 0;

    return i_len;
}
