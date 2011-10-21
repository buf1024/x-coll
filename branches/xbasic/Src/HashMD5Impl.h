/*
 * File       : HashMD5Impl.h
 * Description: 
 * Version    : 2010-11-13 Created
 * Author     : buf1024@gmail.com
 */
#ifndef _HASHMD5IMPL_H_
#define _HASHMD5IMPL_H_

#include "HashImpl.h"

XBASIC_NAMEPACE_BEGIN

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

XBASIC_NAMESPACE_END

#endif
