/*
 * jmm_proc.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_PROC_H__
#define __48SLOTS_JMM_PROC_H__

#include "jmm_conf.h"

int jmm_find_free_wf();
int jmm_assign_wf(int wf_id, int sock_fd);

int jmm_init_proc(jmm_conf* conf);
int jmm_uninit_proc();

int jmm_proc_clear_env_wf();
int jmm_proc_wf(int wf_id);

#endif /* __48SLOTS_JMM_PROC_H__ */
