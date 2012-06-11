/*
 * jmm_util.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_UTIL_H__
#define __48SLOTS_JMM_UTIL_H__

#include <sys/types.h>

#define offset(type, field)                         \
    ((size_t)&(((type*)(0))->field))

void jmm_daemonlize();

ssize_t jmm_send_fd(int fd,/* void* ptr, size_t nbytes, */int sendfd);
ssize_t jmm_recv_fd(int fd,/* void* ptr, size_t nbytes, */int* recvfd);


#endif /* __48SLOTS_JMM_UTIL_H__ */
