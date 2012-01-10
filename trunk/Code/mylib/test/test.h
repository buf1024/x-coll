/*
 * File       : Test.h
 * Description: Very Very Simple Test
 * Version    : 2011-9-1 Created
 * Author     : Luo Guochun
 */

#ifndef TEST_H_
#define TEST_H_

#include <list>
#include <string>
#include <map>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

class Util
{
public:
    static long long GetCurTimeMS()
    {
        struct timeval tp;
        gettimeofday(&tp, 0);
        long long m = (tp.tv_usec + tp.tv_sec * 1000000);
        return m;
    }
};


class Test
{
protected:
    Test()
    {
    }
public:
    virtual ~Test()
    {
    }

public:
    virtual void SetUp()
    {

    }
    virtual void TearDown()
    {

    }
    virtual void Run()
    {
    }

    std::string GetName() const
    {
        return m_strName;
    }
    std::string GetTestCaseName() const
    {
        return m_strTCName;
    }

protected:
    std::string m_strName;
    std::string m_strTCName;

};

class TestCase
{
public:
    TestCase(std::string strName) :
            m_strName(strName)
    {

    }
    virtual ~TestCase()
    {

    }


public:
    std::string GetName() const
    {
        return m_strName;
    }
    std::map<std::string, Test*>& GetTests()
    {
        return m_mapTests;
    }
    void AddTest(Test* pTest)
    {
        m_mapTests.insert(std::make_pair(pTest->GetName(), pTest));
    }
private:
    std::string m_strName;
    std::map<std::string, Test*> m_mapTests;
};

class TestManager
{
private:
    TestManager(){}
public:
    static TestManager* GetInst()
    {
        static TestManager* pInst = NULL;
        if(pInst == NULL){
            pInst = new TestManager;
            printf ("xx");
        }
        return pInst;
    }
public:
    void InitTest(int argc, char** argv)
    {
        for(int i=1; i<argc; i++){
            m_strFilter = argv[i];
        }
    }
    void RegTest(Test* pTest)
    {
        TestCase* pTC = GetTestCase(pTest->GetTestCaseName());
        pTC->AddTest(pTest);
    }
    int RunAllTest()
    {
        if(!m_strFilter.empty()){
            std::cout << "!!!NOTE!!! FILTER=" << m_strFilter << std::endl;
        }
        int nSuccess = 0;
        int nCount = 0;
        long long t1 = Util::GetCurTimeMS();
        for(std::map<std::string, TestCase*>::iterator iter = m_mapTestCases.begin();
                iter != m_mapTestCases.end(); ++iter){
            TestCase* pTC = iter->second;
            if (MatchFilter(pTC)) {
                std::list<Test*> lstTests;
                for (std::map<std::string, Test*>::iterator iterTest =
                        pTC->GetTests().begin();
                        iterTest != pTC->GetTests().end(); ++iterTest) {
                    Test* pTest = iterTest->second;
                    if (MatchFilter(pTest)) {
                        lstTests.push_back(pTest);
                    }
                }
                if (lstTests.size() > 0) {
                    std::cout << "[=========] " << "Run testcase "
                            << pTC->GetName() << std::endl;
                    long long tc1 = Util::GetCurTimeMS();
                    for (std::list<Test*>::iterator iterTest = lstTests.begin();
                            iterTest != lstTests.end(); ++iterTest) {
                        Test* pTest = *iterTest;
                        nCount++;
                        std::cout << "[ RUN     ] " << pTC->GetName() << "."
                                << pTest->GetName() << std::endl;
                        long long tt1 = Util::GetCurTimeMS();
                        pTest->Run();
                        long long tt2 = Util::GetCurTimeMS();
                        if (!IsTestPass(pTest)) {
                            std::cout << "[ FAILED  ] " << pTC->GetName() << "."
                                    << pTest->GetName() << " "
                                    << (tt2 - tt1) / 1000.0 << "ms"
                                    << std::endl;
                        } else {
                            std::cout << "[      OK ] " << pTC->GetName() << "."
                                    << pTest->GetName() << " "
                                    << (tt2 - tt1) / 1000.0 << "ms"
                                    << std::endl;
                            nSuccess++;
                        }

                    }
                    long long tc2 = Util::GetCurTimeMS();
                    std::cout << "[=========] " << "Run testcase "
                            << pTC->GetName() << " " << (tc2 - tc1) / 1000.0
                            << "ms" << std::endl << std::endl;
                }

            }
        }
        long long t2 = Util::GetCurTimeMS();
        std::cout << "[=========] " << "Run " << nCount << " test(s) " <<
                (t2 - t1)/1000.0 << "ms"<< std::endl;
        if(nSuccess > 0){
            std::cout << "[ PASSED  ] " << nSuccess <<" test(s)" << std::endl;
        }
        if(nCount - nSuccess > 0){
            std::cout << "[ FAILED  ] " << nCount - nSuccess <<" test(s) list bellow" << std::endl;
            for(std::map<std::string, Test*>::iterator iter = m_mapFailedTests.begin();
                    iter != m_mapFailedTests.end(); ++iter){
                Test* pTest = iter->second;
                std::cout << "[ FAILED  ] " << pTest->GetTestCaseName() << "." <<
                        pTest->GetName() << std::endl;
            }

        }
        std::cout << "[=========] " << "Finish" << std::endl;

        if(nCount == 0) return 0;
        if(nCount == nSuccess) return 0;
        return nCount - nSuccess;
    }
    void CleanUp()
    {
        for(std::map<std::string, TestCase*>::iterator iter = m_mapTestCases.begin();
                iter != m_mapTestCases.end(); ++iter)
        {
            delete iter->second;
        }
        m_mapTestCases.clear();
        m_mapFailedTests.clear();
    }

