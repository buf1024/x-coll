/*
 * jcc_proc.h
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JCC_PROC_H__
#define __48SLOTS_JCC_PROC_H__

int jcc_init_worker();
int jcc_uninit_workder();


int jcc_lock_buffer();
int jcc_unlock_buffer();
int jcc_add_buffer(const char* buf, int len);

#endif /* __48SLOTS_JCC_PROC_H__ */
