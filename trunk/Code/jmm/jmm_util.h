/*
 * jmm_util.h
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_JMM_UTIL_H__
#define __48SLOTS_JMM_UTIL_H__

#define offset(type, field)                         \
    ((size_t)&(((type*)(0))->field))

void jmm_daemonlize();

#endif /* __48SLOTS_JMM_UTIL_H__ */
