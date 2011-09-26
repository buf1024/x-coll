/*
 * File       : TestManager.cpp
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#include "TestManager.h"
#include "TestDummy.h"
#include "TestSuite.h"
#include <algorithm>

USE_XBASIC_NAMESPACE;

TestManager* TestManager::sm_pInst = NullPtr;

TestManager::TestManager()
{
    // TODO Auto-generated constructor stub
    //m_pGlobalSuite = new TestSuite;
    //m_pGlobalSuite->SetName(_T("DefaultGlobalSuite"));
}

TestManager::~TestManager()
{
    // TODO Auto-generated destructor stub
    for(std::list<UnitDummy*>::iterator iter = m_lstDummy.begin();
            iter != m_lstDummy.end(); ++iter){
        delete *iter;
    }
    m_lstDummy.clear();
    delete m_pGlobalSuite;
}

TestSuite* TestManager::GetGlobalSuite() const
{
    return m_pGlobalSuite;
}
void TestManager::SetGlobalSuite(TestSuite* pSuite)
{
    if(m_pGlobalSuite != NullPtr){
        delete m_pGlobalSuite;
    }
    m_pGlobalSuite = pSuite;
}
int TestManager::RunAllTests()
{
    ASSERT(m_pGlobalSuite != NullPtr);
    m_pGlobalSuite->Run();

    return m_lstFailed.size();
}
void TestManager::Init(int argc, char** argv)
{

}
void TestManager::AddDummy(UnitDummy* pDummy)
{
    std::list<UnitDummy*>::iterator iter =
            std::find(m_lstDummy.begin(), m_lstDummy.end(), pDummy);
    if(iter == m_lstDummy.end()){
        m_lstDummy.push_back(pDummy);
    }
}
void TestManager::RemoveDummy(UnitDummy* pDummy)
{
    std::list<UnitDummy*>::iterator iter =
                std::find(m_lstDummy.begin(), m_lstDummy.end(), pDummy);
    if (iter != m_lstDummy.end()) {
        m_lstDummy.erase(iter);
    }
}

void TestManager::AddFail(TestCase* pTest)
{

}

bool TestManager::MatchFilter(TestCase* pTest)
{
    return false;
}

TestManager* TestManager::GetInst()
{
return NullPtr;
}
