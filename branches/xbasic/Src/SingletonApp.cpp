/*
 * File       : SigntonApp.h
 * Description: ȷ��Ӧ�ó���ֻ����һ��
 *              ���ӣ�
 *               ��main���������������ƵĴ���
 *                SingletonApp inst;
 *                if(!inst) //Not Singleton
 *                {
 *                   ... //Do other things
 *                }
 * Version    : 2011-02-11 Created
 *              2010-9-26 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */

#include "SingletonApp.h"

#ifdef MSWINDOWS
#include <direct.h>
#endif

USE_XBASIC_NAMESPACE

SingletonApp::SingletonApp(const std::string strName)
: m_pFile(NullPtr)
{
    std::string strFile = strName;
    if (strFile.empty())
    {
        char szMaxPath[BUF_SIZE] = "";
#if MSWINDOWS
        strFile = _getcwd(szMaxPath, BUF_SIZE - 1);
#else
        strFile = getcwd(szMaxPath, BUF_SIZE - 1);
#endif
    }

    strFile = StdString::Replace(strFile.c_str(), "\\", "_");
    strFile = StdString::Replace(strFile.c_str(), "/", "_");
    strFile.append(".pid");


    m_pFile = fopen(strFile.c_str(), "w");

    if(m_pFile == NullPtr)
    {
        m_bInstNotExist = false;
    }
    else
    {
        char szLine[BUF_SIZE] = "";
        unsigned long lPid = 0;

#if MSWINDOWS
        lPid = GetCurrentProcessId();
        _snprintf(szLine, BUF_SIZE, "%ld", lPid);
#else
        lPid = getpid();
        snprintf(szLine, BUF_SIZE, "%ld", lPid);
#endif



        std::string strBuf = szLine;

        fwrite(strBuf.c_str(), sizeof(char), strBuf.length(), m_pFile);

        m_bInstNotExist = true;
    }
}

SingletonApp::~SingletonApp(void)
{
	if (m_pFile)
	{
        fclose(m_pFile);
	}
}

bool SingletonApp::operator == (bool bCmp)
{
	return m_bInstNotExist;
}
bool SingletonApp::operator != (bool bCmp)
{
	return !m_bInstNotExist;
}
bool SingletonApp::operator ! ()
{
	return !m_bInstNotExist;
}
SingletonApp::operator bool ()
{
	return m_bInstNotExist;
}
