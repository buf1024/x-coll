#include "StdAfx.h"
#include "FileServiceTest.h"
#include <FileService.h>
#include <StdString.h>

#pragma warning(disable:4996)

FileServieTest::FileServieTest()
{
}
FileServieTest::~FileServieTest()
{
}

void FileServieTest::setup()
{

}
void FileServieTest::tearDown()
{

}

void FileServieTest::testFile()
{
    TCHAR* pTmp = _tgetenv(_T("Temp"));
    CPPUNIT_ASSERT(IsDirExist(pTmp) == TRUE);
    CPPUNIT_ASSERT(IsDirExist(NULL) == FALSE);
    CPPUNIT_ASSERT(IsDirExist(_T("t:\\a\\a\\a\\a\\a\\a\\a\\a")) == FALSE);

    pTmp = _ttempnam(pTmp, _T("lgc"));
    StdString strPath = pTmp;
    if (pTmp)
    {
        free(pTmp);
    }
    HANDLE hFile = CreateFile(strPath.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {

        CPPUNIT_ASSERT(IsFileExist(strPath.c_str()) == TRUE);
        CPPUNIT_ASSERT(IsFileExist(_T("e:\\a\\a\\aa\\a")) == FALSE);

        CPPUNIT_ASSERT(IsFileUsing(strPath.c_str()) == TRUE);

        CloseHandle(hFile);
        CPPUNIT_ASSERT(IsFileUsing(strPath.c_str()) == FALSE);

        TCHAR szMsg[] = _T("Hello world!!");
        PutFileContents(strPath.c_str(), (BYTE*)szMsg, lstrlen(szMsg)*sizeof(TCHAR));
        TCHAR szRead[64] = {0};
        GetFileContents(strPath.c_str(), (BYTE*)szRead);
        CPPUNIT_ASSERT(lstrcmp(szRead, szMsg) == 0);
      
        //pTmp = _tgetenv(_T("Temp"));
        //StdString strTmp = pTmp;
        //strTmp += _T("\\asdf\\asdf\\asdf\\adsf");
        //CPPUNIT_ASSERT(CreateDirectoryNested(strTmp.c_str()));
        //MyMoveFile(strPath.c_str(), strTmp.c_str());
        //
        //size_t idx = strPath.rfind(_T('\\'));
        //StdString strFile = strPath.substr(idx + 1);

        //strTmp += _T('\\');
        //strTmp += strFile;
        //CPPUNIT_ASSERT(IsFileExist(strTmp.c_str()) == TRUE);
    }
    else
    {
        CPPUNIT_ASSERT(FALSE);
    }

}
void FileServieTest::testDir()
{
    TCHAR* pTmp = _tgetenv(_T("Temp"));
    TCHAR szBuf[MAX_PATH] = {0};
    TCHAR szFile[MAX_PATH] = {0};

    lstrcpy(szBuf, pTmp);
    lstrcat(szBuf, _T("\\"));
    lstrcat(szBuf, _T("Hello\\World"));

    lstrcpy(szFile, szBuf);
    lstrcat(szFile, _T("\\a.ini"));

    BOOL bRet = FALSE;
    bRet = CreateDirs(szFile);
    CPPUNIT_ASSERT(bRet);
    CPPUNIT_ASSERT(PathFileExists(szBuf));
}


CPPUNIT_TEST_SUITE_REGISTRATION(FileServieTest);