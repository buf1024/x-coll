/*
 * File       : Locker.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */

#ifndef LOCKER_H_
#define LOCKER_H_


#include "XBasicCore.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI Locker
{
public:
    Locker(){}
    virtual ~Locker(){}
public:
    virtual bool Lock() = 0;
    virtual bool TryLock() = 0;
    virtual bool Unlock() = 0;
};

XBASIC_NAMESPACE_END

#endif /* LOCKER_H_ */

