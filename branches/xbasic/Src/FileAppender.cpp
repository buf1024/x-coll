/*
 * File       : FileAppender.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "FileAppender.h"

#include "IniConfig.h"
#include "XmlConfig.h"

#define FILE_PATH "Path"
#define FILE_MODE "Mode"

#define WRITE_BUF 2048

USE_XBASIC_NAMESPACE

FileAppender::FileAppender(void)

{
    m_strName = "FileAppender";
    m_strMode = "w";
    m_pFile = NullPtr;
}
FileAppender::FileAppender(const FileAppender& other)
{
    if (this != &other)
    {
        this->m_strName = other.m_strName;
        this->m_strPath = other.m_strPath;
        this->m_strMode = other.m_strMode;
        this->m_pFile = other.m_pFile;
        if(other.m_pFile != NullPtr){
            //重新打开
            m_pFile = fopen(m_strPath.c_str(), m_strMode.c_str());
        }
    }
}
FileAppender::~FileAppender(void)
{
    if (m_pFile != NullPtr)
    {
        fflush(m_pFile);
        fclose(m_pFile);
    }
}

unsigned int FileAppender::Write(LogLevel eLogLevel, const char* szMsg, int nLen)
{
    unsigned int uRet = 0;
    UnRefParam(eLogLevel);

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
        uRet += fwrite(szMsg + uIndex, sizeof(char), nCount, m_pFile);
        uIndex += nCount;
        nLen -= nCount;
        nCount = nLen;
    }

    return uRet;
}

Appender* FileAppender::Clone()
{
    return new FileAppender(*this);
}

void FileAppender::Init(const char* szConf)
{
    m_strMode = "w";
    m_strPath = szConf;
    SetFile(m_strPath, m_strMode);
}
void FileAppender::Init(Section* pSec)
{
    ASSERT(pSec != NullPtr);

    std::string strPath;
    pSec->GetValue(FILE_PATH, strPath);
    std::string strMode;
    pSec->GetValue(FILE_MODE, strMode, "w");

    SetFile(strPath, strMode);
}
void FileAppender::Init(Config* pConf)
{
    ASSERT(pConf != NullPtr);

    std::string strPath;
    pConf->GetString(FILE_PATH, strPath);
    std::string strMode;
    pConf->GetString(FILE_MODE, strMode, "w");
    std::string strTmp = StdString::ToLower(strMode);
    if ( strTmp == "write")
    {
        strMode = "w";
    }
    else if (strTmp == "append")
    {
        strMode = "a+";
    }

    SetFile(strPath, strMode);
}

void FileAppender::SetFile(std::string strPath, std::string strMode)
{
    m_strPath = strPath;
    m_strMode = strMode;
    if (m_pFile != NullPtr)
    {
        fflush(m_pFile);
        fclose(m_pFile);        
    }
    m_pFile = fopen(m_strPath.c_str(), m_strMode.c_str());
}

std::string FileAppender::GetPath() const
{
    return m_strPath;
}
std::string FileAppender::GetMode() const
{
    return m_strMode;
}

bool FileAppender::IsAppenderOK()
{
    return m_pFile != NullPtr;
}
