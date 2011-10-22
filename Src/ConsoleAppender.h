/*
 * File       : ConsoleAppender.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#ifndef CONSOLEAPPENDER_H_
#define CONSOLEAPPENDER_H_

#include "Appender.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI ConsoleAppender :
    public Appender
{
public:
    ConsoleAppender(void);
    ConsoleAppender(const ConsoleAppender& other);
    virtual ~ConsoleAppender(void);

    virtual unsigned int Write(int nLogLevel, const std::string& strMsg);
    virtual unsigned int Write(int nLogLevel, const char* szMsg, unsigned int nLen = -1);
    virtual Appender* Clone();
};

XBASIC_NAMESPACE_END

#endif /* CONSOLEAPPENDER_H_ */
