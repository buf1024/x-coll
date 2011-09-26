/*
 * File       : UnitDummy.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef UnitDummy_H_
#define UnitDummy_H_

#include "XBasicCore.h"


XBASIC_NAMEPACE_BEGIN

class TestSuite;
class TestFixture;
class TestCase;

class UnitDummy
{
public:
    UnitDummy(){}
    virtual ~UnitDummy(){}
};

class UnitSuiteFixtureUnitDummy : public UnitDummy
{
public:
    UnitSuiteFixtureUnitDummy(TestSuite* pSuite, TestFixture* pFixture, TestCase* pTestCase);
    virtual ~UnitSuiteFixtureUnitDummy();
};

class UnitGlobalDummy : public UnitDummy
{
public:
    UnitGlobalDummy(TestSuite* pSuite);
    virtual ~UnitGlobalDummy();
};

XBASIC_NAMESPACE_END


#endif /* UnitDummy_H_ */
