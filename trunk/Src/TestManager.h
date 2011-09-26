/*
 * File       : TestManager.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTMANAGER_H_
#define TESTMANAGER_H_

#include "XBasicCore.h"
#include <list>

XBASIC_NAMEPACE_BEGIN

class UnitDummy;
class TestSuite;
class TestCase;

class XBASICAPI TestManager
{
protected:
    TestManager();
public:
    virtual ~TestManager();

public:
    TestSuite* GetGlobalSuite() const;
    void SetGlobalSuite(TestSuite* pSuite);

    int RunAllTests();
    void Init(int argc, char** argv);

    bool MatchFilter(TestCase* pTest);

    void AddDummy(UnitDummy* pDummy);
    void RemoveDummy(UnitDummy* pDummy);

    void AddFail(TestCase* pTest);

public:
    static TestManager* GetInst();

private:
    std::list<UnitDummy*> m_lstDummy;
    std::list<TestCase*> m_lstFailed;

    TestSuite* m_pGlobalSuite;

private:
    static TestManager* sm_pInst;

};

XBASIC_NAMESPACE_END

#endif /* TESTMANAGER_H_ */
