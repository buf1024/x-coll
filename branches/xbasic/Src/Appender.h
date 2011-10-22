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

class Section;
class Config;
class XBASICAPI Appender
{
public:
    virtual void Init(const char* szConf){}
    virtual void Init(const Section* pSec){}
    virtual void Init(const Config* pConf){}
    virtual unsigned int Write(int nLogLevel, const std::string& strMsg) = 0;
    virtual unsigned int Write(int nLogLevel, const char* szMsg, unsigned int nLen = -1) = 0;
    virtual Appender* Clone() = 0;

    std::string GetName() const
    {
        return m_strName;
    }

protected:
    std::string m_strName;
};
XBASIC_NAMESPACE_END

#endif /* APPENDER_H_ */