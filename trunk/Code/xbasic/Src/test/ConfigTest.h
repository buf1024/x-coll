#pragma once
#include <cppunit.h>

class ConfigTest : public TestFixture
{
    CPPUNIT_TEST_SUITE(ConfigTest);
    CPPUNIT_TEST(testConfig);
    CPPUNIT_TEST_SUITE_END();
public:
    ConfigTest();
    ~ConfigTest();
public:
    virtual void setup();
    virtual void tearDown();

public:
    void testConfig();

};