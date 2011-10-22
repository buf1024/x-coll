/*
 * File       : LogFactory.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#ifndef LOGFACTORY_H_
#define LOGFACTORY_H_

#include "XBasicCore.h"
#include "StdString.h"

#include <map>

XBASIC_NAMEPACE_BEGIN

class Logger;
class Appender;

enum LogDestination{
    Console,
    File,
    StdConf
};

class XBASICAPI LogFactory
{
public:
    typedef std::map<std::string, Appender*>::iterator AppPoolIterator;
private:
    LogFactory(void);

public:
    ~LogFactory(void);

    bool InitLogger(LogDestination enDest, const char* szConf = NullPtr);
    bool IsFileExists(const char* szFile);

    bool RegisterAppender(Appender* pApp);
    void UnRegisterAppender(std::string strName);
    Appender* GetAppender(std::string strName) const;

    Logger* GetGlobalLogger() const;
    void SetGlobalLogger(Logger* pLogger);

public:
    static LogFactory* GetInst();
    static void ReleaseRC();

private:
    void InitAppenderPool();
    bool InitConsoleAppender(Logger* pLogger);
    bool InitFileAppender(Logger* pLogger, const char* szFile);
    bool InitStdConfAppender(Logger* pLogger, const char* szConf);
private:
    Logger* m_pGlobalLogger;
    static LogFactory* sm_Inst;
    typedef struct MapWrapper
    {
        std::map<std::string, Appender*> m_MapObjPool;
    };
    MapWrapper* m_pMapWrapper;
};



//Internal use only
class XBASICAPI LogWrapper
{
public:
    LogWrapper(LogDestination enDest, const char* szConf = NullPtr);
    ~LogWrapper();
};

XBASIC_NAMESPACE_END

#endif /* LOGFACTORY_H_ */