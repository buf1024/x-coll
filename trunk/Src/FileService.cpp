////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : FileService.cpp
// Purpose     : This file is copy and modify from Kinksoft safeguard Open source
// Version     : 2011-06-07 (11:40) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "FileService.h"

#include <Shlwapi.h>

#pragma comment(lib, "Version.lib")

BOOL GetFileVersion( LPCTSTR szPath, LARGE_INTEGER &lgVersion )
{   
    if( szPath == NULL)
        return FALSE;

    DWORD dwHandle;
    UINT  cb;
    cb = GetFileVersionInfoSize( szPath, &dwHandle );
    if (cb > 0)
    {
        BYTE* pFileVersionBuffer = new BYTE[cb];
        if( pFileVersionBuffer == NULL )
            return FALSE;

        if (GetFileVersionInfo( szPath, 0, cb, pFileVersionBuffer))
        {
            VS_FIXEDFILEINFO* pVersion = NULL;
            if (VerQueryValue(pFileVersionBuffer, TEXT("\\"), (VOID**)&pVersion, &cb) && 
                pVersion != NULL) 
            {
                lgVersion.HighPart = pVersion->dwFileVersionMS;
                lgVersion.LowPart  = pVersion->dwFileVersionLS;
                delete[] pFileVersionBuffer;
                return TRUE;
            }
        }

        delete[] pFileVersionBuffer;
    }
    return FALSE;
}
BOOL IsFileExist(LPCTSTR pszFile)
{
    BOOL bRet = FALSE;
    if( pszFile == NULL || pszFile[0] == 0)
        return bRet;

    WIN32_FIND_DATA fd = {0};
    HANDLE hFile = FindFirstFile(pszFile, &fd);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFile);
        if( !(fd.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY) )
            bRet = TRUE;
    }
    return bRet;
}

BOOL IsDirExist(LPCTSTR pszFile)
{
    BOOL bRet = FALSE;
    if( pszFile == NULL || pszFile[0] == 0)
        return bRet;

    WIN32_FIND_DATA fd = {0};
    HANDLE hFile = FindFirstFile(pszFile, &fd);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFile);
        if( fd.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY )
            bRet = TRUE;
    }
    return bRet;
}

