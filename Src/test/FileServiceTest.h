#pragma once
#include <cppunit.h>

class FileServieTest : public TestFixture
{
    CPPUNIT_TEST_SUITE(FileServieTest);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(testDir);
    CPPUNIT_TEST_SUITE_END();
public:
    FileServieTest();
    ~FileServieTest();
public:
    virtual void setup();
    virtual void tearDown();

public:
    void testFile();
    void testDir();
};