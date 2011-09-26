/*
 * File       : UnitDummy.cpp
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#include "TestDummy.h"
#include "TestManager.h"
#include "TestSuite.h"

USE_XBASIC_NAMESPACE;

UnitGlobalDummy::UnitGlobalDummy(TestSuite* pSuite)
{
     pSuite->SetName(_T("GlobalSuite"));
     TestManager* pInst = TestManager::GetInst();

     pInst->SetGlobalSuite(pSuite);
     pInst->AddDummy(this);

}
UnitGlobalDummy::~UnitGlobalDummy()
{

}

UnitSuiteFixtureUnitDummy::UnitSuiteFixtureUnitDummy(TestSuite* pSuite,
        TestFixture* pFixture, TestCase* pTestCase)
{

}
UnitSuiteFixtureUnitDummy::~UnitSuiteFixtureUnitDummy()
{

}

