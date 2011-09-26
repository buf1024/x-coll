/*
 * File       : TestAssert.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTASSERT_H_
#define TESTASSERT_H_

#define EXPECT_EQ(a, b)   {                                                             \
    if(a != b) {                                                                        \
        printf("[W]File: %s Line:%d expect: %ld actual: %ld\n",                         \
                __FILE__, __LINE__, (long)a, (long)b);                                  \
        TestManager::GetInst()->AddFail(this);                                          \
    }                                                                                   \
}                                                                                       \

#define EXPECT_STREQ(a, b) {                                                            \
    if(strncmp(a, b, strlen(a)) != 0) {                                                 \
        printf("[W]File: %s Line:%d expect: %s actual: %s\n", __FILE__, __LINE__, a, b);\
        TestManager::GetInst()->AddFail(this);                                          \
    }                                                                                   \
}                                                                                       \

#define EXPECT_TRUE(a) {                                                                \
    if(!((int)a)){                                                                      \
        printf("[W]File: %s Line:%d expect: TRUE actual: FALSE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFail(this);                                          \
    }                                                                                   \
}                                                                                       \

#define EXPECT_FALSE(a) {                                                               \
    if((int)a){                                                                         \
        printf("[W]File: %s Line:%d expect: FALSE actual: TRUE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFail(this);                                          \
    }                                                                                   \
}                                                                                       \

#define ASSERT_EQ(a, b) {                                                               \
    if(a != b) {                                                                        \
        printf("[E]File: %s Line:%d expect: %ld actual: %ld\n",                         \
                __FILE__, __LINE__, (long)a, (long)b);                                  \
        TestManager::GetInst()->AddFail(this);                                          \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_STREQ(a, b) {                                                            \
    if(strncmp(a, b, strlen(a)) != 0) {                                                 \
        printf("[E]File: %s Line:%d expect: %s actual: %s\n", __FILE__, __LINE__, a, b);\
        TestManager::GetInst()->AddFail(this);                                          \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_TRUE(a) {                                                                \
    if(!((int)a)){                                                                      \
        printf("[E]File: %s Line:%d expect: TRUE actual: FALSE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFail(this);                                          \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \

#define ASSERT_FALSE(a) {                                                               \
    if((int)a){                                                                         \
        printf("[E]File: %s Line:%d expect: FALSE actual: TRUE\n", __FILE__, __LINE__); \
        TestManager::GetInst()->AddFail(this);                                          \
        return;                                                                         \
    }                                                                                   \
}                                                                                       \



#endif /* TESTASSERT_H_ */
