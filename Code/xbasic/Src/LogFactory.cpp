/*
 * File       : LogFactory.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "LogFactory.h"
#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"
#include "IniConfig.h"

USE_XBASIC_NAMESPACE;

extern Logger* g_pGlobalPrivateLogger;

LogFactory* LogFactory::sm_Inst = NullPtr;

LogFactory::LogFactory(void)
{
    InitFactory();
}

LogFactory::~LogFactory(void)
{
}
Logger* LogFactory::CreateLogger(const StdChar* szConf)
{
    Logger* pLogger = new Logger;

    Appender* pApp = NullPtr;

    if(!IsConfOk(szConf)){
        pApp = new ConsoleAppender;
        pLogger->AddAppender(pApp);
    }
    else
    {
        StdString strConf = ToLower(szConf);
        if (EndsWith(strConf.c_str, _T(".xml")))
        {
        }
        else
        {

        }
    }

    return pLogger;
}
bool IsConfOk(const StdChar* szConf)
{
    if (szConf == NullPtr || szConf[0] == '\0')
    {
        return false;
    }
    return true;
}
void LogFactory::InitFactory()
{
    m_MapObjPool.insert(std::make_pair(_T("FileAppender"), new FileAppender));
    m_MapObjPool.insert(std::make_pair(_T("ConsoleAppender"), new ConsoleAppender));
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
