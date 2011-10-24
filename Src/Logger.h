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
class Section;
class Config;
class XBASICAPI Logger
{
public:
    Logger();
    ~Logger();

public:

    void Init(const Section* pSec);
    void Init(const Config* pConf);

    std::string GetName() const;
    void SetName(const std::string strName);

    void SetLogLevel(LogLevel eLvl);
    LogLevel GetLogLevel() const;

    void SetLocker(Locker* pLocker);
    Locker* GetLocker() const;

    void AddAppender(Appender* pApp);
    void RemoveAppender(const std::string strAppName);
    Appender* GetAppender(const std::string strAppName);

public:
    void Info(const char* szFormat, ...);
    void Debug(const char* szFormat, ...);
    void Warn(const char* szFormat, ...);
    void Error(const char* szFormat, ...);
    void Fatal(const char* szFormat, ...);

    void LogMessage(LogLevel eLvl, const char* szFormat, ...); 
    void LogMessageV(LogLevel eLvl, const char* szFormat, va_list va); 

protected:
    void Log(LogLevel eLvl, const char* szMsg, int nLen = -1);
    void Init(const char* szConf);

    std::string GetLogHeader(LogLevel eLvl);
    std::string GetCurTime();

protected:
    Locker* m_pLocker;
    LogLevel m_eLvl;

    typedef struct ListWrapper
    {
        std::list<Appender*> m_lstApps;
    };
    ListWrapper* m_pListWrapper;

    std::string m_strName;

};

XBASIC_NAMESPACE_END


#endif /* Logger_H_ */

