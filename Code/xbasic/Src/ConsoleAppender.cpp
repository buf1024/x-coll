/*
 * File       : ConsoleAppender.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "ConsoleAppender.h"

USE_XBASIC_NAMESPACE;

ConsoleAppender::ConsoleAppender(void)
{
}

ConsoleAppender::~ConsoleAppender(void)
{
}

unsigned int ConsoleAppender::Write(int nLogLevel, const StdString& strMsg)
{
    return 0;
}
unsigned int ConsoleAppender::Write(int nLogLevel, const StdChar* szMsg, unsigned int nLen)
{
    return 0;
}
