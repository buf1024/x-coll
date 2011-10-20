/*
 * File       : Logger.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef Logger_H_
#define Logger_H_

#include "XBasicCore.h"
#include "StdString.h"
#include "LogLevel.h"
#include <stdarg.h>
#include <list>

XBASIC_NAMEPACE_BEGIN

class Locker;
class Appender;

class XBASICAPI Logger
{
public:
    Logger();
    ~Logger();

public:
    void SetLogLevel(LogLevel eLvl);
    LogLevel GetLogLevel() const;

    void SetLocker(Locker* pLocker);
    Locker* GetLocker() const;

    void AddAppender(Appender* pApp);
    void RemoveAppender(Appender* pApp);
    Appender* GetAppender(const StdString strAppName);

public:
    void Info(const StdChar* szFormat, ...);
    void Debug(const StdChar* szFormat, ...);
    void Warn(const StdChar* szFormat, ...);
    void Error(const StdChar* szFormat, ...);
    void Fatal(const StdChar* szFormat, ...);

    void LogMessage(LogLevel eLvl, const StdChar* szFormat, ...); 
    void LogMessageV(LogLevel eLvl, const StdChar* szFormat, va_list va); 

protected:
    void Log(LogLevel eLvl, const StdChar* szMsg, int nLen = -1);
    void Init(const StdChar* szConf);

protected:
    Locker* m_pLocker;
    LogLevel m_eLvl;

    std::list<Appender*> m_lstApps;

};

XBASIC_NAMESPACE_END


#endif /* Logger_H_ */