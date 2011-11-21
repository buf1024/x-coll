/*
 * File       : WinCSLocer.cpp
 * Description: 
 * Version    : 2011-10-14 Created
 * Author     : buf1024@gmail.com
 */
#include "WinCSLocer.h"

#ifdef _MSC_VER

USE_XBASIC_NAMESPACE

WinCriticalSectionLocer::WinCriticalSectionLocer(void)
{
    InitializeCriticalSection(&m_sCS);
}

WinCriticalSectionLocer::~WinCriticalSectionLocer(void)
{
    DeleteCriticalSection(&m_sCS);
}

bool WinCriticalSectionLocer::Lock()
{
    EnterCriticalSection(&m_sCS);
    return true;
}
bool WinCriticalSectionLocer::TryLock()
{
    return false;
}
bool WinCriticalSectionLocer::Unlock()
{
    LeaveCriticalSection(&m_sCS);
    return true;
}

#endif

