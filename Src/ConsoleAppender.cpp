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
    return 0;
}
Appender* ConsoleAppender::Clone()
{
    return NullPtr;
}