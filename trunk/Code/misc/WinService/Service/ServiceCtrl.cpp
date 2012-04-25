#include "ServiceCtrl.h"

static ServiceMainCallback g_lpServiceMain               = NULL;
static ServiceNameCallback g_lpServiceName               = NULL;
static ServiceTypeCallback g_lpServiceType               = NULL;
static ServiceDescriptionCallback g_lpServiceDescription = NULL;

static void InitServiceStatus(SERVICE_STATUS& sStatus)
{
    sStatus.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
    sStatus.dwCurrentState            = SERVICE_STOPPED;
    sStatus.dwControlsAccepted        = SERVICE_ACCEPT_STOP;
    sStatus.dwWin32ExitCode           = 0;
    sStatus.dwServiceSpecificExitCode = 0;
    sStatus.dwCheckPoint              = 0;
    sStatus.dwWaitHint                = 0;
}

void SetServiceMainCallback(ServiceMainCallback lpCallback)
{
    g_lpServiceMain = lpCallback;
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



int ServiceMain()
{
    //if (g_lpServiceMain != NULL)
    //{
    //    int error; 

    //    ServiceStatus.dwServiceType = 
    //        SERVICE_WIN32; 
    //    ServiceStatus.dwCurrentState = 
    //        SERVICE_START_PENDING; 
    //    ServiceStatus.dwControlsAccepted   =  
    //        SERVICE_ACCEPT_STOP | 
    //        SERVICE_ACCEPT_SHUTDOWN;
    //    ServiceStatus.dwWin32ExitCode = 0; 
    //    ServiceStatus.dwServiceSpecificExitCode = 0; 
    //    ServiceStatus.dwCheckPoint = 0; 
    //    ServiceStatus.dwWaitHint = 0; 

    //    hStatus = RegisterServiceCtrlHandler(
    //        "MemoryStatus", 
    //        (LPHANDLER_FUNCTION)ControlHandler); 
    //    if (hStatus == (SERVICE_STATUS_HANDLE)0) 
    //    { 
    //        // Registering Control Handler failed
    //        return; 
    //    }  
    //    // Initialize Service 
    //    error = InitService(); 
    //    if (error) 
    //    {
    //        // Initialization failed
    //        ServiceStatus.dwCurrentState = 
    //            SERVICE_STOPPED; 
    //        ServiceStatus.dwWin32ExitCode = -1; 
    //        SetServiceStatus(hStatus, &ServiceStatus); 
    //        return; 
    //    } 
    //    // We report the running sStatus to SCM. 
    //    ServiceStatus.dwCurrentState = 
    //        SERVICE_RUNNING; 
    //    SetServiceStatus (hStatus, &ServiceStatus);

    //    MEMORYSTATUS memory;
    //    // The worker loop of a service
    //    while (ServiceStatus.dwCurrentState == 
    //        SERVICE_RUNNING)
    //    {
    //        char buffer[16];
    //        GlobalMemoryStatus(&memory);
    //        sprintf(buffer, "%d", memory.dwAvailPhys);
    //        int result = WriteToLog(buffer);
    //        if (result)
    //        {
    //            ServiceStatus.dwCurrentState = 
    //                SERVICE_STOPPED; 
    //            ServiceStatus.dwWin32ExitCode      = -1; 
    //            SetServiceStatus(hStatus, 
    //                &ServiceStatus);
    //            return;
    //        }
    //        Sleep(SLEEP_TIME);
    //    }
    //}
    return ESC_SUCCESS;
}
