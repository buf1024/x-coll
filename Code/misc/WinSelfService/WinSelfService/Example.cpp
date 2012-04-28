#include "ServiceCtrl.h"

void WriteToLog(const char* msg)
{
    FILE* fp = fopen("c:\\a.txt", "a+");
    fwrite(msg, strlen(msg), 1, fp);
    fclose(fp);
}

void   ExServiceMainCallback(LPVOID pCtx)
{

}
DWORD  ExServiceControlCallback(DWORD dwType, LPVOID pCtx)
{
    SERVICE_STATUS_HANDLE hStatus = (SERVICE_STATUS_HANDLE)(pCtx);
    SERVICE_STATUS sStatus = {0};
    
    sStatus.dwWin32ExitCode = 0;
    sStatus.dwCurrentState = SERVICE_RUNNING;

    switch(dwType) 
    { 
    case SERVICE_CONTROL_STOP: 
        WriteToLog("Monitoring stopped.");

        sStatus.dwWin32ExitCode = 0; 
        sStatus.dwCurrentState = SERVICE_STOPPED; 

        break; 

    case SERVICE_CONTROL_SHUTDOWN: 
        WriteToLog("Monitoring stopped.");

        sStatus.dwWin32ExitCode = 0; 
        sStatus.dwCurrentState = SERVICE_STOPPED; 

        break

    default:
        break;
    } 

    
    SetServiceStatus (hStatus, &sStatus);
    return 0;
}
LPTSTR ExServiceNameCallback()
{
    return _T("XLServicePlatform2");
}
LPTSTR ExServiceDescriptionCallback()
{
    return _T("这是一个非常简单的服务测试程序");
}

class ExDummyInitailizer
{
public:
    ExDummyInitailizer()
    {
        SetServiceMainCallback(ExServiceMainCallback,
            ExServiceControlCallback);
        SetServiceNameCallback(ExServiceNameCallback);
        SetServiceDescriptionCallback(ExServiceDescriptionCallback);
    }
};

ExDummyInitailizer gDummy; 