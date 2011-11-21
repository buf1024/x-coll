/*
 * File       : NIXMutexLocker.cpp
 * Description: 
 * Version    : 2011-10-24 Created
 * Author     : buf1024@gmail.com
 */
#include "NIXMutexLocker.h"

#ifndef MSWINDOWS

USE_XBASIC_NAMESPACE;

NIXMutexLocker::NIXMutexLocker(void)
{
    pthread_mutex_init(&m_Mutex, NullPtr);
}

NIXMutexLocker::~NIXMutexLocker(void)
{
    pthread_mutex_destroy(&m_Mutex);
}


bool NIXMutexLocker::Lock()
{
    return pthread_mutex_lock(&m_Mutex) == 0;
}
bool NIXMutexLocker::TryLock()
{
    return pthread_mutex_trylock(&m_Mutex) == 0;
}
bool NIXMutexLocker::Unlock()
{
    return pthread_mutex_unlock(&m_Mutex) == 0;
}


#endif

