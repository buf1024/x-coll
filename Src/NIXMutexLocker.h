/*
 * File       : NIXMutexLocker.h
 * Description: 
 * Version    : 2011-10-24 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XBASIC_NIXMUTEXLOCKER_H_
#define XBASIC_NIXMUTEXLOCKER_H_

#ifndef _MSC_VER

#include "XBasicCore.h"
#include "Locker.h"
#include <pthread.h>

XBASIC_NAMEPACE_BEGIN


class XBASICAPI NIXMutexLocker :
    public Locker
{
public:
    NIXMutexLocker(void);
    ~NIXMutexLocker(void);

    bool Lock();
    bool TryLock();
    bool Unlock();

private:
    pthread_mutex_t m_Mutex;

};


XBASIC_NAMESPACE_END

#endif /* _MSC_VER */


#endif /* XBASIC_NIXMUTEXLOCKER_H_ */
