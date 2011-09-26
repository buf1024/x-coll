/*
 * File       : TestFixture.cpp
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#include "TestFixture.h"

USE_XBASIC_NAMESPACE;

TestFixture::TestFixture()
{
    // TODO Auto-generated constructor stub

}

TestFixture::~TestFixture()
{
    // TODO Auto-generated destructor stub
}

void TestFixture::Run()
{
    SetUp();
    TearDown();
}
void TestFixture::SetUp()
{

}
void TestFixture::TearDown()
{

}

void TestFixture::AddTest(TestCase* pTest)
{
    ASSERT(pTest != NullPtr);
    StdString strName = pTest->GetName();
    if(m_mapTests.find(strName) == m_mapTests.end()){
        m_mapTests.insert(std::make_pair(strName, pTest));
    }
}
void TestFixture::RemoveTest(TestCase* pTest)
{
    ASSERT(pTest != NullPtr);
    TestIter iter = m_mapTests.find(pTest->GetName());
    if(iter != m_mapTests.end()){
        m_mapTests.erase(iter);
    }
}
