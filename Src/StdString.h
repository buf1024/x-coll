/*
 * File       : StdString.h
 * Description: 字符串功能扩展
 * Version    : 2011-05-09 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */

#ifndef STDSTRING_H_
#define STDSTRING_H_

#include "XBasicCore.h"

#include <stdlib.h>
#include <string>
#include <list>

// 只有WINODWS才定义多字符串
#ifdef WINDOWS
  #if _UNICODE
    #define StdString   std::wstring
    #define StdChar     wchar_t
    #define _T(x)       L##x
  #else
    #define StdString   std::string
    #define StdChar     char
    #define _T(x)       x
  #endif
#else
  #define StdString     std::string
  #define StdChar       char
  #define _T(x)         x
#endif



XBASIC_NAMEPACE_BEGIN

//extend string service

#ifdef WINDOWS

///**
// * Convert an ANSI string to ANSI string
// * @return the ANSI string
// */
//inline std::string GetAnsiString(const std::string strValue)
//{
//    return strValue;
//}
///**
// * Convert a wide string to ANSI string
// * @return the ANSI string
// */
//inline std::string GetAnsiString(const std::wstring strValue)
//{
//    if (strValue.empty())
//    {
//        return "";
//    }
//
//    int nLen = (strValue.length() + 1)*2;
//    //int nLen = strValue.length() + 1;
//    char* pszBuf = new char[nLen];
//    //We don't use C Runtime convert function here
//    ::WideCharToMultiByte(CP_ACP, 0L, 
//        strValue.c_str(), -1, 
//        pszBuf, nLen,
//        NULL, NULL);
//
//    //wcstombs(pszBuf, strValue.c_str(), nLen);
//
//    std::string strRet = pszBuf;
//    delete[] pszBuf;
//
//    return strRet;
//}
///**
// * Convert a wide string to wide string
// * @return the wide string
// */
//inline std::wstring GetWideString(const std::wstring strValue)
//{
//    return strValue;
//}
///**
// * Convert a ANSI string to wide string
// * @return the wide string
// */
//
//inline std::wstring GetWideString(const std::string strValue)
//{
//    if (strValue.empty())
//    {
//        return L"";
//    }
//
//    int nLen = strValue.length() + 1;
//    wchar_t* pszBuf = new wchar_t[nLen];
//    //We don't use C Runtime convert function here
//    ::MultiByteToWideChar(CP_ACP, 0L,
//        strValue.c_str(), -1,       
//        pszBuf, nLen);
//
//    //mbstowcs(pszBuf, strValue.c_str(), nLen);
//
//    std::wstring strRet = pszBuf;
//    delete[] pszBuf;
//
//    return strRet;
//}
//
///**
// * Convert a ANSI string to std string
// * @return the std string
// */
//inline StdString GetStdString(std::string strValue)
//{
//#if _UNICODE
//    return GetWideString(strValue);
//#else    
//    return strValue;
//#endif    
//}
///**
// * Convert a wide string to std string
// * @return the std string
// */
//inline StdString GetStdString(const std::wstring strValue)
//{
//#if _UNICODE
//    return strValue;
//#else
//    return GetAnsiString(strValue);
//#endif    
//}
//
///**
// * @see GetCStyleStdString
// */
//inline const char* GetCStyleAnsiString(const std::string strValue, char* pBuf)
//{
//    //std::string strVal = GetAnsiString(strValue);
//    std::string strVal = strValue;
//    int nLen = strVal.length() + 1;
//    memcpy(pBuf, strVal.c_str(), nLen);
//    return pBuf;
//}
///**
// * @see GetCStyleStdString
// */
//inline const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf)
//{
//    return GetCStyleAnsiString(
//        GetAnsiString(strValue), pBuf);
//}
///**
// * @see GetCStyleStdString
// */
//inline const wchar_t* GetCStyleWideString(const std::wstring strValue, wchar_t* pBuf)
//{
//    std::wstring strVal = strValue;
//    int nLen = (strVal.length() + 1)*sizeof(wchar_t);
//    memcpy(pBuf, strVal.c_str(), nLen);
//    return pBuf;
//}
//
///**
// * @see GetCStyleStdString
// */
//inline const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf)
//{
//    return GetCStyleWideString(
//        GetWideString(strValue), pBuf);
//}
//
///**
// * @see GetCStyleStdString
// */
//inline const StdChar* GetCStyleStdString(const std::string strValue, StdChar* pBuf)
//{
//#if _UNICODE
//    return GetCStyleWideString(strValue, pBuf);
//#else
//    return GetCStyleAnsiString(strValue, pBuf);
//#endif
//}
//
///**
// * Get the C style string
// * @param strValue the string
// * @param pBuf the buffer to hold the value
// * @return the C style string
// */
//inline const StdChar* GetCStyleStdString(const std::wstring strValue, StdChar* pBuf)
//{
//#if _UNICODE
//    return GetCStyleWideString(strValue, pBuf);
//#else
//    return GetCStyleAnsiString(strValue, pBuf);
//#endif
//}
//
#endif

