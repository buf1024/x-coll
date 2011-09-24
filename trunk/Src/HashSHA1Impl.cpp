////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : HashSHA1Impl.cpp
// Purpose     : 
// Version     : 2010-11-13 15:20:12 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "HashSHA1Impl.h"

HashSHA1Impl::HashSHA1Impl(void)
{

}

HashSHA1Impl::~HashSHA1Impl(void)
{
}
StdString HashSHA1Impl::GetStringHash(std::string strValue)
{
	Reset();
	int nLen = strValue.size();
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	Input(pBuf, nLen);
	unsigned int digest[5] = {0};
	Result(digest);
	TCHAR szRes[48] = _T("");
	_sntprintf_s(szRes, 48, 48, _T("%x%x%x%x%x"),
		digest[0], digest[1], digest[2], digest[3], digest[4]);
	return szRes;
}
StdString HashSHA1Impl::GetStringHash(std::wstring strValue)
{
	Reset();
	int nLen = strValue.size() * sizeof(wchar_t);
	const unsigned char* pBuf = (const unsigned char*)strValue.data();
	Input(pBuf, nLen);
	unsigned int digest[5] = {0};
	Result(digest);
	TCHAR szRes[48] = _T("");
	_sntprintf_s(szRes, 48, 48, _T("%x%x%x%x%x"),
		digest[0], digest[1], digest[2], digest[3], digest[4]);
	return szRes;
}
StdString HashSHA1Impl::GetFileHash(StdString strFile)
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
			
			Reset();
			Input(pByte, dwSize);
			unsigned int digest[5] = {0};
			Result(digest);
			TCHAR szRes[48] = _T("");
			_sntprintf_s(szRes, 48, 48, _T("%x%x%x%x%x"),
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
	return strRet;
}

