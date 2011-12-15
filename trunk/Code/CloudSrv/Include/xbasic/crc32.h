#ifndef _CRC32_H_
#define _CRC32_H_

class CRC32
{
public:
    CRC32();
    ~CRC32();
public:
    int Get_CRC(const unsigned char* buffer, int nLen); // Creates a CRC from a string buffer
private:
    void Init_CRC32_Table(); // Builds Lookup table array
    unsigned long Reflect(unsigned long ref, char ch); // Reflects CRC bits in the lookup table    		
private:
    unsigned long crc32_table[256]; // Lookup table array
};
#endif
