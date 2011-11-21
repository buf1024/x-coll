/*
 * File       : LogLevel.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef XBASIC_LOGLEVEL_H_
#define XBASIC_LOGLEVEL_H_

#include "XBasicCore.h"


XBASIC_NAMEPACE_BEGIN

enum LogLevel
{
    ALL     = 0,
    DEBUG   = 100,
    INFO    = 200,
    WARN    = 300,
    ERR     = 400,
    FATAL   = 500,
    OFF     = 600
};


XBASIC_NAMESPACE_END

#endif /* XBASIC_LOGLEVEL_H_ */
