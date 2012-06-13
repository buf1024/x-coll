/*
 * jct_proc.c
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */


#include "jct_cmmhdr.h"
#include "jct_proc.h"
#include "jct_event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static char recv_buf[JCC_MAX_RECV_BUF_LEN] = "";
static pthread_t thr_id;


static int jct_getline(char* buf, int len);

static void* jct_worker_thread(void* arg);

int jct_lock_buffer()
{
    if(pthread_mutex_lock(&mutex) != 0){
        return JCT_FAIL;
    }
    return JCT_SUCCESS;
}
int jct_unlock_buffer()
{
    if(pthread_mutex_unlock(&mutex) != 0){
        return JCT_FAIL;
    }
    return JCT_SUCCESS;
}

int jct_add_buffer(const char* buf, int len)
{
    if(len > JCC_MAX_RECV_BUF_LEN - sizeof(int)){
        return JCT_FAIL;
    }

    memset(recv_buf, 0, JCC_MAX_RECV_BUF_LEN);
    memcpy(recv_buf, &len, sizeof(int));
    memcpy(recv_buf+sizeof(int), buf, len);

    return JCT_SUCCESS;
}

int jct_init_worker()
{
    if (pthread_create(&thr_id, NULL, jct_worker_thread, NULL) != 0) {
        return JCT_FAIL;
    }
    return JCT_SUCCESS;
}
int jct_uninit_workder()
{
    jct_unlock_buffer(&mutex);
    return JCT_SUCCESS;
}

static void* jct_worker_thread(void* arg)
{
    printf("jct_worker_thread\n");

    char buf[JCC_MAX_SEND_BUF_LEN] = "";
    int buf_len = 0;

    jct_lock_buffer(&mutex);

    while(JCT_TRUE){

        // wait for data ready
        printf("input:");
        buf_len = jct_getline(buf, JCC_MAX_SEND_BUF_LEN);
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
            jct_quit_event_loop();
            pthread_exit(NULL);
            break;
        }
        jct_push_msg(buf, buf_len);
        jct_lock_buffer(&mutex);
        int len = *(int*)recv_buf;
        printf("get data, len:%d, data:%s\n", len, recv_buf+sizeof(int));
    }

    return NULL;
}

static int jct_getline(char* buf, int len)
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
