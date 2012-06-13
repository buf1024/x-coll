/*
 * jct_proc.h
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JCT_PROC_H__
#define __48SLOTS_JCT_PROC_H__

int jct_init_worker();
int jct_uninit_workder();


int jct_lock_buffer();
int jct_unlock_buffer();
int jct_add_buffer(const char* buf, int len);

#endif /* __48SLOTS_JCT_PROC_H__ */
