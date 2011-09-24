#include "StdAfx.h"
#include "MD5Test.h"




MD5Test::MD5Test(void)
: pHash(NULL)
{
}

MD5Test::~MD5Test(void)
{
}

void MD5Test::setUp()
{
	pHash = new Hash(new HashMD5Impl);

}
void MD5Test::tearDown()
{
	if(pHash)
		delete pHash;
}

void MD5Test::testString()
{
	StdString strValue;
	strValue = pHash->GetStringHash("ABC");
	strValue = pHash->GetStringHash(_T("ABC"));
	strValue = pHash->GetStringHash("");
}
void MD5Test::testFile()
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

CPPUNIT_TEST_SUITE_REGISTRATION(MD5Test);