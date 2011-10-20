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

    Logger* CreateLogger(const StdChar* szConf);
    bool IsConfOk(const StdChar* szConf);

public:
    static LogFactory* GetInst();
    static void ReleaseRC();

private:
    void InitFactory();
private:
    static LogFactory* sm_Inst;

    std::map<StdString, Appender*> m_MapObjPool;
};

//Internal use only
class LogWrapper
{
public:
    LogWrapper(const StdChar* szConf);
    ~LogWrapper();
};

XBASIC_NAMESPACE_END

#endif /* LOGFACTORY_H_ */