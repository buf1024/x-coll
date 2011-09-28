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

USE_XBASIC_NAMESPACE;

TEST(StdStringTest, StringLength)
{
    const StdChar* pVal = NullPtr;
    ASSERT_EQ(-1, StringLenth(pVal));

    pVal = _T("123456789");
    ASSERT_EQ(9, StringLenth(pVal));

    pVal = _T("");
    ASSERT_EQ(0, StringLenth(pVal));
}

TEST(StdStringTest, EndsWith)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    pStrVal = _T("");
    pSubVal = _T("");
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("ABC");
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("BC");
    ASSERT_TRUE(EndsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("B");
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    
}
TEST(StdStringTest, StartsWith)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    ASSERT_FALSE(EndsWith(pStrVal, pSubVal));

    pStrVal = _T("");
    pSubVal = _T("");
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("ABC");
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("AB");
    ASSERT_TRUE(StartsWith(pStrVal, pSubVal));

    pStrVal = _T("ABC");
    pSubVal = _T("B");
    ASSERT_FALSE(StartsWith(pStrVal, pSubVal));


}


TEST(StdStringTest, Contains)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    ASSERT_FALSE(Contains(pStrVal, pSubVal));

    pStrVal = _T("");
    pSubVal = _T("");
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = _T("abcd");
    pSubVal = _T("");
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("bccA");
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("Abb");
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("cAB");
    ASSERT_TRUE(Contains(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("cAddddddddddddddddddB");
    ASSERT_FALSE(Contains(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("ddddddddddB");
    ASSERT_FALSE(Contains(pStrVal, pSubVal));


    pStrVal = _T("AbbccddbbccAB");
    ASSERT_FALSE(Contains(pStrVal, _T('X')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_TRUE(Contains(pStrVal, _T('A')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_TRUE(Contains(pStrVal, _T('B')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_TRUE(Contains(pStrVal, _T('d')));
}

TEST(StdStringTest, FirtPosition)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    ASSERT_FALSE(FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("");
    pSubVal = _T("");
    ASSERT_STREQ(_T(""), FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("abcd");
    pSubVal = _T("");
    ASSERT_STREQ(_T(""), FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("bccA");
    ASSERT_STREQ(_T("bccAB"), FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("Abb");
    ASSERT_STREQ(_T("AbbccddbbccAB"), FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("cAB");
    ASSERT_STREQ(_T("cAB"), FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("cAddddddddddddddddddB");
    ASSERT_FALSE(FirtPosition(pStrVal, pSubVal));

    pStrVal = _T("AbbccddbbccAB");
    pSubVal = _T("ddddddddddB");
    ASSERT_FALSE(FirtPosition(pStrVal, pSubVal));


    pStrVal = _T("AbbccddbbccAB");
    ASSERT_FALSE(FirtPosition(pStrVal, _T('X')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_STREQ(_T("AbbccddbbccAB"), FirtPosition(pStrVal, _T('A')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_STREQ(_T("B"), FirtPosition(pStrVal, _T('B')));

    pStrVal = _T("AbbccddbbccAB");
    ASSERT_STREQ(_T("ddbbccAB"), FirtPosition(pStrVal, _T('d')));
}

TEST(StdStringTest, Trim)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    StdString strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T(";?");
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T("an;cd?????;"));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T("");
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(";?an;cd?????;"));

    pStrVal = _T("");
    pSubVal = _T("ddd");
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T(";?");
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(";?an;cd"));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T("");
    strVal = TrimRight(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(";?an;cd?????;"));

    pStrVal = _T("");
    pSubVal = _T("ddd");
    strVal = TrimLeft(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));

    pStrVal = NullPtr;
    pSubVal = NullPtr;
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T(";?");
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T("an;cd"));

    pStrVal = _T(";?an;cd?????;");
    pSubVal = _T("");
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(";?an;cd?????;"));

    pStrVal = _T("");
    pSubVal = _T("ddd");
    strVal = Trim(pStrVal, pSubVal);
    ASSERT_TRUE(strVal == _T(""));
    
}

TEST(StdStringTest, Split)
{
    const StdChar* pStrVal = NullPtr;
    const StdChar* pSubVal = NullPtr;
    std::list<StdString> rgp;
    int nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = _T(";abc;defg;");
    pSubVal = _T("");
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(-1, nRet);

    pStrVal = _T(";abc;defg;");
    pSubVal = _T(";");
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(4, nRet);


    pStrVal = _T(";abc;defg;");
    pSubVal = _T(";abc;defg;");
    nRet = Split(pStrVal, pSubVal, rgp);
    ASSERT_EQ(2, nRet);
}

#endif /* STDSTRINGTEST_CPP_ */
