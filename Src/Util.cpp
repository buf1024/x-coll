/*
 * File       : Util.h
 * Description: 
 * Version    : 2011-12-6 Created
 * Author     : buf1024@gmail.com
 */

#include "Util.h"
#include "StdString.h"
#if _MSC_VER
#include "shlobj.h"
#else
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#endif


#if _MSC_VER
#pragma comment(lib, "shell32.lib")
#endif

XBASIC_NAMEPACE_BEGIN

namespace Util
{

long IsAppInstRuning(const char* szAppID)
{
    std::string strAppID;
    std::string strPath;
    if (szAppID == NullPtr || szAppID[0] == '\0')
    {
        ASSERT(false);
        szAppID = ".dummy";
    }
    else
    {
        strAppID = szAppID;
    }
    
#ifdef _MSC_VER
    char szPath[MAX_PATH] = "";
    if(SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA|CSIDL_FLAG_CREATE,
        NULL, 0, szPath))){
        strPath = szPath;
    }
    if (strPath.empty())
    {
        strPath = ".";
    }    
    strPath.append("\\.");
#else
    char* szPath = getenv("HOME");
    if (szPath != NullPtr)
    {
        strPath = szPath;
    }
    if (strPath.empty())
    {
        strPath = ".";
    }    
    strPath.append("/.");
#endif
    strPath.append(szAppID);

    bool bRunning = false;
    long lFilePID = 0;

    FILE* pFile = fopen(strPath.c_str(), "r+");
    if (pFile != NullPtr)
    {
        fread(&lFilePID, sizeof(lFilePID), 1, pFile);

        if (lFilePID != -1)
        {
#ifdef _MSC_VER
            HANDLE hProcess = OpenProcess(STANDARD_RIGHTS_READ, FALSE, lFilePID);
            if (hProcess == NullPtr)
            {
                if (GetLastError() == 0x5) // 进程存在，拒绝访问
                {
                    bRunning = true;
                }
            }else{
                bRunning = true;
                CloseHandle(hProcess);
            }


#else
            if(kill((pid_t)lFilePID, 0) == 0){
                bRunning = true;
            }
#endif    
            if (bRunning)
            {
                fclose(pFile);
            }
            
        }
     
    }else{
        pFile = fopen(strPath.c_str(), "w");
    }

    if (!bRunning)
    {
#ifdef _MSC_VER
        lFilePID = GetCurrentProcessId();
#else
        lFilePID = getpid();
#endif
        fseek(pFile, 0, SEEK_SET);
        fwrite(&lFilePID, sizeof(lFilePID), 1, pFile);
        fclose(pFile);
    }
    return lFilePID;
}

}

XBASIC_NAMESPACE_END
