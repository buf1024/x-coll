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

    virtual unsigned int Write(LogLevel eLogLevel, const char* szMsg, int nLen = -1);
    virtual Appender* Clone();
    virtual bool IsAppenderOK();

    virtual void Init(const char* szConf);
    virtual void Init(Section* pSec);
    virtual void Init(Config* pConf);

    void SetFile(std::string strPath, std::string strMode);

    std::string GetPath() const;
    std::string GetMode() const;

private:
    std::string m_strPath;
    std::string m_strMode;
    FILE* m_pFile;

};

XBASIC_NAMESPACE_END

#endif /* FILEAPPENDER_H_ */
