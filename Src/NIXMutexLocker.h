/*
 * File       : NIXMutexLocker.h
 * Description: 
 * Version    : 2011-10-24 Created
 * Author     : buf1024@gmail.com
 */
#ifndef NIXMUTEXLOCKER_H_
#define NIXMUTEXLOCKER_H_

#ifndef MSWINDOWS

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

#endif /* MSWINDOWS */


#endif /* NIXMUTEXLOCKER_H_ */
