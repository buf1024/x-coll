#include "ServiceCtrl.h"

static ServiceEntryCallback g_lpServiceEntry             = NULL;
static ServiceMainCallback g_lpServiceMain               = NULL;
static ServiceControlCallback g_lpServiceCtrl            = NULL;
static ServiceNameCallback g_lpServiceName               = NULL;
static ServiceTypeCallback g_lpServiceType               = NULL;
static ServiceDescriptionCallback g_lpServiceDescription = NULL;

static void WINAPI StupidServiceMain(DWORD dwArgc,
                                     LPTSTR* lpszArgv);
static DWORD WINAPI StupidCtrlHandlerEx(DWORD dwControl,
                                        DWORD dwEventType,
                                        LPVOID lpEventData,
                                        LPVOID lpContext);

void SetServiceEntryCallback(ServiceEntryCallback lpCallback)
{
    g_lpServiceEntry = lpCallback;
}
void SetServiceMainCallback(ServiceMainCallback lpMainCallback, 
                            ServiceControlCallback lpCtrlCallback)
{
    g_lpServiceMain = lpMainCallback;
    g_lpServiceCtrl = lpCtrlCallback;
}

void SetServiceNameCallback(ServiceNameCallback lpCallback)
{
    g_lpServiceName = lpCallback;
}

void SetServiceTypeCallback(ServiceTypeCallback lpCallback)
{
    g_lpServiceType = lpCallback;
}

void SetServiceDescriptionCallback(ServiceDescriptionCallback lpCallback)
{
    g_lpServiceDescription = lpCallback;
}


int ServiceInstall()
{
    TCHAR szExePath[MAX_PATH] = {0};
    LPTSTR lpName             = _T("");
    LPTSTR lpDesc             = _T("");
    DWORD  dwType             = SERVICE_DEMAND_START;

    if (g_lpServiceName == NULL) return ESC_FRAMEWORK_UNINITIALIZE;

    lpName = (*g_lpServiceName)();

    if (g_lpServiceDescription != NULL)
    {
        lpDesc = (*g_lpServiceDescription)();
    }
    
    if (g_lpServiceType != NULL)
    {
        dwType = (*g_lpServiceType)();
    }

    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        if (GetLastError() == ERROR_ACCESS_DENIED)
        {
            return ESC_ACCESS_DENY;
        }
        return ESC_UNKNOWN;
    }

    GetModuleFileName(NULL, szExePath, MAX_PATH - 1);

    SC_HANDLE hService = CreateService(
        hSCM, lpName, lpName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
        dwType, SERVICE_ERROR_NORMAL,
        szExePath, NULL, NULL, NULL, NULL, NULL);

    if (hService == NULL)
    {
        CloseServiceHandle(hSCM);
        DWORD dwErr = GetLastError();
        if (dwErr == ERROR_ACCESS_DENIED)
        {
            return ESC_ACCESS_DENY;
        }
        else if (dwErr == ERROR_INVALID_NAME)
        {
            return ESC_SERVICE_NAME_ERROR;
        }
        else if (dwErr == ERROR_DUPLICATE_SERVICE_NAME ||
            dwErr == ERROR_SERVICE_EXISTS)
        {
            return ESC_SERVICE_EXIST;
        }
        else if (dwErr == ERROR_INVALID_HANDLE)
        {
            return ESC_INVALID_HANDLE;
        }
        return ESC_UNKNOWN;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if (lstrlen(lpDesc) > 0)
    {
        LPTSTR szFormat = _T("SYSTEM\\CurrentControlSet\\services\\%s");
        TCHAR szSubKey[MAX_PATH] = {0};
        HKEY hRet;

        _sntprintf_s(szSubKey, MAX_PATH, MAX_PATH, szFormat, lpName);
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0L,
            KEY_ALL_ACCESS, &hRet) != ERROR_SUCCESS)
        {
            return ESC_REG_ERROR;
        }
        if (RegSetKeyValue(hRet, NULL, _T("Description"),
            REG_SZ, lpDesc, lstrlen(lpDesc)*sizeof(TCHAR)) != ERROR_SUCCESS)
        {
            RegCloseKey(hRet);
            return ESC_REG_ERROR;
        }
        RegCloseKey(hRet);
    }

    return ESC_SUCCESS;
}


