/*
 * File       : FileAppender.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#ifndef FILEAPPENDER_H_
#define FILEAPPENDER_H_

#include "Appender.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI FileAppender :
    public Appender
{
public:
    FileAppender(void);
    FileAppender(const FileAppender& other);
    virtual ~FileAppender(void);

    virtual unsigned int Write(LogLevel eLogLevel, const std::string& strMsg);
    virtual unsigned int Write(LogLevel eLogLevel, const char* szMsg, int nLen = -1);
    virtual Appender* Clone();
};

XBASIC_NAMESPACE_END

#endif /* FILEAPPENDER_H_ */