#include "IniConfig.h"
#include "TestCmmHdr.h"


USE_XBASIC_NAMESPACE;

class IniConfigTest : public testing::Test
{
public:
    void SetUp()
    {
        m_pConf = new IniConfig;
    }

    void TearDown()
    {
        delete m_pConf;
    }
public:
    static void SetUpTestCase()
    {
        printf("SetUpTestCase");
    }
    static void TearDownTestCase()
    {
        printf("TearDownTestCase");
    }
protected:
    IniConfig* m_pConf;
};


TEST_F(IniConfigTest, IniConfigLoad)
{
    m_pConf->Load("E:\\Private\\svn\\x-coll\\Code\\xbasic\\Src\\test\\conf.ini");

    m_pConf->Save("E:\\conf.ini");
    Section* pSecA = m_pConf->GetSection("seca");
    long lVal;
    bool b = pSecA->GetValue("knumber", lVal);
    double dVal;
    b = pSecA->GetValue("kdouble", dVal);

    Section* pSecB = m_pConf->GetSection("secb");
    b = pSecB->GetValue("knumber", lVal);
    bool bVal;
    b = pSecB->GetValue("ktrue", bVal);

    b = true;
}