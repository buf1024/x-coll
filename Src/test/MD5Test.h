#pragma once
#include <cppunit.h>
#include "hash.h"
#include "HashMD5Impl.h"

class MD5Test
	 : public TestFixture
{
	CPPUNIT_TEST_SUITE(MD5Test);
		CPPUNIT_TEST(testString);
		CPPUNIT_TEST(testFile);
	CPPUNIT_TEST_SUITE_END();
public:
	MD5Test(void);
	~MD5Test(void);
public:
	void setUp();
	void tearDown();

public:
	void testString();
	void testFile();
private:
	Hash *pHash;
};
