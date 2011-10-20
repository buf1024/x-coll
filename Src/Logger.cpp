/*
* File       : Logger.cpp
* Description: 
* Version    : 2011-10-14 Created
* Author     : buf1024@gmail.com
*/

#include "Logger.h"
#include "Locker.h"
#include <stdio.h>

#pragma warning(disable:4996)
#define MSG_BUF 2048

USE_XBASIC_NAMESPACE;


Logger* g_pGlobalPrivateLogger = NullPtr;

Logger::Logger()
{
    m_eLvl = ALL;
    m_pLocker = NullPtr;
}
Logger::~Logger()
{

}

void Logger::SetLogLevel(LogLevel eLvl)
{
    m_eLvl = eLvl;
}
LogLevel Logger::GetLogLevel() const
{
    return m_eLvl;
}

void Logger::SetLocker(Locker* pLocker)
{
    ASSERT(pLocker != NullPtr);
    if (m_pLocker != NullPtr)
    {
        delete m_pLocker;
    }
    m_pLocker = pLocker;
}
Locker* Logger::GetLocker() const
{
    return m_pLocker;
}

void Logger::AddAppender(Appender* pApp)
{

}
void Logger::RemoveAppender(Appender* pApp)
{

}
Appender* Logger::GetAppender(const std::string strAppName)
{
    return NullPtr;
}

void Logger::Info(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(INFO, szFormat, va);
    va_end(va);
}

void Logger::Debug(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(DEBUG, szFormat, va);
    va_end(va);
}

void Logger::Warn(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(WARN, szFormat, va);
    va_end(va);
}

void Logger::Error(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(ERR, szFormat, va);
    va_end(va);
}

void Logger::Fatal(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(FATAL, szFormat, va);
    va_end(va);
}

void Logger::LogMessage(LogLevel eLvl, const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(eLvl, szFormat, va);
    va_end(va);
}

void Logger::LogMessageV(LogLevel eLvl, const char* szFormat, va_list va)
{
    ASSERT(m_pLocker != NullPtr);
    m_pLocker->Lock();

    char szMsg[MSG_BUF] = {0};
    int nLen = -1;
    do 
    {
        nLen = vsnprintf(szMsg, MSG_BUF, szFormat, va);
        if (nLen == -1)
        {
            Log(eLvl, szMsg, MSG_BUF);
        }
        else
        {
            Log(eLvl, szMsg);
        }

    } while(nLen == -1);



    m_pLocker->Unlock();
}

void Logger::Log(LogLevel eLvl, const char* szMsg, int nLen)
{

}

void Logger::Init(const char* szConf)
{

}
