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
                MessageBox(NULL, _T("����װ�ɹ�"), _T("�ɹ�"), MB_OK);
            }
            else
            {
                _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                    _T("����װʧ��, �����룺%d\n\n")
                    _T("���Բ���\"ERROR %d\"���б�����鿴����ԭ��\n")
                    _T("��ȷ���Թ���Ա������д˳���"), nRet, nRet);
                MessageBox(NULL, szMsg, _T("ʧ��"), MB_ICONWARNING);
            }
            
        }
        else if (lstrcmpi(lpArgs[1], SERVICE_UNINSTALL) == 0)
        {
            nRet = ServiceUninstall();
            if (nRet == ESC_SUCCESS)
            {
                MessageBox(NULL, _T("����ж�سɹ�"), _T("�ɹ�"), MB_OK);
            }
            else
            {
                _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                    _T("����ж��ʧ��, �����룺%d\n\n")
                    _T("���Բ���\"ERROR %d\"���б�����鿴����ԭ��\n")
                    _T("��ȷ���Թ���Ա������д˳���"), nRet, nRet);
                MessageBox(NULL, szMsg, _T("ʧ��"), MB_ICONWARNING);
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
                MessageBox(NULL, _T("������ʽ����"), _T("ʧ��"), MB_ICONWARNING);
            }
            else
            {
                LPTSTR lpszMsg = GetErrorMessage(nRet);
                if (lpszMsg != NULL)
                {
                    _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                        _T("������%d�ĳ�����Ϣ:\n\n%s"), nRet, lpszMsg);
                    MessageBox(NULL, szMsg, _T("ʧ��"), MB_OK);
                }
                else
                {
                    _sntprintf_s(szMsg, BUF_SIZE, BUF_SIZE, 
                        _T("�Ҳ���������%d�ĳ�����Ϣ"), nRet);
                    MessageBox(NULL, szMsg, _T("ʧ��"), MB_ICONWARNING);
                }
            }
        }
        else
        {
            MessageBox(NULL, _T("δ֪����"), _T("ʧ��"), MB_ICONWARNING);
        }
    }
    else
    {
        // ServiceMain
        ServiceMain(numArgs, lpArgs);
    }


    return 0;
}


