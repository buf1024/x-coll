/*
 * File       : Minilog.h
 * Description: 
 * Version    : 2011-11-12 Created
 * Author     : buf1024@gmail.com
 */
 
#ifndef XBASIC_MINILOG_H_
#define XBASIC_MINILOG_H_

#include "XBasicCore.h"

#include "Singleton.h"
#include <string>
#include <stdio.h>


XBASIC_NAMEPACE_BEGIN

enum LogLevel
{
    ALL     = 0,
    DEBUG   = 100,
    INFO    = 200,
    WARN    = 300,
    ERR     = 400,
    FATAL   = 500,
    OFF     = 600
};

// 单进程单线程使用，不进行同步操作
class Minilog
    : public Singleton<Minilog>
{
    DECL_SINGLETON(Minilog)
private:
    Minilog();
public:
    ~Minilog();
public:
    void Info(const char* szFormat, ...);
    void Debug(const char* szFormat, ...);
    void Warn(const char* szFormat, ...);
    void Error(const char* szFormat, ...);
    void Fatal(const char* szFormat, ...);
    
    void SetFileLogLevel(LogLevel eLvl);
    LogLevel GetFileLogLevel() const;
    void SetConsoleLogLevel(LogLevel eLvl);
    LogLevel GetConsoleLogLevel() const;

    void SetFilePath(const char* szPath);
    std::string GetFilePath() const;

    void FlushLog();

    void Log(LogLevel eLvl, const char* szMsg, int nLen = -1);

protected:
    void LogMessageV(LogLevel eLvl, const char* szFormat, va_list va); 
    std::string GetLogHeader(LogLevel eLvl);

private:
    LogLevel m_eFileLvl;
    LogLevel m_eConsoleLvl;
    
    std::string m_strPath;
    FILE* m_pFile;
};

XBASIC_NAMESPACE_END
 
#endif /* XBASIC_MINILOG_H_ */
 
 
 
 