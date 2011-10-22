/*
 * File       : FileAppender.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "FileAppender.h"

USE_XBASIC_NAMESPACE

FileAppender::FileAppender(void)

{
    m_strName = "FileAppender";
}
FileAppender::FileAppender(const FileAppender& other)
{
    if (this != &other)
    {
        this->m_strName = other.m_strName;
    }
}
FileAppender::~FileAppender(void)
{
}

unsigned int FileAppender::Write(int nLogLevel, const std::string& strMsg)
{
    return 0;
}
unsigned int FileAppender::Write(int nLogLevel, const char* szMsg, unsigned int nLen)
{
    return 0;
}

Appender* FileAppender::Clone()
{
    return new FileAppender(*this);
}