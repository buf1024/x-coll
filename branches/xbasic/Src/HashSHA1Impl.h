/*
 * File       : HashSHA1Impl.h
 * Description: 
 * Version    : 2010-11-13 Created
 * Author     : buf1024@gmail.com
 */

#ifndef _HASHSHA1IMPL_H_
#define _HASHSHA1IMPL_H_

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

#include "HashImpl.h"
#include "sha1.h"

XBASIC_NAMEPACE_BEGIN

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

XBASIC_NAMESPACE_END

#endif