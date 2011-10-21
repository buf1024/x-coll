// Config.cpp : 定义控制台应用程序的入口点。
//

#include "TestCmmHdr.h"
#include "Config.h"
#include "ConfigApp.h"

#include <stdio.h>

USE_XBASIC_NAMESPACE

class ConfigAppTest: public ::testing::Test
{
public:
    virtual void SetUp()
    {
        m_strTmpFile = tempnam(".", "ConfigApp");

        m_strTmpFile += ".xml";

        ConfigApp* pApp = new ConfigApp;
        pApp->SetEncoding("gb2312");
        pApp->SetStandalone("yes");

        Config* pConf = new Config("ConfigA"); 
        pConf->AddBoolValue("bool001", false);
        pConf->AddBoolValue("bool002", true);
        pConf->AddBoolValue("bool003", false);

        pConf->AddStringValue("string001", "我是中国人");
        pConf->AddStringValue("string002", "abc");
        pConf->AddStringValue("string003", "你好吧？");

        pConf->AddDWORDValue("dw001", 1L);
        pConf->AddDWORDValue("dw002", 2L);
        pConf->AddDWORDValue("dw003", 3L);  

        pConf->AddDoubleValue("double001", 1.0);
        pConf->AddDoubleValue("double002", 2.0);
        pConf->AddDoubleValue("double003", 3.0);
        pApp->AddConfig(pConf);


        pConf = new Config("ConfigB"); 
        pConf->AddBoolValue("bool001", false);
        pConf->AddBoolValue("bool002", true);
        pConf->AddBoolValue("bool003", false);

        pConf->AddStringValue("string001", "");
        pConf->AddStringValue("string002", "a");
        pConf->AddStringValue("string003", "b");

        pConf->AddDWORDValue("dw001", 1L);
        pConf->AddDWORDValue("dw002", 2L);
        pConf->AddDWORDValue("dw003", 3L);  

        pConf->AddDoubleValue("double001", 1.0);
        pConf->AddDoubleValue("double002", 2.0);
        pConf->AddDoubleValue("double003", 3.0);
        pApp->AddConfig(pConf);

        pApp->Save(m_strTmpFile);
        delete pApp;

    }
    virtual void TearDown()
    {

    }
protected:
    std::string m_strTmpFile;
};

TEST_F(ConfigAppTest, ConfigApp)
{
    ConfigApp* pApp = new ConfigApp;

    bool bRet = pApp->Load(m_strTmpFile);
    ASSERT(bRet);

    Config* pConf = pApp->GetConfig("ConfigA");
    ASSERT(pConf != NullPtr);
    bRet = pConf->GetBool("bool001");
    ASSERT(bRet == false);
    bRet = pConf->GetBool("bool002");
    ASSERT(bRet == true);
    bRet = pConf->GetBool("bool003");
    ASSERT(bRet == false);



    delete pApp;
}


