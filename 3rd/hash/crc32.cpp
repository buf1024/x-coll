#include "crc32.h"

CRC32::CRC32()
{
    Init_CRC32_Table();
}

CRC32::~CRC32()
{
}

// Call this function only once to initialize the CRC table.
void CRC32::Init_CRC32_Table()
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
unsigned long CRC32::Reflect(unsigned long ref, char ch)
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
int CRC32::Get_CRC(const unsigned char* buffer, int nLen)
{
	// Start out with all bits set high.
	unsigned long  ulCRC(0xffffffff);
	while(nLen--)
		ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];
	// Exclusive OR the result with the beginning value.
	return ulCRC ^ 0xffffffff;
}