int ServiceUninstall()
{
    LPTSTR lpName             = _T("");

    if (g_lpServiceName == NULL) return ESC_FRAMEWORK_UNINITIALIZE;

    lpName = (*g_lpServiceName)();

    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        if (GetLastError() == ERROR_ACCESS_DENIED)
        {
            return ESC_ACCESS_DENY;
        }
        return ESC_UNKNOWN;
    }

    SC_HANDLE hService = OpenService(hSCM, lpName, SERVICE_STOP | DELETE);
    
    if (hService == NULL)
    {
        CloseServiceHandle(hSCM);
        DWORD dwErr = GetLastError();
        if (dwErr == ERROR_ACCESS_DENIED)
        {
            return ESC_ACCESS_DENY;
        }
        else if (dwErr == ERROR_INVALID_NAME)
        {
            return ESC_SERVICE_NAME_ERROR;
        }
        else if (dwErr == ERROR_DUPLICATE_SERVICE_NAME ||
            dwErr == ERROR_SERVICE_EXISTS)
        {
            return ESC_SERVICE_EXIST;
        }
        else if (dwErr == ERROR_INVALID_HANDLE)
        {
            return ESC_INVALID_HANDLE;
        }
        return ESC_UNKNOWN;
    }


    SERVICE_STATUS sStatus = {0};
    ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);

    if (DeleteService(hService) == FALSE)
    {
        CloseServiceHandle(hSCM);
        CloseServiceHandle(hService);
        DWORD dwErr = GetLastError();
        if (dwErr == ERROR_ACCESS_DENIED)
        {
            return ESC_ACCESS_DENY;
        }
        else if (dwErr == ERROR_INVALID_HANDLE)
        {
            return ESC_INVALID_HANDLE;
        }
        return ESC_UNKNOWN;
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

    return ESC_SUCCESS;
}

static void WINAPI StupidServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    SERVICE_STATUS_HANDLE hStatus; 
    SERVICE_STATUS sStatus;
    
    LPTSTR lpszName = _T("");

    sStatus.dwServiceType             = SERVICE_WIN32_OWN_PROCESS; 
    sStatus.dwCurrentState            = SERVICE_START_PENDING; 
    sStatus.dwControlsAccepted        =  SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    sStatus.dwWin32ExitCode           = 0; 
    sStatus.dwServiceSpecificExitCode = 0; 
    sStatus.dwCheckPoint              = 0; 
    sStatus.dwWaitHint                = 0; 

    if (g_lpServiceName != NULL)
    {
        lpszName = (*g_lpServiceName)();
    }

    hStatus = RegisterServiceCtrlHandlerEx(
        lpszName, (LPHANDLER_FUNCTION_EX)StupidCtrlHandlerEx, hStatus); 
    if (hStatus == (SERVICE_STATUS_HANDLE)NULL) 
    { 
        return; 
    }
    sStatus.dwCurrentState = SERVICE_RUNNING; 
    SetServiceStatus (hStatus, &sStatus);
    (*g_lpServiceMain)(hStatus);
    

}

static DWORD WINAPI StupidCtrlHandlerEx(DWORD dwControl,
                                        DWORD dwEventType,
                                        LPVOID lpEventData,
                                        LPVOID lpContext)
{
    return (*g_lpServiceCtrl)(dwControl, lpContext);
}

int ServiceMain(DWORD dwArgc, LPTSTR* lpszArgs)
{
    if (g_lpServiceEntry != NULL)
    {
        return (*g_lpServiceEntry)(dwArgc, lpszArgs);
    }

    if (g_lpServiceMain != NULL && g_lpServiceCtrl != NULL)
    {
        SERVICE_TABLE_ENTRY sTable[2] = {0};        
        LPTSTR lpszName = _T("");
        if (g_lpServiceName != NULL)
        {
            lpszName = (*g_lpServiceName)();
        }

        lstrcpy(sTable[0].lpServiceName, lpszName);
        sTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)StupidServiceMain;

        if(StartServiceCtrlDispatcher(sTable) == FALSE)
        {
            return ESC_SERVICE_RUNNING_ERROR;
        }
        return ESC_SUCCESS;
    }
    return ESC_FRAMEWORK_UNINITIALIZE;
}

LPTSTR GetErrorMessage(int nRet)
{
    static struct ErrMsg
    {
        int nErr;
        LPTSTR lpszMsg;
    }
    sErrMsg [] = 
    {
        {ESC_SUCCESS, _T("成功")},
        {ESC_INVALID_HANDLE, _T("无效句柄")},
        {ESC_ACCESS_DENY, _T("没有权限")},
        {ESC_SERVICE_NOT_EXIST, _T("服务不存在")},
        {ESC_SERVICE_EXIST, _T("服务已经存在")},
        {ESC_SERVICE_NAME_ERROR, _T("服务名称出错")},
        {ESC_FRAMEWORK_UNINITIALIZE, _T("服务未初始化")},
        {ESC_REG_ERROR, _T("处理注册表出错")},
        {ESC_SERVICE_RUNNING_ERROR, _T("服务运行错误")},
        {ESC_UNKNOWN, _T("未知错误")},
    };

    LPTSTR lpszRet = NULL;

    int nHigh = sizeof(sErrMsg)/sizeof(sErrMsg[0]) - 1;
    int nLow = 0;
    while(nHigh >= nLow)
    {
        int nMid = (nHigh + nLow) / 2;
        ErrMsg& sTmpMsg = sErrMsg[nMid];
        if (sTmpMsg.nErr > nRet)
        {
            nLow = nMid + 1;
        }
        else if (sTmpMsg.nErr < nRet)
        {
            nHigh = nMid - 1;
        }
        else
        {
            lpszRet = sTmpMsg.lpszMsg;
            break;
        }
    }

    return lpszRet;
}


