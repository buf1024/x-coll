#pragma once
#include <cppunit.h>
#include "hash.h"
#include "HashCRC32Impl.h"

class CRC32Test
	: public TestFixture
{
	CPPUNIT_TEST_SUITE(CRC32Test);
	CPPUNIT_TEST(testString);
	CPPUNIT_TEST(testFile);
	CPPUNIT_TEST_SUITE_END();
public:
	CRC32Test(void);
	~CRC32Test(void);
public:
	void setUp();
	void tearDown();

public:
	void testString();
	void testFile();
private:
	Hash *pHash;
};
