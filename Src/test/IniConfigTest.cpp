#include "StdAfx.h"
#include "IniConfigTest.h"
#include "IniConfig.h"

#pragma warning(disable:4996)

IniConfigTest::IniConfigTest()
{
	m_pSection = new Section;
	m_pConfig = new IniConfig;
}
IniConfigTest::~IniConfigTest()
{
	delete m_pSection;
	delete m_pConfig;
}

void IniConfigTest::setup()
{
	
}
void IniConfigTest::tearDown()
{
	
}

void IniConfigTest::testSectionSetterGetter()
{
	m_pSection->SetSectionName(_T("AppSection"));
	CPPUNIT_ASSERT(m_pSection->GetSectionName() == _T("AppSection"));

	m_pSection->Insert(_T("AKey"), _T("AValue"));
	m_pSection->Insert(_T("BKey"), _T("BValue"));
	m_pSection->Insert(_T("CKey"), _T("CValue"));
	m_pSection->Insert(_T(""), _T("DValue"));
	m_pSection->Insert(_T("DKey"), _T(""));

	StdString strValue;
	m_pSection->GetValue(_T("AKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("AValue"));
	m_pSection->GetValue(_T("BKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("BValue"));
	m_pSection->GetValue(_T("CKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("CValue"));
	strValue = _T("");
	m_pSection->GetValue(_T(""), strValue);
	CPPUNIT_ASSERT(strValue == _T(""));
	m_pSection->GetValue(_T("DKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T(""));

	m_pSection->Insert(_T("AKey"), _T("ARValue"));
	m_pSection->GetValue(_T("AKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("ARValue"));

	m_pSection->Insert(_T("EKey"), 0);
	m_pSection->Insert(_T("FKey"), 1L);
	m_pSection->Insert(_T("GKey"), _T('2'));
	m_pSection->Insert(_T("HKey"), 3.0);
	m_pSection->Insert(_T("IKey"), 4.0f);

	m_pSection->GetValue(_T("EKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("0"));
	m_pSection->GetValue(_T("FKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("1"));
	m_pSection->GetValue(_T("GKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("2"));
	m_pSection->GetValue(_T("HKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("3.000000"));
	m_pSection->GetValue(_T("IKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("4.000000"));

}
void IniConfigTest::testSectionPersistance()
{
	m_pSection->Empty();
	m_pSection->SetSectionName(_T("Test"));
	m_pSection->Insert(_T("AKey"), _T("AValue"));
	m_pSection->Insert(_T("BKey"), _T("BValue"));
	m_pSection->Insert(_T("CKey"), _T("CValue"));
	m_pSection->Insert(_T("DKey"), _T(""));

    TCHAR* pTmp = _ttempnam(_tgetenv(_T("Temp")), _T("lgc"));
	StdString strPath = pTmp;
    if (pTmp)
    {
        free(pTmp);
    }
    
	strPath.append(_T(".ini"));
	m_pSection->Save(strPath);
	m_pSection->Empty();
	m_pSection->SetSectionName(_T("Test"));
	m_pSection->Load(strPath);

	StdString strValue;
	m_pSection->GetValue(_T("AKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("AValue"));
	m_pSection->GetValue(_T("BKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("BValue"));
	m_pSection->GetValue(_T("CKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("CValue"));
	m_pSection->GetValue(_T("DKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T(""));


}

void IniConfigTest::testIniConfigSetterGetter()
{

}
void IniConfigTest::testIniConfigPersistance()
{
	Section* pSec = new Section(_T("SecA"));
	pSec->Insert(_T("AKey"), _T("AValue"));
	pSec->Insert(_T("BKey"), _T("BValue"));
	pSec->Insert(_T("CKey"), _T("CValue"));
	pSec->Insert(_T("DKey"), _T(""));
	m_pConfig->Insert(pSec);

	pSec = new Section(_T("SecB"));
	pSec->Insert(_T("AKey"), _T("EValue"));
	pSec->Insert(_T("BKey"), _T("FValue"));
	pSec->Insert(_T("CKey"), _T("GValue"));
	pSec->Insert(_T("DKey"), _T(""));
	m_pConfig->Insert(pSec);

    TCHAR* pTmp = _ttempnam(_tgetenv(_T("Temp")), _T("lgc"));
    StdString strPath = pTmp;
    if (pTmp)
    {
        free(pTmp);
    }
	strPath.append(_T(".ini"));
	m_pConfig->Save(strPath);

	m_pConfig->Delete(_T("SecA"));
	m_pConfig->Delete(_T("SecB"));
	m_pConfig->Load(strPath);
	
	StdString strValue;
	pSec = m_pConfig->GetSection(_T("SecA"));
	pSec->GetValue(_T("AKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("AValue"));
	pSec->GetValue(_T("BKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("BValue"));
	pSec->GetValue(_T("CKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("CValue"));
	pSec->GetValue(_T("DKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T(""));

	pSec = m_pConfig->GetSection(_T("SecB"));
	pSec->GetValue(_T("AKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("EValue"));
	pSec->GetValue(_T("BKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("FValue"));
	pSec->GetValue(_T("CKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T("GValue"));
	pSec->GetValue(_T("DKey"), strValue);
	CPPUNIT_ASSERT(strValue == _T(""));
}

CPPUNIT_TEST_SUITE_REGISTRATION(IniConfigTest);