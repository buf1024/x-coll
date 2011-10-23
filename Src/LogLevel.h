/*
 * File       : LogLevel.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */


#ifndef LOGLEVEL_H_
#define LOGLEVEL_H_

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

#endif /* LOGLEVEL_H_ */
