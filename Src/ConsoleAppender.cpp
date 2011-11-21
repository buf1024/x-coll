/*
 * File       : ConsoleAppender.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "ConsoleAppender.h"

USE_XBASIC_NAMESPACE

ConsoleAppender::ConsoleAppender(void)
{
    m_strName = "ConsoleAppender";

#ifdef _MSC_VER
    m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}
ConsoleAppender::ConsoleAppender(const ConsoleAppender& other)
{
    if (this != &other)
    {
        this->m_strName = other.m_strName;
#ifdef _MSC_VER
        m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    }
}
ConsoleAppender::~ConsoleAppender(void)
{
#ifdef _MSC_VER
    CloseHandle(m_hStdOut);
#endif
}

unsigned int ConsoleAppender::Write(LogLevel eLogLevel, const char* szMsg, int nLen)
{
    unsigned int uRet = 0;
    if (szMsg)
    {
        if(nLen < 0) nLen = strlen(szMsg);
#ifdef _MSC_VER

        CONSOLE_SCREEN_BUFFER_INFO csbi = {sizeof(csbi)};
        GetConsoleScreenBufferInfo(
            m_hStdOut, &csbi);
        WORD wAtt = csbi.wAttributes;
        SetConsoleColor(eLogLevel);        
        DWORD dwReal;
        WriteConsoleA(m_hStdOut, szMsg, nLen, &dwReal, NULL);
        SetConsoleTextAttribute(m_hStdOut, wAtt);
        uRet = (unsigned int)dwReal;
#else
        SetConsoleColor(eLogLevel);
        uRet = printf("%s", szMsg);
        printf("\033[0m");
#endif
    }
    return uRet;
}

void ConsoleAppender::SetConsoleColor(LogLevel eLogLevel)
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
    printf("%s");
#endif

}

Appender* ConsoleAppender::Clone()
{
    return new ConsoleAppender(*this);
}

bool ConsoleAppender::IsAppenderOK()
{
    return true;
}
