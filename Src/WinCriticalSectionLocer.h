/*
 * File       : WinCriticalSectionLocer.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_WINCRITICALSECTIONLOCKER_H_
#define XBASIC_WINCRITICALSECTIONLOCKER_H_

#include "Locker.h"

#ifdef MSWINDOWS

XBASIC_NAMEPACE_BEGIN

class XBASICAPI WinCriticalSectionLocer :
    public Locker
{
public:
    WinCriticalSectionLocer(void);
    virtual ~WinCriticalSectionLocer(void);

    bool Lock();
    bool TryLock();
    bool Unlock();

private:
    CRITICAL_SECTION m_sCS;
};


XBASIC_NAMESPACE_END

#endif

#endif /* XBASIC_WINCRITICALSECTIONLOCKER_H_ */

