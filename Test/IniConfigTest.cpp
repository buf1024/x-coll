#include "IniConfig.h"
#include "TestCmmHdr.h"

#include <stdio.h>

USE_XBASIC_NAMESPACE

class IniConfigTest : public testing::Test
{
public:
    void SetUp()
    {
        IniConfig ini;
        m_strTmpFile = tempnam(".", "IniConfig");
        Section* pSec = new Section("SecA");
        pSec->Insert("num", 100);
        pSec->Insert("str", "\\$abc/$PYTHON/he\\$llo/$_/$PYTHON/$GVIM");
        pSec->Insert("bool", "true");
        ini.Insert(pSec);
        
        pSec = new Section("SecB");
        pSec->Insert("num", 200);
        pSec->Insert("str", "hello");
        pSec->Insert("bool", "false");
        ini.Insert(pSec);

        ini.Save(m_strTmpFile);

    }

    void TearDown()
    {
    }
public:
    static void SetUpTestCase()
    {
    }
    static void TearDownTestCase()
    {
    }
protected:
    std::string m_strTmpFile;
};


TEST_F(IniConfigTest, IniConfig)
{
    IniConfig ini;
    ini.Load(m_strTmpFile);

    Section* pSec = ini.GetSection("SecA");
    ASSERT(pSec != NullPtr);
    
    long lVal;
    bool b = pSec->GetValue("num", lVal);
    ASSERT(b);
    ASSERT(lVal == 100);
    
    std::string str;
    b = pSec->GetValue("str", str);
    ASSERT(b);
    ASSERT(str == "hello");

    bool bVal;
    b = pSec->GetValue("bool", bVal);
    ASSERT(b);
    ASSERT(bVal);

    pSec = ini.GetSection("SecB");
    ASSERT(pSec != NullPtr);

    b = pSec->GetValue("num", lVal);
    ASSERT(b);
    ASSERT(lVal == 200);


    b = pSec->GetValue("str", str);
    ASSERT(b);
    ASSERT(str == "hello");

    b = pSec->GetValue("bool", bVal);
    ASSERT(b);
    ASSERT(bVal == false);

    pSec = ini.GetSection("SecC");
    ASSERT(pSec == NullPtr);
}

