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
    m_pConf->Load(_T("E:\\Private\\svn\\x-coll\\Src\\test\\conf001.ini"));

    m_pConf->Save(_T("E:\\conf.ini"));
    Section* pSecA = m_pConf->GetSection(_T("seca"));
    long lVal;
    bool b = pSecA->GetValue(_T("knumber"), lVal);
    double dVal;
    b = pSecA->GetValue(_T("kdouble"), dVal);

    Section* pSecB = m_pConf->GetSection(_T("secb"));
    b = pSecB->GetValue(_T("knumber"), lVal);
    bool bVal;
    b = pSecB->GetValue(_T("ktrue"), bVal);

    b = true;
}