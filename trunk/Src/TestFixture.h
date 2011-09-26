/*
 * File       : TestFixture.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTFIXTURE_H_
#define TESTFIXTURE_H_

#include "TestCase.h"

#include <map> // 为了有序

XBASIC_NAMEPACE_BEGIN

class XBASICAPI TestFixture: public TestCase
{
public:
    typedef std::map<StdString, TestCase*>::iterator TestIter;
public:
    TestFixture();
    virtual ~TestFixture();

public:
    virtual void Run();
    virtual void SetUp();
    virtual void TearDown();

public:
    void AddTest(TestCase* pTest);
    void RemoveTest(TestCase* pTest);

protected:
    std::map<StdString, TestCase*> m_mapTests;
};

XBASIC_NAMESPACE_END

#endif /* TESTFIXTURE_H_ */
