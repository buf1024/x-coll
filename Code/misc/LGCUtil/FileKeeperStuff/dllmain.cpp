// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "ModuleContext.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		ModuleContext::GetInstPtr()->SetModuleHandle(hModule);
		break;
	case DLL_PROCESS_DETACH:
//	case DLL_THREAD_DETACH:
		ModuleContext::ReleaseRC();
		break;
	}
	return TRUE;
}

