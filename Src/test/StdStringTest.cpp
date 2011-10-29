/*
 * File       : StdStringTest.cpp
 * Description: 
 * Version    : 2011-9-28 Created
 * Author     : buf1024@gmail.com
 */

#ifndef STDSTRINGTEST_CPP_
#define STDSTRINGTEST_CPP_

#include "TestCmmHdr.h"
#include "StdString.h"

USE_XBASIC_NAMESPACE

TEST(StdStringTest, StringLength)
{
    const char* pVal = NullPtr;
    ASSERT_EQ(-1, StdString::StringLenth(pVal));

    pVal = "123456789";
    ASSERT_EQ(9, StdString::StringLenth(pVal));

    pVal = "";
    ASSERT_EQ(0, StdString::StringLenth(pVal));
}

TEST(StdStringTest, EndsWith)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(StdString::EndsWith(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(StdString::EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "ABC";
    ASSERT_TRUE(StdString::EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "BC";
    ASSERT_TRUE(StdString::EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "B";
    ASSERT_FALSE(StdString::EndsWith(pStrVal, pSubVal));

    
}
TEST(StdStringTest, StartsWith)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(StdString::StartsWith(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(StdString::StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "ABC";
    ASSERT_TRUE(StdString::StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "AB";
    ASSERT_TRUE(StdString::StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "B";
    ASSERT_FALSE(StdString::StartsWith(pStrVal, pSubVal));


}


TEST(StdStringTest, Contains)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "abcd";
    pSubVal = "";
    ASSERT_TRUE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "bccA";
    ASSERT_TRUE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "Abb";
    ASSERT_TRUE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAB";
    ASSERT_TRUE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAddddddddddddddddddB";
    ASSERT_FALSE(StdString::Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "ddddddddddB";
    ASSERT_FALSE(StdString::Contains(pStrVal, pSubVal));


    pStrVal = "AbbccddbbccAB";
    ASSERT_FALSE(StdString::Contains(pStrVal, 'X'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(StdString::Contains(pStrVal, 'A'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(StdString::Contains(pStrVal, 'B'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(StdString::Contains(pStrVal, 'd'));
}

TEST(StdStringTest, FirstPosition)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_STREQ("", StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "abcd";
    pSubVal = "";
    ASSERT_STREQ("", StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "bccA";
    ASSERT_STREQ("bccAB", StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "Abb";
    ASSERT_STREQ("AbbccddbbccAB", StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAB";
    ASSERT_STREQ("cAB", StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAddddddddddddddddddB";
    ASSERT_FALSE(StdString::FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "ddddddddddB";
    ASSERT_FALSE(StdString::FirstPosition(pStrVal, pSubVal));


    pStrVal = "AbbccddbbccAB";
    ASSERT_FALSE(StdString::FirstPosition(pStrVal, 'X'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("AbbccddbbccAB", StdString::FirstPosition(pStrVal, 'A'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("B", StdString::FirstPosition(pStrVal, 'B'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("ddbbccAB", StdString::FirstPosition(pStrVal, 'd'));
}

TEST(StdStringTest, Trim)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    std::string strVal = StdString::TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = StdString::TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "an;cd?????;");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = StdString::TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = StdString::TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = StdString::TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = StdString::TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = StdString::TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = StdString::TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = StdString::Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = StdString::Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "an;cd");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = StdString::Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = StdString::Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");
    
}

TEST(StdStringTest, Split)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    std::list<std::string> rgp;
    int nRet = StdString::Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = ";abc;defg;";
    pSubVal = "";
    nRet = StdString::Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = ";abc;defg;";
    pSubVal = ";";
    nRet = StdString::Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(4, nRet);


    pStrVal = ";abc;defg;";
    pSubVal = ";abc;defg;";
    nRet = StdString::Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(2, nRet);
}

#endif /* STDSTRINGTEST_CPP_ */
