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
#define ESC_UNKNOWN                  -100


typedef void (WINAPI *ServiceMainCallback)(DWORD, LPTSTR*);
typedef LPTSTR (*ServiceNameCallback)();
typedef DWORD (*ServiceTypeCallback)();
typedef LPTSTR (*ServiceDescriptionCallback)();


void SetServiceMainCallback(ServiceMainCallback lpCallback);
void SetServiceNameCallback(ServiceNameCallback lpCallback);
void SetServiceTypeCallback(ServiceTypeCallback lpCallback);
void SetServiceDescriptionCallback(ServiceDescriptionCallback lpCallback);


int ServiceInstall();
int ServiceUninstall();
int ServiceMain();

