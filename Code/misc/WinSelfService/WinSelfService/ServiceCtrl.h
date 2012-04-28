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
typedef int    (*ServiceEntryCallback)(DWORD, LPTSTR*);
typedef void   (*ServiceMainCallback)(LPVOID);
typedef DWORD  (*ServiceControlCallback)(DWORD, LPVOID);
typedef LPTSTR (*ServiceNameCallback)();
typedef DWORD  (*ServiceTypeCallback)();
typedef LPTSTR (*ServiceDescriptionCallback)();

// 服务入口回调函数，启动服务时用到。
// 与SetServiceMainCallback两之中，必须设置一个
// 如果两个都设置了，优先考虑这个。
void SetServiceEntryCallback(ServiceEntryCallback lpCallback);
// 服务入口回调函数，启动服务时用到。提供一些默认的初始化。
// 与SetServiceEntryCallback两之中，必须设置一个
// 如果两个都设置了，优先考虑上一个。
void SetServiceMainCallback(ServiceMainCallback lpMainCallback, 
                            ServiceControlCallback lpCtrlCallback);
// 服务名称回调函数，在安装服务，删除服务，启用服务都用到。
// 必须设置。
void SetServiceNameCallback(ServiceNameCallback lpCallback);
// 服务类型回调函数，在安装服务是最好设置，其它情况下用到。
// 可不初始化，不初始化时，默认是按需启动。
void SetServiceTypeCallback(ServiceTypeCallback lpCallback);
// 服务描述回调函数，在安装服务是最好设置，其它情况下用到。
// 可不初始化。
void SetServiceDescriptionCallback(ServiceDescriptionCallback lpCallback);


// 将错误码转化字符串
LPTSTR GetErrorMessage(int nRet);

// 安装服务
int ServiceInstall();
// 删除服务
int ServiceUninstall();
// 启用服务
int ServiceMain(DWORD dwArgc, LPTSTR* lpszArgs);

#endif /* __48SLOTS_SERVICE_CTRL_H__ */

