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

// 回调函数类型
typedef VOID    (WINAPI *ServiceMainCallback)(DWORD, LPTSTR*);

class ServiceCtrl;
class ServiceFactory
{
private:
    ServiceFactory();
public:
    ~ServiceFactory();

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
    virtual ~ServiceCtrl();

public:
    // 将错误码转化字符串
    virtual LPTSTR GetErrorMessage(int nRet);
    
    // 安装服务
    int ServiceInstall();
    // 删除服务
    int ServiceUninstall();
    // 启用服务
    int ServiceMain(DWORD dwArgc, LPTSTR* lpszArgs);

    void SetServiceMain(ServiceMainCallback fnServiceMain);

public:    
    virtual void  SimpleServiceMain(LPVOID);
    virtual DWORD SimpleCtrlHandleEx(DWORD dwControl, LPVOID lpContext);

    virtual LPTSTR GetServiceName() = 0;
    virtual LPTSTR GetSeerviceDisplayName(); // default same as GetServiceName
    virtual DWORD  GetServiceType() = 0;
    virtual LPTSTR GetServiceDescription() = 0;

private:
    ServiceMainCallback m_fnServiceMain;
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
    


#endif /* __48SLOTS_SERVICE_CTRL_H__ */