BOOL MyMoveFile(LPCTSTR lpszFileFrom, LPCTSTR lpszFileto)
{
    if( !PathFileExists(lpszFileFrom) )
        return FALSE;
    if( PathFileExists(lpszFileto) )
        SetFileAttributes(lpszFileto, FILE_ATTRIBUTE_NORMAL);

    DWORD dwFlags = GetFileAttributes( lpszFileFrom );
    SetFileAttributes(lpszFileFrom, FILE_ATTRIBUTE_NORMAL);
    BOOL bRet = MoveFileEx(lpszFileFrom, lpszFileto, MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
    if(bRet)
        SetFileAttributes(lpszFileto, dwFlags);
    return bRet;
}

BOOL IsFileUsing(LPCTSTR szFilename)
{
    if( !PathFileExists(szFilename) )
        return FALSE;

    DWORD dwFlags = GetFileAttributes( szFilename );
    SetFileAttributes(szFilename, FILE_ATTRIBUTE_NORMAL);

    HANDLE hfile = CreateFile(szFilename, GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0); 
    BOOL bRet = TRUE;
    if(hfile!=INVALID_HANDLE_VALUE)
    {
        CloseHandle( hfile );
        bRet = FALSE;
    }	
    SetFileAttributes(szFilename, dwFlags);
    return bRet;
}
BOOL GetFileContents( LPCTSTR lpszFilename, BYTE* pCont)
{
    HANDLE hFile = ::CreateFile(lpszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    BOOL bRet = FALSE;
    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
    if (hMapping != INVALID_HANDLE_VALUE)
    {
        PBYTE pByte = (PBYTE)MapViewOfFile(hMapping, FILE_MAP_COPY, 0, 0, 0);
        UINT64 size = MyGetFileSize(lpszFilename);	
        //less than 4GB
        memcpy(pCont, pByte, (size_t)size);
        UnmapViewOfFile(pByte);
        CloseHandle(hMapping);
        bRet = TRUE;
    }
    CloseHandle(hFile);

    return bRet;
}

BOOL PutFileContents(LPCTSTR lpszFilename, BYTE *pBuffer, INT nLen)
{
    if(pBuffer == NULL) return FALSE;
    HANDLE hFile = CreateFile(lpszFilename, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
        NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    DWORD dwReal = 0L;
    DWORD idx = 0;
    BOOL bRet = FALSE;
    while(TRUE)
    {
        bRet = WriteFile(hFile, pBuffer + idx, nLen, &dwReal, NULL);
        if (bRet)
        {
            if (dwReal == nLen)
            {
                break;
            }
            else
            {
                nLen -= dwReal;
                idx += dwReal;
            }
        }
        else
        {
            break;
        }
    }
    CloseHandle(hFile);
    return bRet;
}

INT64 MyGetFileSize(LPCTSTR lpszFilename)
{
    HANDLE hFile = ::CreateFile(lpszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    DWORD dwHigh = 0L;
    DWORD dwLow  = 0L;
    dwLow = ::GetFileSize(hFile, &dwHigh);
    CloseHandle(hFile);
    
    return (INT64)dwHigh << 32 | dwLow;
}

INT64 GetFolderSize(LPCTSTR szFolder)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    TCHAR strFolder[MAX_PATH] = {0};
    lstrcpy(strFolder, szFolder);
    lstrcat(strFolder, _T("\\*"));
    INT64 folderSize = 0;
    hFind = FindFirstFile(strFolder, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE) 
    {
        do 
        {
            if( _tcsicmp(_T("."), FindFileData.cFileName)==0 
                || _tcsicmp(_T(".."), FindFileData.cFileName)==0 )
            {
                continue;
            }
            if( FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
            {
                TCHAR strResult[MAX_PATH] = {0};
                lstrcpy(strResult, szFolder);
                LPCTSTR pszResult;
                LPCTSTR pchLast;
                pszResult = strResult;
                pchLast = _tcsdec( pszResult, pszResult+lstrlen(strResult) );
                if ((*pchLast != _T('\\')) && (*pchLast != _T('/')))
                    lstrcat(strResult, _T("\\"));
                lstrcat(strResult, FindFileData.cFileName);

                folderSize += GetFolderSize( strResult );
            }
            else
            {
                ULARGE_INTEGER nFileSize;
                nFileSize.LowPart = FindFileData.nFileSizeLow;
                nFileSize.HighPart = FindFileData.nFileSizeHigh;
                folderSize += nFileSize.QuadPart;
            }

        } while (FindNextFile(hFind, &FindFileData) != 0);
        FindClose(hFind);
    }
    return folderSize;
}

BOOL CreateDirectoryNested( LPCTSTR  lpszDir )
{
    if( ::PathIsDirectory( lpszDir ) ) 
        return TRUE;

    if(_tcslen(lpszDir)>=MAX_PATH)
        return FALSE;

    TCHAR   szPreDir[ MAX_PATH ];
    _tcscpy_s( szPreDir, lpszDir );
    //确保路径末尾没有反斜杠
    TCHAR *pend = szPreDir + lstrlen(szPreDir) - 1;
    if(*pend==_T('/')|| *pend==_T('\\'))
    {
        *pend = _T('\0');
    }

    //获取上级目录
    BOOL  bGetPreDir  = ::PathRemoveFileSpec( szPreDir );
    if( !bGetPreDir ) return FALSE;

    //如果上级目录不存在,则递归创建上级目录
    if( !::PathIsDirectory( szPreDir ) )
    {
        CreateDirectoryNested( szPreDir );
    }

    return ::CreateDirectory( lpszDir, NULL );
}

BOOL CreateDirs (LPCTSTR lpFileName)
{
    TCHAR lpNameCopy[MAX_PATH] = {0};
    lstrcpy(lpNameCopy, lpFileName);

    TCHAR *pend = lpNameCopy + lstrlen(lpNameCopy);
    while( pend>lpNameCopy )
    {
        if(*pend==_T('/')|| *pend==_T('\\'))
        {
            *pend = _T('\0');
            break;
        }
        --pend;
    }
    return CreateDirectoryNested (lpNameCopy);
}
