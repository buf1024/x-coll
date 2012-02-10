/*
 * File       : Minilog.h
 * Description: 
 * Version    : 2011-11-12 Created
 * Author     : buf1024@gmail.com
 */
#include "Minilog.h"
#include "StdString.h"
#include <time.h>
#include <map>
#include <stdarg.h>
#ifdef _MSC_VER
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#endif


USE_XBASIC_NAMESPACE;


#define MAX_PATH_LEN 256
#define WRITE_BUF 1024

Minilog::Minilog()
: m_eFileLvl(ALL)
, m_eConsoleLvl(ALL)
, m_pFile(NULL)
{
	memset(m_szMsgBuf, 0, MSG_BUF);

#ifdef _MSC_VER
	m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif

}

Minilog::~Minilog()
{
	if (m_pFile != NullPtr)
	{
		fflush(m_pFile);
		fclose(m_pFile);
		m_pFile = NullPtr;
	}
#ifdef _MSC_VER
	CloseHandle(m_hStdOut);
#endif
}
void Minilog::Info(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(INFO, szFormat, va);
    va_end(va);
}
void Minilog::Debug(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(DEBUG, szFormat, va);
    va_end(va);
}
void Minilog::Warn(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(WARN, szFormat, va);
    va_end(va);
}
void Minilog::Error(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(ERR, szFormat, va);
    va_end(va);
}
void Minilog::Fatal(const char* szFormat, ...)
{
    va_list va;
    va_start(va, szFormat);
    LogMessageV(FATAL, szFormat, va);
    va_end(va);
}

void Minilog::SetFileLogLevel(LogLevel eLvl)
{
    m_eFileLvl = eLvl;
}
LogLevel Minilog::GetFileLogLevel() const
{
    return m_eFileLvl;
}
void Minilog::SetConsoleLogLevel(LogLevel eLvl)
{
    m_eConsoleLvl = eLvl;
}
LogLevel Minilog::GetConsoleLogLevel() const
{
    return m_eConsoleLvl;
}

void Minilog::SetLogPath(const char* szPath)
{
	char szCur[MAX_PATH_LEN] = "";
	if (szPath == NullPtr || szPath[0] == '\0')
	{
#ifdef _MSC_VER
		_getcwd(szCur, MAX_PATH_LEN);
#else
		getcwd(szCur, MAX_PATH_LEN);
#endif
	}
	else
	{
		int nRet = -1;
#ifdef _MSC_VER
		nRet = _access(szPath, 04); //Read
#else
		nRet = access(szPath, 04); //Read
#endif
		if (nRet == -1)
		{
#ifdef _MSC_VER
			_getcwd(szCur, MAX_PATH_LEN);
#else
			getcwd(szCur, MAX_PATH_LEN);
#endif
		}
		else
		{
			strcpy(szCur, szPath);
		}
	}
	int nLen = strlen(szCur);
	if (szCur[nLen - 1] == '/' || szCur[nLen - 1] == '\\')
	{
		szCur[nLen - 1] = '\0';
	}
	m_strPath = szCur;    
}
std::string Minilog::GetLogPath() const
{
    return m_strPath;
}

