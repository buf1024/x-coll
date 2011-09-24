////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCUI -- Personal Windowless UI Library Project
// 
// FileName    : Hash.cpp
// Purpose     : 
// Version     : 2010-11-9 20:09:19) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "Hash.h"
#include "HashImpl.h"

Hash::Hash(HashImpl* pImpl)
: m_pImpl(pImpl)
{
	_ASSERT(pImpl != NULL);
}
Hash::~Hash()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
}
StdString Hash::GetStringHash(std::string strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
StdString Hash::GetStringHash(std::wstring strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
StdString Hash::GetFileHash(StdString strFile)
{
	return m_pImpl->GetFileHash(strFile);
}