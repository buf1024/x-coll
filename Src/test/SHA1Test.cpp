#include "StdAfx.h"
#include "SHA1Test.h"




SHA1Test::SHA1Test(void)
: pHash(NULL)
{
}

SHA1Test::~SHA1Test(void)
{
}

void SHA1Test::setUp()
{
	pHash = new Hash(new HashSHA1Impl);

}
void SHA1Test::tearDown()
{
	if(pHash)
		delete pHash;
}

void SHA1Test::testString()
{
	StdString strValue;
	// Test Vectors (from FIPS PUB 180-1)
	//
	//  SHA1("abc") =
	//      A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
	//
	//  SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
	//      84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
	//
	strValue = pHash->GetStringHash("abc");
	strValue = pHash->GetStringHash("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
	strValue = pHash->GetStringHash(_T("ABC"));
	strValue = pHash->GetStringHash("");
}
void SHA1Test::testFile()
{
	//Test Existing file
	StdString strFile(_T("C:\\WINDOWS\\system32\\cmd.exe"));
	StdString strValue = pHash->GetFileHash(strFile);
	strFile = _T("Z:\\a.TXT");
	strValue = pHash->GetFileHash(strFile);
	//Test Unexisting file
	strFile = _T("XX.xx");
	strValue = pHash->GetFileHash(strFile);
	CPPUNIT_ASSERT(strValue == _T(""));
}

CPPUNIT_TEST_SUITE_REGISTRATION(SHA1Test);