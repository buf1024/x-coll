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

extern Logger* g_pGlobalPrivateLogger;

#define LOG_DEBUG(...)                                                        \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->LogMessage(DEBUG, __VA_ARGS__);                   \
}                                                                             \

#define LOG_INFO(...)                                                         \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->LogMessage(INFO, __VA_ARGS__);                    \
}                                                                             \

#define LOG_WARN(...)                                                         \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->LogMessage(WARN, __VA_ARGS__);                    \
}                                                                             \

#define LOG_ERROR(...)                                                        \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->LogMessage(ERR, __VA_ARGS__);                     \
}                                                                             \

#define LOG_FATAL(...)                                                        \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->LogMessage(FATAL, __VA_ARGS__);                   \
}                                                                             \

#define SET_LOG_LEVEL(level)                                                  \
{                                                                             \
    ASSERT(g_pGlobalPrivateLogger != NullPtr);                                \
    g_pGlobalPrivateLogger->SetLogLevel(level);                               \
}                                                                             \

#define SET_Logger(pLog)                                                      \
{                                                                             \
    ASSERT(pLog != NullPtr);                                                  \
    if (g_pGlobalPrivateLogger != NullPtr)                                    \
    {                                                                         \
        delete g_pGlobalPrivateLogger;                                        \
        g_pGlobalPrivateLogger = NullPtr;                                     \
    }                                                                         \
    g_pGlobalPrivateLogger = pLog;                                            \
}                                                                             \

#define INIT_STD_LOG(szFile)                                                  \
    LogWrapper* g_pGlobalPriviteLogWraper = new LogWrapper(szFile);           \

#define INIT_DEF_LOG()                                                        \
    LogWrapper* g_pGlobalPriviteLogWraper = new LogWrapper(NullPtr);          \

#endif /* LOG_H_ */
