/*
 * File       : ConsoleAppender.h
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XBASIC_CONSOLEAPPENDER_H_
#define XBASIC_CONSOLEAPPENDER_H_

#include "Appender.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI ConsoleAppender :
    public Appender
{
public:
    ConsoleAppender(void);
    ConsoleAppender(const ConsoleAppender& other);
    virtual ~ConsoleAppender(void);

    virtual unsigned int Write(LogLevel eLogLevel, const char* szMsg, int nLen = -1);
    virtual Appender* Clone();
    virtual bool IsAppenderOK();

    void SetConsoleColor(LogLevel eLogLevel);

private:
#ifdef MSWINDOWS
    HANDLE m_hStdOut;
#endif
};

XBASIC_NAMESPACE_END

#endif /* XBASIC_CONSOLEAPPENDER_H_ */
