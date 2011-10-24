/*
 * File       : Hash.cpp
 * Description: 计算Hash值的接口
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */


#include "Hash.h"
#include "HashImpl.h"

USE_XBASIC_NAMESPACE

Hash::Hash(HashImpl* pImpl)
: m_pImpl(pImpl)
{
	ASSERT(pImpl != NULL);
}
Hash::~Hash()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
}
std::string Hash::GetStringHash(std::string strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
std::string Hash::GetStringHash(std::wstring strValue)
{
	return m_pImpl->GetStringHash(strValue);
}
std::string Hash::GetFileHash(std::string strFile)
{
	return m_pImpl->GetFileHash(strFile);
}
