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
typedef int    (WINAPI *ServiceMainCallback)(DWORD, LPTSTR*);
typedef DWORD  (WINAPI *ServiceControlCallback)(DWORD, LPVOID);

class ServiceCtrl;
class ServiceFactory
{
public:
    static ServiceFactory& GetFactory();

public:
    ServiceCtrl* CreateServiceCtrl();
    void RegServiceCtrl(ServiceCtrl* pCtrl);

private:
    ServiceCtrl* m_pDefServiceCtrl;
};

class ServiceCtrl
{
protected:
    ServiceCtrl();

public:
    ~ServiceCtrl();

public:
    // ��������ת���ַ���
    LPTSTR GetErrorMessage(int nRet);
    // ��װ����
    int ServiceInstall();
    // ɾ������
    int ServiceUninstall();
    // ���÷���
    int ServiceMain(DWORD dwArgc, LPTSTR* lpszArgs);

    void SetServiceMain(ServiceMainCallback fnServiceMain);
    void SetServiceCtrl(ServiceControlCallback fnServiceCtrl);

protected:
    void WINAPI StupidServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    DWORD WINAPI StupidCtrlHandlerEx(DWORD dwControl,
        DWORD dwEventType,
        LPVOID lpEventData,
        LPVOID lpContext);

    virtual void  SimpleServiceMain(LPVOID);
    virtual DWORD SimpleCtrlHandleEx(DWORD dwControl, LPVOID lpContext);

public:
    virtual LPTSTR GetServiceName() = 0;
    virtual LPTSTR GetSeerviceDisplayName(); // default same as GetServiceName
    virtual DWORD  GetServiceType() = 0;
    virtual LPTSTR GetServiceDescription() = 0;

private:
    ServiceMainCallback m_fnServiceMain;
    ServiceControlCallback m_fnServiceCtrl;
};

#define REG_SERVICE(RealServiceCtrl)                              \
    class StupidDummpy##RealServiceCtrl##DummyStupid              \
    {                                                             \
    public:                                                       \
        StupidDummpy##RealServiceCtrl##DummyStupid()              \
        {                                                         \
            RealServiceCtrl* pCtrl = new RealServiceCtrl;         \
            ServiceFactory& sSF = ServiceFactory::GetFactory();   \
            sSF.RegServiceCtrl(pCtrl);                            \
        }                                                         \
    };                                                            \
    static StupidDummpy##RealServiceCtrl##DummyStupid             \
        sDummyStupidInstanceStupidDummy;                          \
    



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

