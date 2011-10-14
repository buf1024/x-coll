/*
 * File       : Appender.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef APPENDER_H_
#define APPENDER_H_

#include "XBasicCore.h"
#include "StdString.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI Appender
{
public:
    virtual unsigned int Write(int nLogLevel, const StdString& strMsg)
    {
        return 0;
    }
    virtual unsigned int Write(int nLogLevel, const StdChar* szMsg, unsigned int nLen = -1)
    {
        return 0;
    }
};
XBASIC_NAMESPACE_END

#endif /* APPENDER_H_ */