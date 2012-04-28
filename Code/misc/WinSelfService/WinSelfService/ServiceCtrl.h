#ifndef __48SLOTS_SERVICE_CTRL_H__
#define __48SLOTS_SERVICE_CTRL_H__

#include <Windows.h>
#include <tchar.h>

#define ESC_SUCCESS                  0
#define ESC_INVALID_HANDLE           -1
#define ESC_ACCESS_DENY              -2
#define ESC_SERVICE_NOT_EXIST        -3
#define ESC_SERVICE_EXIST            -4
#define ESC_SERVICE_NAME_ERROR       -5
#define ESC_FRAMEWORK_UNINITIALIZE   -6
#define ESC_REG_ERROR                -7
#define ESC_SERVICE_RUNNING_ERROR    -8
#define ESC_UNKNOWN                  -100

// �ص���������
typedef int    (*ServiceEntryCallback)(DWORD, LPTSTR*);
typedef void   (*ServiceMainCallback)(LPVOID);
typedef DWORD  (*ServiceControlCallback)(DWORD, LPVOID);
typedef LPTSTR (*ServiceNameCallback)();
typedef DWORD  (*ServiceTypeCallback)();
typedef LPTSTR (*ServiceDescriptionCallback)();

// ������ڻص���������������ʱ�õ���
// ��SetServiceMainCallback��֮�У���������һ��
// ��������������ˣ����ȿ��������
void SetServiceEntryCallback(ServiceEntryCallback lpCallback);
// ������ڻص���������������ʱ�õ����ṩһЩĬ�ϵĳ�ʼ����
// ��SetServiceEntryCallback��֮�У���������һ��
// ��������������ˣ����ȿ�����һ����
void SetServiceMainCallback(ServiceMainCallback lpMainCallback, 
                            ServiceControlCallback lpCtrlCallback);
// �������ƻص��������ڰ�װ����ɾ���������÷����õ���
// �������á�
void SetServiceNameCallback(ServiceNameCallback lpCallback);
// �������ͻص��������ڰ�װ������������ã�����������õ���
// �ɲ���ʼ��������ʼ��ʱ��Ĭ���ǰ���������
void SetServiceTypeCallback(ServiceTypeCallback lpCallback);
// ���������ص��������ڰ�װ������������ã�����������õ���
// �ɲ���ʼ����
void SetServiceDescriptionCallback(ServiceDescriptionCallback lpCallback);


// ��������ת���ַ���
LPTSTR GetErrorMessage(int nRet);

// ��װ����
int ServiceInstall();
// ɾ������
int ServiceUninstall();
// ���÷���
int ServiceMain(DWORD dwArgc, LPTSTR* lpszArgs);

#endif /* __48SLOTS_SERVICE_CTRL_H__ */

