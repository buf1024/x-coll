#pragma once
#include <cppunit.h>

class Section;
class IniConfig;
class IniConfigTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(IniConfigTest);
		CPPUNIT_TEST(testSectionSetterGetter);
		CPPUNIT_TEST(testSectionPersistance);
		CPPUNIT_TEST(testIniConfigSetterGetter);
		CPPUNIT_TEST(testIniConfigPersistance);
	CPPUNIT_TEST_SUITE_END();
public:
	IniConfigTest();
	~IniConfigTest();
public:
	virtual void setup();
	virtual void tearDown();

public:
	void testSectionSetterGetter();
	void testSectionPersistance();

	void testIniConfigSetterGetter();
	void testIniConfigPersistance();
private:
	Section* m_pSection;
	IniConfig* m_pConfig;
	
};