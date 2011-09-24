////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : HashCRC32Impl.h
// Purpose     : 
// Version     : 2010-11-13 15:19:12) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file HashCRC32Impl.h */

#ifndef _HASHCRC32IMPL_H_
#define _HASHCRC32IMPL_H_

#include "HashImpl.h"

class HashCRC32Impl :
    public HashImpl
{
public:
    HashCRC32Impl(void);
    ~HashCRC32Impl(void);
public:
    virtual StdString GetStringHash(std::string strValue);
    virtual StdString GetStringHash(std::wstring strValue);
    virtual StdString GetFileHash(StdString strFile);

private:
    void Init_CRC32_Table(); // Builds Lookup table array
    unsigned long Reflect(unsigned long ref, char ch); // Reflects CRC bits in the lookup table
    int Get_CRC(const unsigned char* buffer, int nLen); // Creates a CRC from a string buffer		
private:
    unsigned long crc32_table[256]; // Lookup table array
};

#endif