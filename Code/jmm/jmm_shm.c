/*
 * jmm_shm.c
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */
#include "jmm_cmmhdr.h"
#include "jmm_shm.h"
#include "jmm_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>


static int       shm_id = -1;
jmm_shm*            shm = NULL;
jmm_shm_wf*      shm_wf = NULL;
extern jmm_conf    conf;

size_t jmm_shm_size(int proc_num, int proc_svr_num)
{
    return offset(jmm_shm, shm_wf) + proc_num*jmm_shm_wf_size(proc_svr_num);
}
size_t jmm_shm_wf_size(int proc_svr_num)
{
    return offset(jmm_shm_wf, shm_sock) + proc_svr_num*jmm_shm_sock_size();
}
size_t jmm_shm_sock_size()
{
    return sizeof(struct jmm_shm_wf);
}

jmm_shm_wf* jmm_shm_get_wf(jmm_shm* theshm, int wf_id, int svr_num)
{
    if(theshm == NULL){
        return NULL;
    }
    return (jmm_shm_wf*) ((char*) &(theshm->shm_wf)
            + wf_id * jmm_shm_wf_size(svr_num));
}
jmm_shm_sock* jmm_shm_get_sock(jmm_shm_wf* theshm, int sock_id)
{
    if(theshm == NULL){
        return NULL;
    }
    return (jmm_shm_sock*)((char*)&theshm->shm_sock + sock_id*jmm_shm_sock_size());
}


int jmm_init_shm(jmm_conf* conf)
{
    int shm_size = 0;
    key_t key = -1;
    jmm_shm_wf* shm_wf = NULL;
    int idx = 0;

    if(!conf){
        return JMM_FAIL;
    }

    key = ftok(conf->shm_path, JMM_SHARE_MEM_ID);
    if(key == -1){
        JMM_ERROR("fail to call ftok: path=%s progid=%d\n",
                conf->shm_path, JMM_SHARE_MEM_ID);
        return JMM_FAIL;
    }

    shm_size = jmm_shm_size(conf->proc_num, conf->proc_svr_num);

    shm_id = shmget(key, shm_size, IPC_CREAT | IPC_EXCL | 0600);

    if(shm_id == -1){
        JMM_ERROR("fail to create share memory\n");
        return JMM_FAIL;
    }

    shm = (struct jmm_shm*) shmat(shm_id, NULL, 0);
    memset(shm, 0, shm_size);

    shm->pid = getpid();
    shm->proc_num = conf->proc_num;

    for(idx = 0; idx < conf->proc_num; idx++){
        shm_wf = (jmm_shm_wf*)((char*)&(shm->shm_wf) + idx*jmm_shm_wf_size(conf->proc_svr_num));
        shm_wf->proc_svr_num = conf->proc_svr_num;
    }

    return JMM_SUCCESS;
}
int jmm_uninit_shm()
{
    if(shm != NULL){
        shmdt(shm);
        shmctl(shm_id, IPC_RMID, NULL);
        shm = NULL;
        shm_id = 0;
    }
    return JMM_SUCCESS;
}

int jmm_init_shm_wf(int wf_id, int wf_svr_num)
{
    key_t key = -1;

    key = ftok(conf.shm_path, JMM_SHARE_MEM_ID);
    if(key == -1){
        JMM_ERROR("fail to call ftok: path=%s progid=%d\n",
                conf.shm_path, JMM_SHARE_MEM_ID);
        return JMM_FAIL;
    }

    shm_id = shmget(key, 0, 0);

    if(shm_id == -1){
        JMM_ERROR("fail to create share memory\n");
        return JMM_FAIL;
    }

    if(shm){
        shmdt(shm);
    }

    shm = (jmm_shm*)shmat(shm_id, NULL, 0);

/*    shm_wf = (struct jmm_shm_wf*)((char*)(&shm->shm_wf)
            +  wf_id*jmm_shm_wf_size(wf_svr_num));*/
    shm_wf = jmm_shm_get_wf(shm, wf_id, wf_svr_num);

    return JMM_SUCCESS;
}
int jmm_uninit_shm_wf()
{
    if(shm_wf != NULL){
        shmdt(shm);
        shm    = NULL;
        shm_wf = NULL;
        shm_id = 0;
    }
    return JMM_SUCCESS;
}