    void AddFailedTest(Test* pTest)
    {
        std::string strKey = pTest->GetTestCaseName() + "." + pTest->GetName();
        m_mapFailedTests.insert(std::make_pair(strKey, pTest));
    }

private:
    TestCase* GetTestCase(std::string strName)
    {
        TestCase* pTC = NULL;
        std::map<std::string, TestCase*>::iterator iter = m_mapTestCases.find(strName);
        if(iter == m_mapTestCases.end()){
            pTC = new TestCase(strName);
            m_mapTestCases.insert(std::make_pair(strName, pTC));
        }else{
            pTC = iter->second;
        }
        return pTC;
    }
    bool MatchFilter(Test* pTest)
    {
        if(m_strFilter.empty()){
            return true;
        }
        std::string strKey = pTest->GetTestCaseName() + "." + pTest->GetName();
        std::string::size_type idx = m_strFilter.find('*');
        if(idx == std::string::npos){
            if(m_strFilter == strKey){
                return true;
            }
        }else{
            std::string strFilterPref = m_strFilter.substr(0, idx);
            if(pTest->GetTestCaseName() + "." == strFilterPref){
                return true;
            }
        }
        return false;
    }
    bool MatchFilter(TestCase* pTest)
    {
        if(m_strFilter.empty()){
            return true;
        }
        std::string strKey = pTest->GetName() + ".";
        std::string::size_type idx = m_strFilter.find('*');
        if(idx != std::string::npos){
            std::string strFilterPref = m_strFilter.substr(0, idx);
            if(strKey == strFilterPref){
                return true;
            }
        }else{
            return true;
        }
        return false;
    }
    bool IsTestPass(Test* pTest)
    {
        std::string strKey = pTest->GetTestCaseName() + "." + pTest->GetName();
        std::map<std::string, Test*>::iterator iter = m_mapFailedTests.find(strKey);
        if(iter != m_mapFailedTests.end())
        {
            return false;
        }
        return true;
    }
private:
    std::map<std::string, TestCase*> m_mapTestCases;
    std::map<std::string, Test*> m_mapFailedTests;
    std::string m_strFilter;
};

