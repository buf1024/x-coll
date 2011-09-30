////////////////////////////////////////////////////////////////////////////////////////
// 
// Filekeeper Project
//  
//  
// FileName    : ComRegSrv.h
// Purpose     : Register server
// Version     : 2010-12-30 (22:03) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "stl.h"
#include <Guiddef.h>
#include "Singleton.h"

namespace lgc
{
	class ComRegSrv : public Singleton<ComRegSrv>
	{
	public:
		// Register the component in the registry.
		//
		HRESULT STDMETHODCALLTYPE RegisterServer(const CLSID& clsid,	// Class ID
			const Std_String strFileName,			// DLL module handle
			const Std_String strThreadingModel,		// ThreadingModel
			const Std_String strProgID,				//   IDs
			const Std_String strDescription);		// Description String


		//
		// Remove the component from the registry.
		//
		HRESULT STDMETHODCALLTYPE UnregisterServer(const CLSID& clsid,// Class ID
			const Std_String strProgID);			//   IDs
	};

}




