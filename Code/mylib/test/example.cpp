// Copyright 1985-2012 Luo Guochun, http://imlgc.com
#include <iostream>
#include "test.h"

class MyEnvironment: public Environment
{
public:
    virtual void SetUp()
    {
        std::cout << "MyEnvironment::SetUp" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "MyEnvironment::TearDown" << std::endl;
    }
};

class MyTestFixture : public Test
{
public:
    static void SetUpTestCase()
    {
        std::cout << "MyTestFixture::SetUpTestCase" << std::endl;
    }
    static void TearDownTestCase()
    {
        std::cout << "MyTestFixture::TearDownTestCase" << std::endl;
    }
    virtual void SetUp()
    {
        std::cout << "MyTestFixture::SetUp" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "MyTestFixture::TearDown" << std::endl;
    }
};

TEST_F(MyTestFixture, MyCase1)
{
    ASSERT_TRUE(1);
}
TEST_F(MyTestFixture, MyCase2)
{
    ASSERT_TRUE(1);
}

TEST(MyDummyTestFixture, MyCase)
{
    ASSERT_TRUE(1);
}

int main(int argc, char** argv)
{
    SET_ENVIRONMENT(new MyEnvironment());
    INIT_TEST(argc, argv);
    RUN_ALL_TEST();
}