#define TEST_F(TestCase, TestName)                                                      \
    class TestCase##_##TestName##_Test : public TestCase                                \
    {                                                                                   \
    public:                                                                             \
        TestCase##_##TestName##_Test(){                                                 \
            m_strTCName = #TestCase;                                                    \
            m_strName = #TestName;                                                      \
            TestManager::GetInst()->RegTest(this);                                      \
        }                                                                               \
        virtual void Run(){                                                             \
            SetUp();                                                                    \
            RunMyTest();                                                                \
            TearDown();                                                                 \
        }                                                                               \
        void RunMyTest();                                                               \
    };                                                                                  \
    TestCase##_##TestName##_Test* pDummy##TestCase##_##TestName##_Test  =               \
                                                  new TestCase##_##TestName##_Test;     \
    void TestCase##_##TestName##_Test::RunMyTest()                                      \


#define TEST(TestCase, TestName)                                                        \
    class TestCase##_##TestName##_Test : public Test                                    \
    {                                                                                   \
    public:                                                                             \
        TestCase##_##TestName##_Test(){                                                 \
            m_strTCName = #TestCase;                                                    \
            m_strName = #TestName;                                                      \
            TestManager::GetInst()->RegTest(this);                                      \
        }                                                                               \
        virtual void Run(){                                                             \
            SetUp();                                                                    \
            RunMyTest();                                                                \
            TearDown();                                                                 \
        }                                                                               \
        void RunMyTest();                                                               \
    };                                                                                  \
    TestCase##_##TestName##_Test* pDummy##TestCase##_##TestName##_Test  =               \
                                                  new TestCase##_##TestName##_Test;     \
    void TestCase##_##TestName##_Test::RunMyTest()                                      \


#define INIT_TEST(a, b) {                                                               \
    TestManager::GetInst()->InitTest(a, b);                                             \
   }                                                                                    \


#define RUN_ALL_TEST()                                                                  \
    int nxxxxxxxXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX = \
    TestManager::GetInst()->RunAllTest();                                               \
    TestManager::GetInst()->CleanUp();                                                  \
    return                                                                              \
          nxxxxxxxXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;\


#define EXPECT_EQ(a, b)   {                                                             \
    if(a != b) {                                                                        \
        printf("[W]File: %s Line:%d expect: %lld actual: %lld\n", __FILE__, __LINE__, (long long)a, (long long)b); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
    }                                                                                   \
}                                                                                       \

#define EXPECT_STREQ(a, b) {                                                            \
    if(strncmp(a, b, strlen(a)) != 0) {                                                 \
        printf("[W]File: %s Line:%d expect: %s actual: %s\n", __FILE__, __LINE__, a, b);\
        TestManager::GetInst()->AddFailedTest(this);                                    \
    }                                                                                   \
}                                                                                       \

#define EXPECT_TRUE(a) {                                                                \
    if(!((int)a)){                                                                      \
        printf("[W]File: %s Line:%d expect: TRUE actual: FALSE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
    }                                                                                   \
}                                                                                       \

#define EXPECT_FALSE(a) {                                                               \
    if((int)a){                                                                         \
        printf("[W]File: %s Line:%d expect: FALSE actual: TRUE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
    }                                                                                   \
}                                                                                       \

#define ASSERT_EQ(a, b) {                                                               \
    if(a != b) {                                                                        \
        printf("[E]File: %s Line:%d expect: %lld actual: %lld\n", __FILE__, __LINE__, (long long)a, (long long)b); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_STREQ(a, b) {                                                            \
    if(strncmp(a, b, strlen(a)) != 0) {                                                 \
        printf("[E]File: %s Line:%d expect: %s actual: %s\n", __FILE__, __LINE__, a, b);\
        TestManager::GetInst()->AddFailedTest(this);                                    \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_TRUE(a) {                                                                \
    if(!((int)a)){                                                                      \
        printf("[E]File: %s Line:%d expect: TRUE actual: FALSE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_FALSE(a) {                                                               \
    if((int)a){                                                                         \
        printf("[E]File: %s Line:%d expect: FALSE actual: TRUE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFailedTest(this);                                    \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \


#endif /* TEST_H_ */
