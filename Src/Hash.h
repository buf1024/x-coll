/*
 * File       : Hash.h
 * Description: 计算Hash值的接口
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#ifndef XBASIC_HASH_H_
#define XBASIC_HASH_H_

#include "XBasicCore.h"
#include "StdString.h"

class SHA1;

XBASIC_NAMEPACE_BEGIN

class HashImpl;
/**
 * 计算Hash值的接口
 */

class XBASICAPI Hash
{
public:
   /**
     * 构造函数，要提供某种HASH的实现
     * @param pImpl 某种HASH的实现
     */

    Hash(HashImpl* pImpl);
    ~Hash();
public:
    /**
     * 计算 ASCII 形式的字符串HASH值
     * @param strValue 要计算的字符串
     * @return HASH值
     */

    std::string GetStringHash(std::string strValue);
    /**
     * 计算宽字符形式的字符串HASH值e
     * @param strValue 要计算的字符串
     * @return HASH值
     */

    std::string GetStringHash(std::wstring strValue);
    /**
     * 计算文件的HASH值
     * @param strFile 文件的路径
     * @return HASH值, 如果文件不存在或者出错则返回空字符串
     */

    std::string GetFileHash(std::string strFile);
private:
    HashImpl* m_pImpl; /*< 具体的实现*/

};

class XBASICAPI HashImpl
{
public:
    HashImpl(){}
    virtual ~HashImpl(){}
public:
    virtual std::string GetStringHash(std::string strValue) = 0;
    virtual std::string GetStringHash(std::wstring strValue) = 0;
    virtual std::string GetFileHash(std::string strFile) = 0;

};

class XBASICAPI HashMD5Impl :
    public HashImpl
{
public:
    HashMD5Impl(void);
    ~HashMD5Impl(void);
public:
    virtual std::string GetStringHash(std::string strValue);
    virtual std::string GetStringHash(std::wstring strValue);
    virtual std::string GetFileHash(std::string strFile);

private:
    std::string ComputeHash(const unsigned char* pBuf, unsigned long lLen);
};

// Test Vectors (from FIPS PUB 180-1)
//
//  SHA1("abc") =
//      A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
//
//  SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
//      84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
//
//  SHA1(A million repetitions of "a") =
//      34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
//
class XBASICAPI HashSHA1Impl :
    public HashImpl
{
public:
    HashSHA1Impl(void);
    ~HashSHA1Impl(void);
public:
    virtual std::string GetStringHash(std::string strValue);
    virtual std::string GetStringHash(std::wstring strValue);
    virtual std::string GetFileHash(std::string strFile);
private:
    SHA1* m_pSHA1;
};

class XBASICAPI HashCRC32Impl :
    public HashImpl
{
public:
    HashCRC32Impl(void);
    ~HashCRC32Impl(void);
public:
    virtual std::string GetStringHash(std::string strValue);
    virtual std::string GetStringHash(std::wstring strValue);
    virtual std::string GetFileHash(std::string strFile);

private:
    void Init_CRC32_Table(); // Builds Lookup table array
    unsigned long Reflect(unsigned long ref, char ch); // Reflects CRC bits in the lookup table
    int Get_CRC(const unsigned char* buffer, int nLen); // Creates a CRC from a string buffer		
private:
    unsigned long crc32_table[256]; // Lookup table array
};


XBASIC_NAMESPACE_END


#endif /* XBASIC_HASH_H_ */