void Minilog::SetLogFile(const char* szFile, bool bAppDate)
{
	if (szFile != NullPtr)
	{
		m_strFile = szFile;
	}
	
	time_t t;
	time(&t);
	struct tm * pTm = localtime(&t);
	char szBuf[BUF_SIZE] = "";
#ifdef _MSC_VER
	_snprintf(szBuf, BUF_SIZE, "%04d%02d%02d%02d%02d%02d", pTm->tm_year + 1900,
		pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
#else
	snprintf(szBuf, BUF_SIZE, "%04d%02d%02d%02d%02d%02d", pTm->tm_year + 1900,
		pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
#endif
	if (m_strFile.empty())
	{
		m_strFile = szBuf;
	}
	else
	{
		if (bAppDate)
		{
			m_strFile = m_strFile + "_";
			m_strFile = m_strFile + szBuf;
		}		
	}
	if (m_pFile != NullPtr)
	{
		fflush(m_pFile);
		fclose(m_pFile);
	}
	std::string strFile = m_strPath;
#ifdef _MSC_VER
	strFile += "\\";
#else
	strFile += "/";
#endif
	strFile += m_strFile;

	m_pFile = fopen(strFile.c_str(), "w");
	ASSERT(m_pFile != NullPtr);
}
std::string Minilog::GetLogFile() const
{
	return m_strFile;
}

void Minilog::FlushLog()
{
	if(m_pFile)
	{
		fflush(m_pFile);
	}
}


void Minilog::LogConsole(LogLevel eLvl, const char* szMsg, int nLen)
{
	if (eLvl >= m_eConsoleLvl)
	{
		if (szMsg != NullPtr && szMsg[0] != '\0')
		{
			std::string strHeader = GetLogHeader(eLvl);
			if(nLen < 0) nLen = strlen(szMsg);
#ifdef _MSC_VER
			CONSOLE_SCREEN_BUFFER_INFO csbi = {sizeof(csbi)};
			GetConsoleScreenBufferInfo(
				m_hStdOut, &csbi);
			WORD wAtt = csbi.wAttributes;
			SetConsoleColor(eLvl);        
			DWORD dwReal;
			WriteConsoleA(m_hStdOut, strHeader.c_str(), strHeader.length(), &dwReal, NULL);
			WriteConsoleA(m_hStdOut, szMsg, nLen, &dwReal, NULL);
			SetConsoleTextAttribute(m_hStdOut, wAtt);
#else
			SetConsoleColor(eLvl);
			printf("%s", strHeader.c_str());
			printf("%s", szMsg);
			printf("\033[0m");
#endif
		}
	}
}
void Minilog::LogFile(LogLevel eLvl, const char* szMsg, int nLen)
{
	if (eLvl >= m_eFileLvl)
	{
		if (m_pFile != NullPtr)
		{
			std::string strHeader = GetLogHeader(eLvl);
			fwrite(strHeader.c_str(), sizeof(char), strHeader.length(), m_pFile);
			if (nLen < 0)
			{
				nLen = strlen(szMsg);
			}

			int nCount = nLen;
			size_t uIndex = 0;
			while(nLen > 0){
				if (nLen > WRITE_BUF)
				{
					nCount = WRITE_BUF;
				}
				fwrite(szMsg + uIndex, sizeof(char), nCount, m_pFile);
				uIndex += nCount;
				nLen -= nCount;
				nCount = nLen;
			}
		}
		else
		{
			ASSERT(false);
		}
	}
}
void Minilog::LogMessageV(LogLevel eLvl, const char* szFormat, va_list va)
{
	if (eLvl >= m_eConsoleLvl || eLvl >= m_eFileLvl)
	{
		if (vsnprintf(m_szMsgBuf, MSG_BUF, szFormat, va) < 0)
		{
			Fatal("Logger Buffer too Small");
			return;
		}
	}
	if (eLvl >= m_eConsoleLvl)
	{
		LogConsole(eLvl, m_szMsgBuf);
	}
	if (eLvl >= m_eFileLvl)
	{
		LogFile(eLvl, m_szMsgBuf);
	}
}
std::string Minilog::GetLogHeader(LogLevel eLvl)
{
    std::string strRet;
    switch(eLvl)
    {
    case DEBUG:
        strRet += "[D]";
        break;
    case INFO:
        strRet += "[I]";
        break;
    case WARN:
        strRet += "[W]";
        break;
    case ERR:
        strRet += "[E]";
        break;
    case FATAL:
        strRet += "[F]";
        break;
    default:
        break;
    }
    strRet += "[";
    strRet += StdString::FromNumber((long)time(0));
    strRet += "] ";
    return strRet;
}


void Minilog::SetConsoleColor(LogLevel eLogLevel)
{
#ifdef _MSC_VER
	WORD dwTextAttr = FOREGROUND_BLUE | FOREGROUND_GREEN |
		FOREGROUND_RED | FOREGROUND_INTENSITY;
	switch(eLogLevel)
	{
	case FATAL:
		dwTextAttr = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case ERR:
		dwTextAttr = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case WARN:
		dwTextAttr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case INFO:
		dwTextAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case DEBUG:
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(m_hStdOut, dwTextAttr);
#else
	char szBuf[32] = "\033[0m";
	switch(eLogLevel)
	{
	case FATAL:
		strcpy(szBuf, "\033[1;31m");
		break;
	case ERR:
		strcpy(szBuf, "\033[1;35m");
		break;
	case WARN:
		strcpy(szBuf, "\033[1;34m");
		break;
	case INFO:
		strcpy(szBuf, "\033[1;33m");
		break;
	case DEBUG:
		break;
	default:
		break;
	}
	printf("%s", szBuf);
#endif

}


LogLevel Minilog::GetMapLevel(int nLvl)
{
	if (nLvl <100)
	{
		return ALL;
	}
	if (nLvl >= 100 && nLvl < 200)
	{
		return DEBUG;
	}
	if (nLvl >= 200 && nLvl < 300)
	{
		return INFO;
	}
	if (nLvl >= 300 && nLvl < 400)
	{
		return WARN;
	}
	if (nLvl >= 400 && nLvl < 500)
	{
		return ERR;
	}
	if (nLvl >= 500 && nLvl < 600)
	{
		return FATAL;
	}
	return OFF;
}
LogLevel Minilog::GetMapLevel(const char* szLvl)
{
	struct _StrLvl
	{
		const char* szStr;
		LogLevel eLvl;
	};

	static _StrLvl strLvlMap [] = {
		{"ALL", ALL},
		{"DEBUG", DEBUG},
		{"INFO", INFO},
		{"WARN", WARN},
		{"ERROR", ERR},
		{"FATAL", FATAL},
		{"OFF", OFF}
	};

	if (szLvl == NullPtr)
	{
		return ALL;
	}

	for (unsigned i=0; i<sizeof(strLvlMap); i++)
	{
#ifdef _MSC_VER
		if (stricmp(szLvl, strLvlMap[i].szStr) == 0)
#else
		if (strcasecmp(szLvl, strLvlMap[i].szStr) == 0)
#endif
		{
			return strLvlMap[i].eLvl;
		}
	}
	ASSERT(false);
	return ALL;
}
