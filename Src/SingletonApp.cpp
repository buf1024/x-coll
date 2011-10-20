/*
 * File       : SigntonApp.h
 * Description: 确保应用程序只启动一次
 *              例子：
 *               在main函数里，添加以下类似的代码
 *                SingletonApp inst;
 *                if(!inst) //Not Singleton
 *                {
 *                   ... //Do other things
 *                }
 * Version    : 2011-02-11 Created
 *              2010-9-26 多操作系统支持
 * Author     : buf1024@gmail.com
 */

#include "SingletonApp.h"
#include <direct.h>


#ifdef WINDOWS
#pragma warning(disable:4996)
#endif

USE_XBASIC_NAMESPACE;

SingletonApp::SingletonApp(const StdString strName)
: m_pFile(NullPtr)
{
    StdString strFile = strName;
    if (strFile.empty())
    {
        StdChar szMaxPath[BUF_SIZE] = _T("");
#if WINDOWS
#ifdef _UNICODE
        strFile = _wgetcwd(szMaxPath, BUF_SIZE - 1);
#else
        strFile = _getcwd(szMaxPath, BUF_SIZE - 1);
#endif
#else
        strFile = getcwd(szMaxPath, BUF_SIZE - 1);
#endif
    }

    strFile = Replace(strFile.c_str(), _T("\\"), _T("_"));
    strFile = Replace(strFile.c_str(), _T("/"), _T("_"));
    strFile.append(_T(".pid"));

#ifndef _UNICODE
    m_pFile = fopen(strFile.c_str(), _T("w"));
#else
    m_pFile = _wfopen(strFile.c_str(), _T("w"));
#endif

    if(m_pFile == NullPtr)
    {
        m_bInstNotExist = false;
    }
    else
    {
        StdChar szLine[BUF_SIZE] = _T("");
        unsigned long lPid = 0;

#if WINDOWS
        lPid = GetCurrentProcessId();
#if _UNICODE
        _snwprintf_s(szLine, BUF_SIZE, BUF_SIZE, _T("%ld"), lPid);
#else
        _snprintf(szLine, BUF_SIZE, _T("%ld"), lPid);
#endif
#else
        lPid = getpid();
        snprintf(szLine, BUF_SIZE, _T("%ld"), lPid);
#endif



        std::string strBuf;
#ifdef WINDOWS
        strBuf = GetAnsiString(szLine);
#else
        strBuf = strLine;
#endif
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
