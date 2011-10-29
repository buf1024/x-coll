/*
 * File       : Log.h
 * Description: 
 * Version    : 2011-10-15 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_LOG_H_
#define XBASIC_LOG_H_

#include "LogLevel.h"
#include "LogFactory.h"
#include "Logger.h"

XBASIC_NAMEPACE_BEGIN

#define LOG_DEBUG(...)                                                        \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->LogMessage(DEBUG, __VA_ARGS__);                                  \
}                                                                             \


#define LOG_INFO(...)                                                         \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->LogMessage(INFO, __VA_ARGS__);                                   \
}                                                                             \


#define LOG_WARN(...)                                                         \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->LogMessage(WARN, __VA_ARGS__);                                   \
}                                                                             \


#define LOG_ERROR(...)                                                        \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->LogMessage(ERR, __VA_ARGS__);                                  \
}                                                                             \


#define LOG_FATAL(...)                                                        \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->LogMessage(FATAL, __VA_ARGS__);                                  \
}                                                                             \


#define SET_LOG_LEVEL(level)                                                  \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    Logger* pLogger = pFactory->GetGlobalLogger();                            \
    ASSERT(pLogger != NullPtr);                                               \
    pLogger->->SetLogLevel(level);                                            \
}                                                                             \


#define SET_LOGGER(pLog)                                                      \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    pFactory->SetGlobalLogger(pLog);                                          \
}                                                                             \


inline Logger* GET_LOGGER()                                                   \
{                                                                             \
    LogFactory* pFactory = LogFactory::GetInst();                             \
    ASSERT(pFactory != NullPtr);                                              \
    return pFactory->GetGlobalLogger();                                       \
} 


#define INIT_STD_LOG(szConfFile)                                              \
    LogWrapper* g_pGlobalPriviteSTDLogWraper =                                \
                    new LogWrapper(StdConf, szConfFile);                      \


#define INIT_CONSOLE_LOG()                                                    \
    LogWrapper* g_pGlobalPriviteConsoleLogWraper =                            \
                    new LogWrapper(Console);                                  \


#define INIT_FILE_LOG(szFile)                                                 \
    LogWrapper* g_pGlobalPriviteFileLogWraper =                               \
                    new LogWrapper(File, szFile);                             \


XBASIC_NAMESPACE_END

#endif /* XBASIC_LOG_H_ */
