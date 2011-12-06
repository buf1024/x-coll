/*
 * File       : Minilog.h
 * Description: 
 * Version    : 2011-11-12 Created
 * Author     : buf1024@gmail.com
 */
#include "Minilog.h"
#include "StdString.h"
#include <time.h>

USE_XBASIC_NAMESPACE;

Minilog::Minilog()
{

}

Minilog::~Minilog()
{

}
void Minilog::Info(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(INFO, szFormat, va);
    va_end(va);
}
void Minilog::Debug(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(DEBUG, szFormat, va);
    va_end(va);
}
void Minilog::Warn(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(WARN, szFormat, va);
    va_end(va);
}
void Minilog::Error(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(ERR, szFormat, va);
    va_end(va);
}
void Minilog::Fatal(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(FATAL, szFormat, va);
    va_end(va);
}

void Minilog::SetFileLogLevel(LogLevel eLvl)
{
    m_eFileLvl = eLvl;
}
LogLevel Minilog::GetFileLogLevel() const
{
    return m_eFileLvl;
}
void Minilog::SetConsoleLogLevel(LogLevel eLvl)
{
    m_eConsoleLvl = eLvl;
}
LogLevel Minilog::GetConsoleLogLevel() const
{
    return m_eConsoleLvl;
}

void Minilog::SetFilePath(const char* szPath)
{
    m_strPath = szPath;
}
std::string Minilog::GetFilePath() const
{
    return m_strPath;
}

void Minilog::FlushLog()
{

}


void Minilog::Log(LogLevel eLvl, const char* szMsg, int nLen)
{

}
void Minilog::LogMessageV(LogLevel eLvl, const char* szFormat, va_list va)
{

}
std::string Minilog::GetLogHeader(LogLevel eLvl)
{
    std::string strRet;
    switch(eLvl)
    {
    case DEBUG:
        strRet += "[D]";
        break;
    case INFO:
        strRet += "[I]";
        break;
    case WARN:
        strRet += "[W]";
        break;
    case ERR:
        strRet += "[E]";
        break;
    case FATAL:
        strRet += "[F]";
        break;
    default:
        break;
    }
    strRet += "[";
    strRet += StdString::FromNumber((long)time(0));
    strRet += "] ";
    return strRet;
}




