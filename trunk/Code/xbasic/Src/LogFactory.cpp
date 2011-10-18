/*
 * File       : LogFactory.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "LogFactory.h"
#include "Loger.h"

USE_XBASIC_NAMESPACE;

extern Loger* g_pGlobalPrivateLoger;

LogFactory* LogFactory::sm_Inst = NullPtr;

LogFactory::LogFactory(void)
{
}

LogFactory::~LogFactory(void)
{
}
Loger* LogFactory::CreateLoger(const StdChar* szConf)
{
    return NullPtr;
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
    if (g_pGlobalPrivateLoger = NullPtr)
    {
        delete g_pGlobalPrivateLoger;
    }
    LogFactory* pFactory = LogFactory::GetInst();
    g_pGlobalPrivateLoger = pFactory->CreateLoger(szConf);
}
LogWrapper::~LogWrapper()
{
    LogFactory* pFactory = LogFactory::GetInst();
    pFactory->ReleaseRC();
}
