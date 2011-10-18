/*
 * File       : LogFactory.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "LogFactory.h"
#include "Logger.h"

USE_XBASIC_NAMESPACE;

extern Logger* g_pGlobalPrivateLogger;

LogFactory* LogFactory::sm_Inst = NullPtr;

LogFactory::LogFactory(void)
{
}

LogFactory::~LogFactory(void)
{
}
Logger* LogFactory::CreateLogger(const StdChar* szConf)
{
    Logger* pLogger = NullPtr;

    if(!IsConfOk(szConf)){

    }

    return pLogger;
}
bool IsConfOk(const StdChar* szConf)
{
    return false;
}
LogFactory* LogFactory::GetInst()
{
    if (sm_Inst == NullPtr)
    {
        sm_Inst = new LogFactory;
    }
    return sm_Inst;
}
void LogFactory::ReleaseRC()
{
    if (sm_Inst != NullPtr)
    {
        delete sm_Inst;
    }
}

LogWrapper::LogWrapper(const StdChar* szConf)
{
    if (g_pGlobalPrivateLogger = NullPtr)
    {
        delete g_pGlobalPrivateLogger;
    }
    LogFactory* pFactory = LogFactory::GetInst();
    g_pGlobalPrivateLogger = pFactory->CreateLogger(szConf);
}
LogWrapper::~LogWrapper()
{
    LogFactory* pFactory = LogFactory::GetInst();
    pFactory->ReleaseRC();
}
