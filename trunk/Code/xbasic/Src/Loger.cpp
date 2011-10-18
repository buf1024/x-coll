/*
* File       : Loger.cpp
* Description: 
* Version    : 2011-10-14 Created
* Author     : buf1024@gmail.com
*/

#include "Loger.h"
#include "Locker.h"

USE_XBASIC_NAMESPACE;

Loger* g_pGlobalPrivateLoger = NullPtr;

Loger::Loger()
{
    m_eLvl = ALL;
    m_pLocker = NullPtr;
}
Loger::~Loger()
{

}

void Loger::SetLogLevel(LogLevel eLvl)
{
    m_eLvl = eLvl;
}
LogLevel Loger::GetLogLevel() const
{
    return m_eLvl;
}

void Loger::SetLocker(Locker* pLocker)
{
    ASSERT(pLocker != NullPtr);
    if (m_pLocker != NullPtr)
    {
        delete m_pLocker;
    }
    m_pLocker = pLocker;
}
Locker* Loger::GetLocker() const
{
    return m_pLocker;
}

void Loger::Info(const StdChar* szFormat, ...)
{
}

void Loger::Debug(const StdChar* szFormat, ...)
{
}

void Loger::Warn(const StdChar* szFormat, ...)
{
}

void Loger::Error(const StdChar* szFormat, ...)
{
}

void Loger::Fatal(const StdChar* szFormat, ...)
{
}

void Loger::LogMessage(LogLevel eLvl, const StdChar* szFormat, ...)
{
 

}
