////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : HashMD5Impl.cpp
// Purpose     : 
// Version     : 2010-11-13 15:19:30 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////

#include "HashMD5Impl.h"
#include "md5.h"

HashMD5Impl::HashMD5Impl(void)
{
}

HashMD5Impl::~HashMD5Impl(void)
{
}

StdString HashMD5Impl::GetStringHash(std::string strValue)
{
	int nLen = strValue.size();
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	return ComputeHash(pBuf, nLen);
}

StdString HashMD5Impl::GetStringHash(std::wstring strValue)
{
	int nLen = strValue.size() * sizeof(wchar_t);
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	return ComputeHash(pBuf, nLen);
}
StdString HashMD5Impl::GetFileHash(StdString strFile)
{
	StdString strRet;

	HANDLE hFile = CreateFile(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
			PBYTE pByte = (PBYTE)MapViewOfFile(hMapping, FILE_MAP_COPY, 0, 0, 0);
			unsigned long dwSize = GetFileSize(hFile, NULL);			
			strRet = ComputeHash(pByte, dwSize);
			UnmapViewOfFile(pByte);
			CloseHandle(hMapping);
		}
		else
		{
			CloseHandle(hFile);
		}
	}

	return strRet;
}


StdString HashMD5Impl::ComputeHash(const unsigned char* pBuf, unsigned long lLen)
{
	unsigned char digest[16] = {0};

	MD5Context ctx;
	MD5Init(&ctx);
	MD5Update(&ctx, pBuf, lLen);	
	MD5Final(&ctx, digest);

	TCHAR szBuf[33] = {0};  //szBuf[32] = 0
	for (int i=0; i<16; i++)
	{
		int nValL = digest[i]&0x0F;
		int nValH = digest[i]>>4;
		_sntprintf_s(szBuf + i*2, 33 - i*2, 33 - i*2, _T("%x%x"), nValH, nValL);
	}

	return szBuf;
}