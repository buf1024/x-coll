/*
 * File       : Appender.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef XBASIC_APPENDER_H_
#define XBASIC_APPENDER_H_

#include "XBasicCore.h"
#include "LogLevel.h"
#include "StdString.h"

XBASIC_NAMEPACE_BEGIN

class Section;
class Config;
class XBASICAPI Appender
{
public:
    Appender()
        : m_strName("Appender")
    {
    }
    virtual ~Appender()
    {

    }
public:
    virtual void Init(const char* szConf){}
    virtual void Init(Section* pSec){}
    virtual void Init(Config* pConf){}
    unsigned int Write(LogLevel eLogLevel, const std::string& strMsg)
    {
        return Write(eLogLevel, strMsg.c_str(), strMsg.length());
    }
    virtual unsigned int Write(LogLevel eLogLevel, const char* szMsg, int nLen = -1) = 0;
    virtual Appender* Clone() = 0;
    
    virtual bool IsAppenderOK()
    {
        return false;
    }

    std::string GetName() const
    {
        return m_strName;
    }

protected:
    std::string m_strName;
};
XBASIC_NAMESPACE_END

#endif /* XBASIC_APPENDER_H_ */

