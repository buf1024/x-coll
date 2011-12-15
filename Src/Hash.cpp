/*
 * File       : Hash.cpp
 * Description: 计算Hash值的接口
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */


#include "Hash.h"

#include "md5.h"
#include "sha1.h"
#ifndef _MSC_VER
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#endif

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






/////////////////////////////////////////////////////
// MD5
HashMD5Impl::HashMD5Impl(void)
{
}

HashMD5Impl::~HashMD5Impl(void)
{
}

std::string HashMD5Impl::GetStringHash(std::string strValue)
{
    int nLen = strValue.size();
    const unsigned char* pBuf = (const unsigned char*)strValue.data();
    return ComputeHash(pBuf, nLen);
}

std::string HashMD5Impl::GetStringHash(std::wstring strValue)
{
    int nLen = strValue.size() * sizeof(wchar_t);
    const unsigned char* pBuf = (const unsigned char*)strValue.data();
    return ComputeHash(pBuf, nLen);
}
std::string HashMD5Impl::GetFileHash(std::string strFile)
{
    std::string strRet;
#ifdef _MSC_VER
    HANDLE hFile = CreateFileA(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
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
        CloseHandle(hFile);
    }
#else
    int fd = open(strFile.c_str(), O_RDONLY);
    if(fd != -1){
        lseek(fd, 0, SEEK_SET);
        off_t len = lseek(fd, 0, SEEK_END);
        void* pAddr = mmap(NullPtr, len, PROT_READ, MAP_PRIVATE, fd, 0);
        
        if (pAddr != MAP_FAILED)
        {
            strRet = ComputeHash((const unsigned char*)pAddr, len);
            munmap(pAddr, len);
        }

        close(fd);
    }
#endif
    return strRet;
}


std::string HashMD5Impl::ComputeHash(const unsigned char* pBuf, unsigned long lLen)
{
    unsigned char digest[16] = {0};

    MD5Context ctx;
    MD5Init(&ctx);
    MD5Update(&ctx, pBuf, lLen);	
    MD5Final(&ctx, digest);

    char szBuf[33] = {0};  //szBuf[32] = 0
    for (int i=0; i<16; i++)
    {
        int nValL = digest[i]&0x0F;
        int nValH = digest[i]>>4;
#ifdef _MSC_VER
        _snprintf_s(szBuf + i*2, 33 - i*2, 33 - i*2, "%x%x", nValH, nValL);
#else
        snprintf(szBuf + i*2, 33 - i*2, "%x%x", nValH, nValL);
#endif
    }

    return szBuf;
}

/////////////////////////////////////
// SHA1

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
#ifdef _MSC_VER
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
#ifdef _MSC_VER
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

#ifdef _MSC_VER

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
        CloseHandle(hFile);
    }
#else
    int fd = open(strFile.c_str(), O_RDONLY);
    if(fd != -1){
        lseek(fd, 0, SEEK_SET);
        off_t len = lseek(fd, 0, SEEK_END);
        void* pAddr = mmap(NullPtr, len, PROT_READ, MAP_PRIVATE, fd, 0);
        if (pAddr != MAP_FAILED)
        {
            m_pSHA1->Reset();
            m_pSHA1->Input((const char*)pAddr, len);
            unsigned int digest[5] = {0};
            m_pSHA1->Result(digest);
            char szRes[48] = "";
            snprintf(szRes, 48, "%x%x%x%x%x",
                digest[0], digest[1], digest[2], digest[3], digest[4]);
            strRet = szRes;
            munmap(pAddr, len);
        }
        close(fd);
    }
#endif

    return strRet;
}


////////////////////////////////////
// CRC32
HashCRC32Impl::HashCRC32Impl(void)
{
    Init_CRC32_Table();
}

HashCRC32Impl::~HashCRC32Impl(void)
{
}

