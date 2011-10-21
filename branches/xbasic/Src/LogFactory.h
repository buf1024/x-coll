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

class XBASICAPI LogFactory
{
private:
    LogFactory(void);

public:
    ~LogFactory(void);

    Logger* CreateLogger(const char* szConf);
    bool IsConfOk(const char* szConf);

public:
    static LogFactory* GetInst();
    static void ReleaseRC();

private:
    void InitFactory();
private:
    static LogFactory* sm_Inst;
    typedef struct MapWrapper
    {
        std::map<std::string, Appender*> m_MapObjPool;
    };
    MapWrapper* m_pMapWrapper;
};

//Internal use only
class LogWrapper
{
public:
    LogWrapper(const char* szConf);
    ~LogWrapper();
};

XBASIC_NAMESPACE_END

#endif /* LOGFACTORY_H_ */