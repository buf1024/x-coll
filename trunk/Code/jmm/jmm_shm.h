/*
 * jmm_shm.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_SHM_H__
#define __48SLOTS_JMM_SHM_H__

#include "jmm_conf.h"
#include <sys/types.h>

typedef struct jmm_shm_sock
{
    int status;
    int sock_fd;
}jmm_shm_sock;

typedef struct jmm_shm_wf
{
    pid_t pid;
    int girl_fd;
    int boy_fd;
    int proc_svr_num;
    jmm_shm_sock* shm_sock;
}jmm_shm_wf;

typedef struct jmm_shm
{
    pid_t pid;
    int proc_num;
    jmm_shm_wf* shm_wf;
}jmm_shm;

size_t jmm_shm_size(int proc_num, int proc_svr_num);
size_t jmm_shm_wf_size(int proc_svr_num);
size_t jmm_shm_sock_size();
jmm_shm_wf* jmm_shm_get_wf(jmm_shm* theshm, int wf_id, int svr_num);
jmm_shm_sock* jmm_shm_get_sock(jmm_shm_wf* theshm, int sock_id);

int jmm_init_shm(jmm_conf* conf);
int jmm_uninit_shm();

int jmm_init_shm_wf(int wf_id, int wf_svr_num);
int jmm_uninit_shm_wf();

#endif /* __48SLOTS_JMM_SHM_H__ */
