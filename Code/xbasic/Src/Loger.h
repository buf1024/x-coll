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
protected:
    Loger();
public:
    virtual ~Loger();

public:
    void SetLogLevel(LogLevel eLvl);
    LogLevel GetLogLevel() const;

    void SetLocker(Locker* pLocker);
    Locker* GetLocker() const;

public:
    void Info(const StdChar* szFormat, ...);
    void Debug(const StdChar* szFormat, ...);
    void Warn(const StdChar* szFormat, ...);
    void Error(const StdChar* szFormat, ...);
    void Fatal(const StdChar* szFormat, ...);

    void LogMessage(LogLevel eLvl, const StdChar* szFormat, ...); 

protected:
    virtual void Log(LogLevel eLvl, const StdChar* szMsg, int nLen = -1) = 0;
    virtual void Init(const StdChar* szConf);

protected:
    Locker* m_pLocker;

    LogLevel m_eLvl;

};

XBASIC_NAMESPACE_END


#endif /* LOGER_H_ */