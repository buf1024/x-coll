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
    ASSERT_EQ(-1, StringLenth(pVal));

    pVal = "123456789";
    ASSERT_EQ(9, StringLenth(pVal));

    pVal = "";
    ASSERT_EQ(0, StringLenth(pVal));
}

TEST(StdStringTest, EndsWith)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "ABC";
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "BC";
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "B";
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    
}
TEST(StdStringTest, StartsWith)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "ABC";
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "AB";
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = "ABC";
    pSubVal = "B";
    ASSERT_FALSE(StartsWith(pStrVal, pSubVal));


}


TEST(StdStringTest, Contains)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(Contains(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = "abcd";
    pSubVal = "";
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "bccA";
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "Abb";
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAB";
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAddddddddddddddddddB";
    ASSERT_FALSE(Contains(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "ddddddddddB";
    ASSERT_FALSE(Contains(pStrVal, pSubVal));


    pStrVal = "AbbccddbbccAB";
    ASSERT_FALSE(Contains(pStrVal, 'X'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(Contains(pStrVal, 'A'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(Contains(pStrVal, 'B'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_TRUE(Contains(pStrVal, 'd'));
}

TEST(StdStringTest, FirstPosition)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    ASSERT_FALSE(FirstPosition(pStrVal, pSubVal));

    pStrVal = "";
    pSubVal = "";
    ASSERT_STREQ("", FirstPosition(pStrVal, pSubVal));

    pStrVal = "abcd";
    pSubVal = "";
    ASSERT_STREQ("", FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "bccA";
    ASSERT_STREQ("bccAB", FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "Abb";
    ASSERT_STREQ("AbbccddbbccAB", FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAB";
    ASSERT_STREQ("cAB", FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "cAddddddddddddddddddB";
    ASSERT_FALSE(FirstPosition(pStrVal, pSubVal));

    pStrVal = "AbbccddbbccAB";
    pSubVal = "ddddddddddB";
    ASSERT_FALSE(FirstPosition(pStrVal, pSubVal));


    pStrVal = "AbbccddbbccAB";
    ASSERT_FALSE(FirstPosition(pStrVal, 'X'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("AbbccddbbccAB", FirstPosition(pStrVal, 'A'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("B", FirstPosition(pStrVal, 'B'));

    pStrVal = "AbbccddbbccAB";
    ASSERT_STREQ("ddbbccAB", FirstPosition(pStrVal, 'd'));
}

TEST(StdStringTest, Trim)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    std::string strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "an;cd?????;");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");

    pStrVal = ";?an;cd?????;";
    pSubVal = ";?";
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "an;cd");

    pStrVal = ";?an;cd?????;";
    pSubVal = "";
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == ";?an;cd?????;");

    pStrVal = "";
    pSubVal = "ddd";
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == "");
    
}

TEST(StdStringTest, Split)
{
    const char* pStrVal = NullPtr;
    const char* pSubVal = NullPtr;
    std::list<std::string> rgp;
    int nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = ";abc;defg;";
    pSubVal = "";
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = ";abc;defg;";
    pSubVal = ";";
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(4, nRet);


    pStrVal = ";abc;defg;";
    pSubVal = ";abc;defg;";
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(2, nRet);
}

#endif /* STDSTRINGTEST_CPP_ */
