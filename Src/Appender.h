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
    virtual void Init(const char* szConf){}
    virtual unsigned int Write(int nLogLevel, const std::string& strMsg) = 0;
    virtual unsigned int Write(int nLogLevel, const char* szMsg, unsigned int nLen = -1) = 0;
    virtual Appender* Clone() = 0;

};
XBASIC_NAMESPACE_END

#endif /* APPENDER_H_ */