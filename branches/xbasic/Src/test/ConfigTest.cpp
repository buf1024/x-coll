// Config.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Config.h"
#include "ConfigApp.h"
#include "ConfigTest.h"

ConfigTest::ConfigTest()
{

}
ConfigTest::~ConfigTest()
{

}

void ConfigTest::setup()
{

}
void ConfigTest::tearDown()
{

}

void ConfigTest::testConfig()
{
    ConfigApp* pApp = new ConfigApp;
    
    Config* pConf = new Config(_T("Config 001")); 
    pConf->AddBoolValue(_T("bool001"), false);
    pConf->AddBoolValue(_T("bool002"), true);
    pConf->AddBoolValue(_T("bool003"), false);

    pConf->AddStringValue(_T("string001"), _T("我是中国人"));
    pConf->AddStringValue(_T("string002"), _T("a"));
    pConf->AddStringValue(_T("string003"), _T("你好吧？"));

    pConf->AddDWORDValue(_T("dw001"), 2L);
    pConf->AddDWORDValue(_T("dw002"), 3L);
    pConf->AddDWORDValue(_T("dw003"), 23L);    
    pApp->AddConfig(pConf);


    pConf = new Config(_T("Config 002")); 
    pConf->AddBoolValue(_T("bool001"), false);
    pConf->AddBoolValue(_T("bool002"), true);
    pConf->AddBoolValue(_T("bool003"), false);

    pConf->AddStringValue(_T("string001"), _T(""));
    pConf->AddStringValue(_T("string002"), _T("a"));
    pConf->AddStringValue(_T("string003"), _T("b"));

    pConf->AddDWORDValue(_T("dw001"), 2L);
    pConf->AddDWORDValue(_T("dw002"), 3L);
    pConf->AddDWORDValue(_T("dw003"), 23L);  
    pApp->AddConfig(pConf);

    pApp->Save(_T("test.xml"));
    delete pApp;

    pApp = new ConfigApp;
    pApp->Load(_T("test.xml"));
    pConf = pApp->GetConfig(_T("Config 001"));
    CPPUNIT_ASSERT(pConf->GetBool(_T("bool001")) == false);
    CPPUNIT_ASSERT(pConf->GetBool(_T("bool003")) == false);
    pConf = pApp->GetConfig(_T("Config 002"));
    CPPUNIT_ASSERT(pConf->GetString(_T("string002")) == _T("a"));
    CPPUNIT_ASSERT(pConf->GetString(_T("string003")) == _T("b"));
    CPPUNIT_ASSERT(pConf->GetDoubleWorld(_T("dw002")) == 3L);
    delete pApp;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ConfigTest);

