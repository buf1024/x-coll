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

XBASIC_NAMEPACE_BEGIN

class Loger;

class XBASICAPI LogFactory
{
private:
    LogFactory(void);

public:
    ~LogFactory(void);

    Loger* CreateLoger(const StdChar* szConf);

public:
    static LogFactory* GetInst();
    static void ReleaseRC();

private:
    static LogFactory* sm_Inst;
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