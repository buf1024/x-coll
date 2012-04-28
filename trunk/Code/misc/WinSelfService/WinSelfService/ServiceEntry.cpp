#include "ServiceCtrl.h"

#define SERVICE_INSTALL   _T("INSTALL")
#define SERVICE_UNINSTALL _T("UNINSTALL")
#define SERVICE_ERROR     _T("ERROR")

#define BUF_SIZE          2048

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int    numArgs = 0;
    LPWSTR* lpArgs = CommandLineToArgvW(GetCommandLine(), &numArgs);


    TCHAR szMsg[BUF_SIZE] = {0};
    int nRet = 0;

    if (numArgs > 1)
    {
        if (lstrcmpi(lpArgs[1], SERVICE_INSTALL) == 0)
        {
            nRet = ServiceInstall();
            if (nRet == ESC_SUCCESS)
            {
                MessageBox(NULL, _T("服务安装成功"), _T("成功"), MB_OK);
            }
            else
            {
                _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                    _T("服务安装失败, 返回码：%d\n\n")
                    _T("请以参数\"ERROR %d\"运行本程序查看出错原因\n")
                    _T("请确保以管理员身份运行此程序"), nRet, nRet);
                MessageBox(NULL, szMsg, _T("失败"), MB_ICONWARNING);
            }
            
        }
        else if (lstrcmpi(lpArgs[1], SERVICE_UNINSTALL) == 0)
        {
            nRet = ServiceUninstall();
            if (nRet == ESC_SUCCESS)
            {
                MessageBox(NULL, _T("服务卸载成功"), _T("成功"), MB_OK);
            }
            else
            {
                _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                    _T("服务卸载失败, 返回码：%d\n\n")
                    _T("请以参数\"ERROR %d\"运行本程序查看出错原因\n")
                    _T("请确保以管理员身份运行此程序"), nRet, nRet);
                MessageBox(NULL, szMsg, _T("失败"), MB_ICONWARNING);
            }
        }
        else if (lstrcmpi(lpArgs[1], SERVICE_ERROR) == 0)
        {
            if (numArgs > 2)
            {
                nRet = _tstoi(lpArgs[2]);
            }
            if (nRet == 0 && lpArgs[2][0] != _T('0'))
            {
                MessageBox(NULL, _T("参数格式不对"), _T("失败"), MB_ICONWARNING);
            }
            else
            {
                LPTSTR lpszMsg = GetErrorMessage(nRet);
                if (lpszMsg != NULL)
                {
                    _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                        _T("错误码%d的出错信息:\n\n%s"), nRet, lpszMsg);
                    MessageBox(NULL, szMsg, _T("失败"), MB_OK);
                }
                else
                {
                    _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                        _T("找不到错误码%d的出错信息"), nRet);
                    MessageBox(NULL, szMsg, _T("失败"), MB_ICONWARNING);
                }
            }
        }
        else
        {
            MessageBox(NULL, _T("未知参数"), _T("失败"), MB_ICONWARNING);
        }
    }
    else
    {
        // ServiceMain
        ServiceMain(numArgs, lpArgs);
    }


    return 0;
}


