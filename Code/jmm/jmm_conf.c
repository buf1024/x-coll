/*
 * jmm_conf.c
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#include "jmm_conf.h"
#include "ciniconfig.h"
#include <string.h>

#define JMM_CONF_DEF_NET_PORT                     10433
#define JMM_CONF_DEF_NET_BACKLOG                  128
#define JMM_CONF_DEF_PROC_NUM                     8
#define JMM_CONF_DEF_PROC_SVR_NUM                 1
#define JMM_CONF_DEF_SHM_PATH                     "conf/jmm_shm"
#define JMM_CONF_DEF_CONF_PATH                    "conf/jmm.conf"

int jmm_init_conf(jmm_conf* conf)
{
    if(!conf){
        return JMM_FAIL;
    }

    return JMM_SUCCESS;
}
int jmm_init_def_conf(jmm_conf* conf)
{
    if(!conf){
        return JMM_FAIL;
    }

    conf->net_port = JMM_CONF_DEF_NET_PORT;
    conf->net_backlog = JMM_CONF_DEF_NET_BACKLOG;
    conf->proc_num = JMM_CONF_DEF_PROC_NUM;
    conf->proc_svr_num = JMM_CONF_DEF_PROC_SVR_NUM;
    strcpy(conf->shm_path, JMM_CONF_DEF_SHM_PATH);

    strcpy(conf->conf_path, JMM_CONF_DEF_CONF_PATH);

    return JMM_SUCCESS;
}

