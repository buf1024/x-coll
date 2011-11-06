STAT_LIB_DEBUG = '/Od /D "WIN32" /D "_DEBUG" /D "_LIB" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
STAT_LIB_RELEASE = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /D "_LIB" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

DLL_DEBUG = '/Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
DLL_RELEASE = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" "_WINDLL" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

CONSOLE_DEBUG = '/Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
CONSOLE_RELEASE = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

WINDOWS_DEBUG = '/Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
WINDOWS_RELEASE = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

DEBUG_COMM = '/Od /D "WIN32" /D "_DEBUG" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
RELEASE_COMM = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'