/*
* File       : Logger.cpp
* Description: 
* Version    : 2011-10-14 Created
* Author     : buf1024@gmail.com
*/

#include "Logger.h"
#include "Locker.h"
#include "Config.h"
#include "IniConfig.h"
#include "Appender.h"
#include <stdio.h>

#ifdef MSWINDOWS
#include "WinCriticalSectionLocer.h"
#pragma warning(disable:4996)
#endif

#define MSG_BUF 2048

USE_XBASIC_NAMESPACE

Logger::Logger()
: m_strName("Logger")
{
    m_pListWrapper = new ListWrapper;
    m_eLvl = ALL;
#ifdef MSWINDOWS
    m_pLocker = new WinCriticalSectionLocer;
#endif
}
Logger::~Logger()
{
    delete m_pListWrapper;
    delete m_pLocker;
}

void Logger::Init(const Section* pSec)
{

}
void Logger::Init(const Config* pConf)
{

}
std::string Logger::GetName() const
{
    return m_strName;
}
void Logger::SetName(const std::string strName)
{
    m_strName = strName;
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
    if (pApp)
    {
        if (GetAppender(pApp->GetName()) == NullPtr)
        {
            m_pListWrapper->m_lstApps.push_back(pApp);
        }
    }
}
void Logger::RemoveAppender(const std::string strAppName)
{

    for (std::list<Appender*>::iterator iter = m_pListWrapper->m_lstApps.begin();
        iter != m_pListWrapper->m_lstApps.end(); ++iter)
    {
        if ((*iter)->GetName() == strAppName)
        {
            delete *iter;
            m_pListWrapper->m_lstApps.erase(iter);
        }
    }

}
Appender* Logger::GetAppender(const std::string strAppName)
{
    for (std::list<Appender*>::iterator iter = m_pListWrapper->m_lstApps.begin();
        iter != m_pListWrapper->m_lstApps.end(); ++iter)
    {
        if ((*iter)->GetName() == strAppName)
        {
            return *iter;
        }
    }
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
    for (std::list<Appender*>::iterator iter = m_pListWrapper->m_lstApps.begin();
        iter != m_pListWrapper->m_lstApps.end(); ++iter)
    {
        Appender* pApp = *iter;
        pApp->Write(eLvl, szMsg, nLen);
    }
}

void Logger::Init(const char* szConf)
{

}
