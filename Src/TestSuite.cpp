/*
 * File       : TestSuite.cpp
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#include "TestSuite.h"

USE_XBASIC_NAMESPACE;

TestSuite::TestSuite()
{
    // TODO Auto-generated constructor stub

}

TestSuite::~TestSuite()
{
    // TODO Auto-generated destructor stub
}

void TestSuite::Run()
{
    SetUp();
    for(TestIter iter = m_mapTests.begin();
            iter != m_mapTests.end(); ++iter){
        TestCase* pTest = iter->second;
        pTest->Run();
    }
    TearDown();
}
void TestSuite::SetUp()
{

}
void TestSuite::TearDown()
{

}
void TestSuite::Attach(TestSuite*& pSuite)
{
    if(pSuite != NullPtr){
        delete pSuite;
    }
    pSuite = this;
}
