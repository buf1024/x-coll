////////////////////////////////////////////////////////////////////////////////////////
// 
// Filekeeper Project
//  
//  
// FileName    : FileKeeperFactory.cpp
// Purpose     : 
// Version     : 2010-12-30 (22:11) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "FileKeeperFactory.h"
#include "ModuleContext.h"
#include "FileKeeperStuff.h"

FileKeeperFactory::FileKeeperFactory(void)
: m_nRef(0L)
{
}

FileKeeperFactory::~FileKeeperFactory(void)
{
}

//IClassFactory
HRESULT FileKeeperFactory::CreateInstance( 
	/* [unique][in] */ IUnknown *pUnkOuter,
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ void **ppvObject)
{
	if (pUnkOuter != NULL) return CLASS_E_NOAGGREGATION;

	FileKeeperStuff* pObj = new FileKeeperStuff;
	HRESULT hRes = pObj->QueryInterface(riid, ppvObject);
	if (hRes != S_OK)
	{
		ModuleContext* pCtx = ModuleContext::GetInstPtr();
		pCtx->AddRefUsageNum();
		delete pObj;
	}
	return hRes;
}

HRESULT FileKeeperFactory::LockServer( 
	/* [in] */ BOOL fLock)
{
	ModuleContext* pCtx = ModuleContext::GetInstPtr();
	if (fLock)
	{
		pCtx->AddRefLockNum();
	}
	else
	{
		pCtx->ReleaseLockNum();
	}
	return S_FALSE;
}

//IUnkown
HRESULT FileKeeperFactory::QueryInterface( 
										/* [in] */
										REFIID riid,
										/* [iid_is][out] */
										void **ppvObject)
{

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown*)this;
		((IUnknown*)*ppvObject)->AddRef();
	}
	else if (riid == IID_IClassFactory)
	{
		*ppvObject = (IClassFactory*)this;
		((IClassFactory*)*ppvObject)->AddRef();
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

ULONG FileKeeperFactory::AddRef( void)
{
	//m_nRef++;
    InterlockedIncrement(&m_nRef);
	return m_nRef;
}

ULONG FileKeeperFactory::Release( void)
{
    InterlockedDecrement(&m_nRef);
	//m_nRef--;
	if (m_nRef == 0L)
	{
		//Suicide
		delete this;
	}
	return m_nRef;
}