int StringLenth(const StdChar* szStrVal);
/**
 * 将给出的字符串分割到组里
 * @param szStrValue 要分割的字符串
 * @param strDelim 分割符
 * @param szStrDelim 结果集合
 * @return 结果集的个数，如果出错则返回负数
 */
int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::list<StdString>& rgpRet);
/**
 * 将给出的字符串分割到组里
 * @param strValue 要分割的字符串
 * @param strDelim 分割符
 * @param rgpRet 结果集合
 * @return 结果集的个数
 */
int Split(const StdString& strValue, const StdString& strDelim, std::list<StdString>& rgpRet);

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
StdString TrimLeft(const StdChar* szStrValue, const StdChar* szStrDelim);

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
StdString TrimLeft(const StdString& strValue, const StdString& strDelim);


/**
 * 去掉字符串A右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
StdString TrimRight(const StdChar* szStrValue, const StdChar* szStrDelim);
/**
 * 去掉字符串A右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
StdString TrimRight(const StdString& strValue, const StdString& strDelim);
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
StdString Trim(const StdChar* szStrValue, const StdChar* szStrDelim);
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
StdString Trim(const StdString& strValue, const StdString& strDelim);

/**
 * Check whether a string is starts with another string
 * @param strValue the string that will be checked
 * @param strSubStr the started string
 * @return true is a string is starts with another string, false otherwise
 */
bool StartsWith(const StdChar* szStrValue, const StdChar*szStrSubStr);
/**
 * Check whether a string is starts with another string
 * @param strValue the string that will be checked
 * @param strSubStr the started string
 * @return true is a string is starts with another string, false otherwise
 */
bool StartsWith(const StdString& strValue, const StdString& strSubStr);
/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
 */
bool EndsWith(const StdChar* szStrValue, const StdChar*szStrSubStr);

/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
 */
bool EndsWith(const StdString& strValue, const StdString& strSubStr);


bool Contains(const StdChar* szStrValue, const StdChar ch);
bool Contains(const StdString& strValue, const StdChar ch);
/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
bool Contains(const StdChar* szStrValue, const StdChar* szStrSubStr);
/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
bool Contains(const StdString& strValue, const StdString& strSubStr);
const StdChar* FirtPosition(const StdChar* szStrVal, const StdChar* szSubVal);
const StdChar* FirtPosition(const StdChar* szStrVal, const StdChar ch);
StdString FromNumber(long lVal);
StdString FromNumber(int nVal);
StdString FromNumber(double fVal);

long ToLong(const StdChar* szStrVal, int nBase, bool& bStat);
long ToLong(StdString& strVal, int nBase, bool& bStat);
double ToDouble(const StdChar* szStrVal, bool& bStat);
double ToDouble(StdString& strVal, bool& bStat);

XBASIC_NAMESPACE_END

#endif /*STDSTRING_H_*/
