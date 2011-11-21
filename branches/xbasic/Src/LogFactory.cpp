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
#include "XmlConfig.h"
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

USE_XBASIC_NAMESPACE

LogFactory* LogFactory::sm_Inst = NullPtr;

LogFactory::LogFactory(void)
{
    m_pGlobalLogger = new Logger;
    InitAppenderPool();
}

LogFactory::~LogFactory(void)
{
    delete m_pGlobalLogger;
}
bool LogFactory::InitLogger(LogDestination enDest, const char* szConf)
{
    Logger* pLogger = GetGlobalLogger();

    if (pLogger == NullPtr)
    {
        return false;
    }

    bool bRet = false;

    switch(enDest)
    {
    case Console:
        bRet = InitConsoleAppender(pLogger);
    	break;
    case File:
        bRet = InitFileAppender(pLogger, szConf);
    	break;
    case StdConf:
        bRet = InitStdConfAppender(pLogger, szConf);
        break;
    default:
        bRet = InitConsoleAppender(pLogger);
        break;
    }

    return bRet;
}
bool LogFactory::InitConsoleAppender(Logger* pLogger)
{
    Appender* pApp = GetAppender("ConsoleAppender");
    if (pApp)
    {
        pLogger->AddAppender(pApp);
        return true;
    }
    return false;
}
bool LogFactory::InitFileAppender(Logger* pLogger, const char* szFile)
{
    Appender* pApp = GetAppender("FileAppender");
    if (pApp)
    {
        if (IsFileExists(szFile))
        {
            pApp->Init(szFile);
            pLogger->AddAppender(pApp);
            return true;
        }      
    }
    return false;
}
bool LogFactory::InitStdConfAppender(Logger* pLogger, const char* szConf)
{
    if (IsFileExists(szConf))
    {
        std::string strConf = StdString::ToLower(szConf);
        XmlConfig* pXMLConf = NullPtr;
        IniConfig* pIniConf = NullPtr;
        if (StdString::EndsWith(strConf, ".xml"))
        {
            pXMLConf = new XmlConfig;
            pXMLConf->Load(strConf);
        }
        else
        {
            pIniConf = new IniConfig;
            pIniConf->Load(strConf);
        }
        Appender* pApp = NullPtr;
        if (pXMLConf)
        {
            for(XmlConfig::Iterator iter = pXMLConf->begin();
                iter != pXMLConf->end(); ++iter)
            {
                std::string strName = iter->first;
                if (strName == m_pGlobalLogger->GetName())
                {
                    m_pGlobalLogger->Init(iter->second);
                }
                else
                {
                    pApp = GetAppender(strName);
                    if (pApp)
                    {
                        pApp->Init(iter->second);
                        pLogger->AddAppender(pApp);
                    }
                }
                
            }

            delete pXMLConf;
        }
        if (pIniConf)
        {
            for(IniConfig::Iterator iter = pIniConf->begin();
                iter != pIniConf->end(); ++iter)
            {
                Section* pSec = *iter;
                std::string strName = pSec->GetSectionName();
                if (strName == m_pGlobalLogger->GetName())
                {
                    m_pGlobalLogger->Init(pSec);
                }
                else
                {
                    pApp = GetAppender(strName);
                    if (pApp)
                    {
                        pApp->Init(pSec);
                        pLogger->AddAppender(pApp);
                    }
                }
                
            }
            delete pIniConf;
        }
    }
    return true;
}
bool LogFactory::IsFileExists(const char* szFile)
{
    if (szFile == NullPtr || szFile[0] == '\0')
    {
        return false;
    }
    int nRet = -1;
#ifdef _MSC_VER
    nRet = _access(szFile, 04); //Read
#else
    nRet = access(szFile, 04); //Read
#endif
    return nRet == 0;
}
bool LogFactory::RegisterAppender(Appender* pApp)
{
    if (pApp)
    {
        std::string strName = pApp->GetName();
        AppPoolIterator iter = m_MapObjPool.find(strName);
        if (iter == m_MapObjPool.end())
        {
            m_MapObjPool.insert(std::make_pair(strName, pApp));
        }
        return true;
    }
    return false;
}

void LogFactory::UnRegisterAppender(std::string strName)
{
    AppPoolIterator iter = m_MapObjPool.find(strName);
    if (iter != m_MapObjPool.end())
    {
        delete iter->second;
        m_MapObjPool.erase(iter);
    }

}
Appender* LogFactory::GetAppender(std::string strName) const
{
    AppPoolIterator iter = m_MapObjPool.find(strName);
    if (iter == m_MapObjPool.end())
    {
        return NullPtr;
    }
    return iter->second->Clone();
}

Logger* LogFactory::GetGlobalLogger() const
{
    return m_pGlobalLogger;
}

void LogFactory::SetGlobalLogger(Logger* pLogger)
{
    if (m_pGlobalLogger != NullPtr)
    {
        delete m_pGlobalLogger;
    }
    m_pGlobalLogger = pLogger;
}

void LogFactory::InitAppenderPool()
{
    RegisterAppender(new FileAppender);
    RegisterAppender(new ConsoleAppender);

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

LogWrapper::LogWrapper(LogDestination enDest, const char* szConf)
{
    LogFactory* pFactory = LogFactory::GetInst();
    pFactory->InitLogger(enDest, szConf);
}
LogWrapper::~LogWrapper()
{
    LogFactory* pFactory = LogFactory::GetInst();
    pFactory->ReleaseRC();
}
