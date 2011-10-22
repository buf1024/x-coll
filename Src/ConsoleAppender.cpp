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
}
ConsoleAppender::ConsoleAppender(const ConsoleAppender& other)
{
    if (this != &other)
    {
        this->m_strName = other.m_strName;
    }
}
ConsoleAppender::~ConsoleAppender(void)
{
}

unsigned int ConsoleAppender::Write(int nLogLevel, const std::string& strMsg)
{
    return 0;
}
unsigned int ConsoleAppender::Write(int nLogLevel, const char* szMsg, unsigned int nLen)
{
    
    return printf("%s", szMsg);
}
Appender* ConsoleAppender::Clone()
{
    return new ConsoleAppender(*this);
}