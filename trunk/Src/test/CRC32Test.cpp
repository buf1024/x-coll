#include "StdAfx.h"
#include "CRC32Test.h"




CRC32Test::CRC32Test(void)
: pHash(NULL)
{
}

CRC32Test::~CRC32Test(void)
{
}

void CRC32Test::setUp()
{
	pHash = new Hash(new HashCRC32Impl);

}
void CRC32Test::tearDown()
{
	if(pHash)
		delete pHash;
}

void CRC32Test::testString()
{
	StdString strValue;
	strValue = pHash->GetStringHash("ABC");
	strValue = pHash->GetStringHash(_T("ABC"));
	strValue = pHash->GetStringHash("");
}
void CRC32Test::testFile()
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

CPPUNIT_TEST_SUITE_REGISTRATION(CRC32Test);