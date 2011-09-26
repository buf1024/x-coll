/*
 * File       : TestSuite.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTSUITE_H_
#define TESTSUITE_H_

#include "TestFixture.h"

#include <list>

XBASIC_NAMEPACE_BEGIN

class XBASICAPI TestSuite: public TestFixture
{
public:
    TestSuite();
    virtual ~TestSuite();

public:
    virtual void Run();
    virtual void SetUp();
    virtual void TearDown();

    void Attach(TestSuite*& pSuite);

private:
    std::list<TestCase*> m_lstFailed;
};

XBASIC_NAMESPACE_END

#endif /* TESTSUITE_H_ */
