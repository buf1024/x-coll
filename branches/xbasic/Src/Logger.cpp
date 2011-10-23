/*
* File       : Logger.cpp
* Description: 
* Version    : 2011-10-14 Created
* Author     : buf1024@gmail.com
*/

#include "Logger.h"
#include "Locker.h"
#include "IniConfig.h"
#include "Appender.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <map>
#include <time.h>

#ifdef MSWINDOWS
#include "WinCriticalSectionLocer.h"
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

    std::string strHeader = GetLogHeader(eLvl);
    Log(eLvl, strHeader.c_str());

    size_t size = sizeof(char)*MSG_BUF;
    char* szMsg = (char*)malloc(size);
    if(szMsg)
    {
        int nLen = -1;
        while(nLen < 0)
        {
            nLen = vsnprintf(szMsg, size, szFormat, va);
            if (nLen < 0)
            {
                size += sizeof(char)*MSG_BUF;
                szMsg = (char*)realloc(szMsg, size);
            }
            else
            {
                Log(eLvl, szMsg);
            }
        }
        free(szMsg);
    }
    


    m_pLocker->Unlock();
}

void Logger::Log(LogLevel eLvl, const char* szMsg, int nLen)
{
    for (std::list<Appender*>::iterator iter = m_pListWrapper->m_lstApps.begin();
        iter != m_pListWrapper->m_lstApps.end(); ++iter)
    {
        Appender* pApp = *iter;
        if (pApp->IsAppenderOK())
        {
            pApp->Write(eLvl, szMsg, nLen);
        }        
    }
}

void Logger::Init(const char* szConf)
{

}

std::string Logger::GetLogHeader(LogLevel eLvl)
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
    strRet += GetCurTime();
    strRet += "] ";
    return strRet;
}

std::string Logger::GetCurTime()
{
    char szBuf[BUF_SIZE] = "";
    struct tm* psTime;
    time_t t = time(0);
    psTime = localtime(&t);

    //yyyy-mm-dd HH:MM:SS-MISS
    strftime(szBuf, BUF_SIZE, "%Y-%m-%d %H:%M:%S", psTime);

    return szBuf;
}