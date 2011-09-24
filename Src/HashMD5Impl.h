////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : HashMD5Impl.h
// Purpose     : 
// Version     : 2010-11-13 15:19:30 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file HashMD5Impl.h */
#ifndef _HASHMD5IMPL_H_
#define _HASHMD5IMPL_H_

#include "HashImpl.h"


class HashMD5Impl :
    public HashImpl
{
public:
    HashMD5Impl(void);
    ~HashMD5Impl(void);
public:
    virtual StdString GetStringHash(std::string strValue);
    virtual StdString GetStringHash(std::wstring strValue);
    virtual StdString GetFileHash(StdString strFile);

private:
    StdString ComputeHash(const unsigned char* pBuf, unsigned long lLen);
};
#endif