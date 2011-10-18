/*
 * File       : Log.h
 * Description: 
 * Version    : 2011-10-15 Created
 * Author     : buf1024@gmail.com
 */

#ifndef LOG_H_
#define LOG_H_

#include "LogLevel.h"
#include "LogFactory.h"

extern Loger* g_pGlobalPrivateLoger;

#define LOG_DEBUG(ARGS)\

#define LOG_INFO(ARGS)\

#define LOG_WARN(ARGS)\

#define LOG_ERROR(ARGS)\

#define LOG_FATAL(ARGS)\

#define SET_LOG_LEVEL(level)\
{\
    ASSERT(g_pGlobalPrivateLoger != NullPtr);\
    g_pGlobalPrivateLoger->SetLogLevel(level);\
}\

#define SET_LOGER(pLog)\
{\
    ASSERT(pLog != NullPtr);\
    if (g_pGlobalPrivateLoger != NullPtr)\
    {\
        delete g_pGlobalPrivateLoger;\
        g_pGlobalPrivateLoger = NullPtr;\
    }\
    g_pGlobalPrivateLoger = pLog;\
}\

#define INIT_DEFLOG(szFile)\
    LogWrapper* pGlobalPriviteLogWraper = new LogWrapper(szFile);

#endif /* LOG_H_ */
