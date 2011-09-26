/*
 * File       : UnitTest.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "TestCase.h"
#include "TestFixture.h"
#include "TestSuite.h"
#include "TestManager.h"
#include "TestDummy.h"
#include "TestAssert.h"

USE_XBASIC_NAMESPACE;

#define TEST_S(S, F, T)                                                                  \
    class S##_##F##_##T##_Test : public TestCase                                         \
    {                                                                                    \
    public:                                                                              \
        virtual ~S##_##F##_##T##_Test();                                                 \
        void Run();                                                                      \
    };                                                                                   \
    UnitSuiteFixtureUnitDummy* p_##S##_##F##_##T##_Dummy =                               \
        new UnitSuiteFixtureUnitDummy(new S, new F, new S##_##F##_##T##_Test);           \
    S##_##F##_##T##_Test::~S##_##F##_##T##_Test(){}                                      \
    void S##_##F##_##T##_Test::Run()                                                     \

#define TEST_F(F, T)                                                                     \
    TEST_S(TestSuite, F, T)                                                              \

#define TEST(T)                                                                          \
    TEST_F(TestFixture, T)                                                               \

#define DECL_GLOBAL(S)                                                                   \
    UnitGlobalDummy* pUnitGlobal_##S##_Dummy = new UnitGlobalDummy(new S);               \

#define INIT_TEST(argc, argv)                                                            \
        TestManager::GetInst()->Init(argc, argv);                                        \

#define RUN_ALL_TESTS()                                                                  \
        TestManager::GetInst()->RunAllTests();                                           \

#endif /* UNITTEST_H_ */
