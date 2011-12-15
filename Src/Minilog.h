/*
 * File       : Minilog.h
 * Description: 
 * Version    : 2011-11-12 Created
 * Author     : buf1024@gmail.com
 */
 
#ifndef XBASIC_MINILOG_H_
#define XBASIC_MINILOG_H_

#include "XBasicCore.h"

#include "Singleton.h"
#include <string>
#include <stdio.h>


XBASIC_NAMEPACE_BEGIN

#define LOG_DEBUG(...)                                               \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.Debug(__VA_ARGS__);                                         \
}                                                                    \

#define LOG_INFO(...)                                                \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.Info(__VA_ARGS__);                                          \
}                                                                    \

#define LOG_WARN(...)                                                \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.Warn(__VA_ARGS__);                                          \
}                                                                    \

#define LOG_ERROR(...)                                               \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.Error(__VA_ARGS__);                                         \
}                                                                    \

#define LOG_FATAL(...)                                               \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.Fatal(__VA_ARGS__);                                         \
}  

#define SET_FILE_LOG_LEVEL(lvl)                                      \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
    sLog.SetFileLogLevel(Minilog::GetMapLevel(nLvl));                \
}                                                                    \


#define SET_CONSOLE_LOG_LEVEL(lvl)                                   \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.SetConsoleLogLevel(Minilog::GetMapLevel(nLvl));             \
}                                                                    \

#define SET_LOG_LEVEL(lvl)                                          \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
    sLog.SetConsoleLogLevel(Minilog::GetMapLevel(lvl));              \
	sLog.SetFileLogLevel(Minilog::GetMapLevel(lvl));                 \
}                                                                    \


#define SET_LOG_PATH(szPath)                                         \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.SetLogPath(szPath);                                         \
}                                                                    \

#define SET_LOG_FILE_FIXED(szFile)                                   \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.SetLogFile(szFile, false);                                  \
}                                                                    \

#define SET_LOG_FILE(szFile)                                         \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.SetLogFile(szFile);                                         \
}                                                                    \

#define FLUSH_LOG()                                                  \
{                                                                    \
	Minilog& sLog = Minilog::GetInst();                              \
	sLog.FlushLog();                                                 \
}                                                                    \

#define RELEASE_LOG()                                                \
{                                                                    \
	Minilog::ReleaseRC();                                            \
}                                                                    \


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


// 单进程单线程使用，不进行同步操作
class Minilog
	: public Util::Singleton<Minilog>
{
    DECL_SINGLETON(Minilog)
private:
    Minilog();
public:
    ~Minilog();
public:
    void Info(const char* szFormat, ...);
    void Debug(const char* szFormat, ...);
    void Warn(const char* szFormat, ...);
    void Error(const char* szFormat, ...);
    void Fatal(const char* szFormat, ...);
    
    void SetFileLogLevel(LogLevel eLvl);
    LogLevel GetFileLogLevel() const;
    void SetConsoleLogLevel(LogLevel eLvl);
    LogLevel GetConsoleLogLevel() const;

    void SetLogPath(const char* szPath);
    std::string GetLogPath() const;

	void SetLogFile(const char* szFile, bool bAppDate = true);
	std::string GetLogFile() const;

    void FlushLog();

	void LogConsole(LogLevel eLvl, const char* szMsg, int nLen = -1);
	void LogFile(LogLevel eLvl, const char* szMsg, int nLen = -1);

	static LogLevel GetMapLevel(int nLvl);
	static LogLevel GetMapLevel(const char* szLvl);

protected:	
    void LogMessageV(LogLevel eLvl, const char* szFormat, va_list va); 
    std::string GetLogHeader(LogLevel eLvl);

	void SetConsoleColor(LogLevel eLogLevel);

private:
    LogLevel m_eFileLvl;
    LogLevel m_eConsoleLvl;
    
    std::string m_strPath;
	std::string m_strFile;
    FILE* m_pFile;

	static const unsigned int MSG_BUF = 4096;
	char m_szMsgBuf[MSG_BUF];

#ifdef _MSC_VER
	HANDLE m_hStdOut;
#endif
};

XBASIC_NAMESPACE_END
 
#endif /* XBASIC_MINILOG_H_ */


