/*
 * File       : HashCRC32Impl.h
 * Description: 
 * Version    : 2010-11-13 Created
 * Author     : buf1024@gmail.com
 */

#ifndef _HASHCRC32IMPL_H_
#define _HASHCRC32IMPL_H_


#include "HashImpl.h"

XBASIC_NAMEPACE_BEGIN

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

#endif