std::string HashCRC32Impl::GetStringHash(std::string strValue)
{
    int nLen = strValue.size();
    const unsigned char* pBuf = (const unsigned char*)strValue.data();
    int nRes = Get_CRC(pBuf, nLen);
    char szBuf[16] = "";
    char szFormat[8] = "%x";
    if (nRes < 0)
    {
        strcpy(szFormat, "-%x");
        nRes = -nRes;
    }

#ifdef _MSC_VER
    _snprintf_s(szBuf, 16, 16, szFormat, nRes);
#else
    snprintf(szBuf, 16, szFormat, nRes);
#endif
    return szBuf;
}

std::string HashCRC32Impl::GetStringHash(std::wstring strValue)
{
    int nLen = strValue.size() * sizeof(wchar_t);
    const unsigned char* pBuf = (const unsigned char*)strValue.data();
    int nRes = Get_CRC(pBuf, nLen);	
    char szBuf[16] = "";
    char szFormat[8] = "%x";
    if (nRes < 0)
    {
        strcpy(szFormat, "-%x");
        nRes = -nRes;
    }

#ifdef _MSC_VER
    _snprintf_s(szBuf, 16, 16, szFormat, nRes);
#else
    snprintf(szBuf, 16, szFormat, nRes);
#endif

    return szBuf;
}

std::string HashCRC32Impl::GetFileHash(std::string strFile)
{
    std::string strRet;
#ifdef _MSC_VER
    HANDLE hFile = CreateFileA(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
        if (hMapping != INVALID_HANDLE_VALUE)
        {
            PBYTE pByte = (PBYTE)MapViewOfFile(hMapping, FILE_MAP_COPY, 0, 0, 0);
            unsigned long dwSize = GetFileSize(hFile, NULL);			
            int nRes = Get_CRC(pByte, dwSize);
            char szBuf[16] = "";
            char szFormat[8] = "%x";
            if (nRes < 0)
            {
                strcpy(szFormat, "-%x");
                nRes = -nRes;
            }
            _snprintf_s(szBuf, 16, 16, szFormat, nRes);
            strRet = szBuf;
            UnmapViewOfFile(pByte);
            CloseHandle(hMapping);
        }
        CloseHandle(hFile);
    }
#else
    int fd = open(strFile.c_str(), O_RDONLY);
    if(fd != -1){
        lseek(fd, 0, SEEK_SET);
        off_t len = lseek(fd, 0, SEEK_END);
        void* pAddr = mmap(NullPtr, len, PROT_READ, MAP_PRIVATE, fd, 0);
        if (pAddr != MAP_FAILED)
        {
            int nRes = Get_CRC((const unsigned char*)pAddr, len);
            char szBuf[16] = "";
            char szFormat[8] = "%x";
            if (nRes < 0)
            {
                strcpy(szFormat, "-%x");
                nRes = -nRes;
            }
            snprintf(szBuf, 16, szFormat, nRes);
            strRet = szBuf;
            munmap(pAddr, len);
        }
        close(fd);
    }
#endif
    return strRet;
}

// Call this function only once to initialize the CRC table.
void HashCRC32Impl::Init_CRC32_Table()
{
    // This is the official polynomial used by CRC-32 
    // in PKZip, WinZip and Ethernet. 
    unsigned long ulPolynomial = 0x04c11db7;

    // 256 values representing ASCII character codes.
    for(int i = 0; i <= 0xFF; i++)
    {
        crc32_table[i]=Reflect(i, 8) << 24;
        for (int j = 0; j < 8; j++)
            crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
        crc32_table[i] = Reflect(crc32_table[i], 32);
    }
}

// Reflection is a requirement for the official CRC-32 standard.
unsigned long HashCRC32Impl::Reflect(unsigned long ref, char ch)
{
    // Used only by Init_CRC32_Table()
    unsigned long value(0);

    // Swap bit 0 for bit 7
    // bit 1 for bit 6, etc.
    for(int i = 1; i < (ch + 1); i++)
    {
        if(ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}

// Once the lookup table has been filled in by the two functions above,
// this function creates all CRCs using only the lookup table.
int HashCRC32Impl::Get_CRC(const unsigned char* buffer, int nLen)
{
    // Start out with all bits set high.
    unsigned long  ulCRC(0xffffffff);
    while(nLen--)
        ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];
    // Exclusive OR the result with the beginning value.
    return ulCRC ^ 0xffffffff;
}






