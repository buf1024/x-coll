/*
 * File       : Loger.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef LOGER_H_
#define LOGER_H_

#include "XBasicCore.h"
#include "StdString.h"

#include "LogLevel.h"

XBASIC_NAMEPACE_BEGIN

class Locker;

class XBASICAPI Loger
{
public:
    Loger();
    virtual ~Loger();

public:
    void SetLogLevel(LogLevel eLvl);
    LogLevel GetLogLevel() const;

public:
    void Info(const StdString& strMsg);
    void Info(const StdChar* szMsg, int nLen = -1);

    void Debug(const StdString& strMsg);
    void Debug(const StdChar* szMsg, int nLen = -1);

    void Warn(const StdString& strMsg);
    void Warn(const StdChar* szMsg, int nLen = -1);

    void Error(const StdString& strMsg);
    void Error(const StdChar* szMsg, int nLen = -1);

    void Fatal(const StdString& strMsg);
    void Fatal(const StdChar* szMsg, int nLen = -1);

protected:
    virtual void LogMessage(LogLevel eLvl, const StdChar* szMsg, int nLen = -1) = 0;

protected:
    Locker* m_pLocker;

};

XBASIC_NAMESPACE_END


#endif /* LOGER_H_ */