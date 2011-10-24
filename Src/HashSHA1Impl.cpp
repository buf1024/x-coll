/*
 * File       : HashSHA1Impl.cpp
 * Description: 
 * Version    : 2010-11-13 Created
 * Author     : buf1024@gmail.com
 */

#include "HashSHA1Impl.h"


USE_XBASIC_NAMESPACE


HashSHA1Impl::HashSHA1Impl(void)
{
    m_pSHA1 = new SHA1;
}

HashSHA1Impl::~HashSHA1Impl(void)
{
    delete m_pSHA1;
}
std::string HashSHA1Impl::GetStringHash(std::string strValue)
{
	m_pSHA1->Reset();
	int nLen = strValue.size();
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	m_pSHA1->Input(pBuf, nLen);
	unsigned int digest[5] = {0};
	m_pSHA1->Result(digest);
	char szRes[48] = "";
#ifdef MSWINDOWS
	_snprintf_s(szRes, 48, 48, "%x%x%x%x%x",
		digest[0], digest[1], digest[2], digest[3], digest[4]);
#else
    snprintf(szRes, 48, "%x%x%x%x%x",
        digest[0], digest[1], digest[2], digest[3], digest[4]);
#endif
	return szRes;
}
std::string HashSHA1Impl::GetStringHash(std::wstring strValue)
{
	m_pSHA1->Reset();
	int nLen = strValue.size() * sizeof(wchar_t);
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	m_pSHA1->Input(pBuf, nLen);
	unsigned int digest[5] = {0};
	m_pSHA1->Result(digest);
	char szRes[48] = "";
#ifdef MSWINDOWS
	_snprintf_s(szRes, 48, 48, "%x%x%x%x%x",
		digest[0], digest[1], digest[2], digest[3], digest[4]);
#else
    snprintf(szRes, 48, "%x%x%x%x%x",
        digest[0], digest[1], digest[2], digest[3], digest[4]);
#endif
	return szRes;
}
std::string HashSHA1Impl::GetFileHash(std::string strFile)
{
	std::string strRet;

#ifdef MSWINDOWS

	HANDLE hFile = CreateFileA(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
			PBYTE pByte = (PBYTE)MapViewOfFile(hMapping, FILE_MAP_COPY, 0, 0, 0);
			unsigned long dwSize = GetFileSize(hFile, NULL);			
			
			m_pSHA1->Reset();
			m_pSHA1->Input(pByte, dwSize);
			unsigned int digest[5] = {0};
			m_pSHA1->Result(digest);
			char szRes[48] = "";
			_snprintf_s(szRes, 48, 48, "%x%x%x%x%x",
				digest[0], digest[1], digest[2], digest[3], digest[4]);
			strRet = szRes;

			UnmapViewOfFile(pByte);
			CloseHandle(hMapping);
		}
		else
		{
			CloseHandle(hFile);
		}
	}
#endif

	return strRet;
}


