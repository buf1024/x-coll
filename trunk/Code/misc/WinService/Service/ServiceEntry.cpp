#include "ServiceCtrl.h"

#define SERVICE_INSTALL   _T("INSTALL")
#define SERVICE_UNINSTALL _T("UNINSTALL")

LPTSTR XServiceNameCallback()
{
    return _T("myxxservice");
}
LPTSTR XServiceDescriptionCallback()
{
    return _T("This is the service");
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int    numArgs = 0;
    LPWSTR* lpArgs = CommandLineToArgvW(lpCmdLine, &numArgs);


    TCHAR szMsg[1024] = {0};

    SetServiceNameCallback(XServiceNameCallback);
    SetServiceDescriptionCallback(XServiceDescriptionCallback);

    if (numArgs >= 1)
    {
        if (lstrcmpi(lpArgs[0], SERVICE_INSTALL) == 0)
        {
            int r = ServiceInstall();
            _sntprintf(szMsg, 1023, _T("Ret=%d\n"), r);
            MessageBox(NULL, szMsg, _T("t"), MB_OK);
        }
        else if (lstrcmpi(lpArgs[0], SERVICE_UNINSTALL) == 0)
        {
            int r = ServiceUninstall();

            _sntprintf(szMsg, 1023, _T("Ret=%d\n"), r);
            MessageBox(NULL, szMsg, _T("tTTT"), MB_OK);
        }
        else
        {
            // Do nothing
            MessageBox(NULL, _T("do nothting"), _T("t"), MB_OK);
        }
    }
    else
    {
        // ServiceMain
        ServiceMain();
        MessageBox(NULL, _T("do nothting2"), _T("t"), MB_OK);
    }


    return 0;
}


