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
#include <vector>

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

/**
 * Convert an ANSI string to ANSI string
 * @return the ANSI string
 */
inline std::string GetAnsiString(const std::string strValue);
/**
 * Convert a wide string to ANSI string
 * @return the ANSI string
 */
std::string GetAnsiString(const std::wstring strValue);
/**
 * Convert a wide string to wide string
 * @return the wide string
 */
std::wstring GetWideString(const std::wstring strValue);
/**
 * Convert a ANSI string to wide string
 * @return the wide string
 */
std::wstring GetWideString(const std::string strValue);

/**
 * Convert a ANSI string to std string
 * @return the std string
 */
StdString GetStdString(std::string strValue);
/**
 * Convert a wide string to std string
 * @return the std string
 */
StdString GetStdString(const std::wstring strValue);

/**
 * @see GetCStyleStdString
 */
const char* GetCStyleAnsiString(const std::string strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleStdString
 */
const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleStdString
 */
const wchar_t* GetCStyleWideString(const std::wstring strValue, wchar_t* pBuf, int& nBufLen);

/**
 * @see GetCStyleStdString
 */
const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf, int& nBufLen);

/**
 * @see GetCStyleStdString
 */
const StdChar* GetCStyleStdString(const std::string strValue, StdChar* pBuf, int& nBufLen);

/**
 * Get the C style string
 * @param strValue the string
 * @param pBuf the buffer to hold the value
 * @return the C style string
 */
const StdChar* GetCStyleStdString(const std::wstring strValue, StdChar* pBuf, int& nBufLen);

#endif

int StringLenth(const StdChar* szStrVal);
/**
 * 将给出的字符串分割到组里
 * @param szStrValue 要分割的字符串
 * @param strDelim 分割符
 * @param szStrDelim 结果集合
 * @return 结果集的个数，如果出错则返回负数
 */
int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::vector<StdString>& rgpRet);
/**
 * 将给出的字符串分割到组里
 * @param strValue 要分割的字符串
 * @param strDelim 分割符
 * @param rgpRet 结果集合
 * @return 结果集的个数
 */
int Split(const StdString& strValue, const StdString& strDelim, std::vector<StdString>& rgpRet);
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
const StdChar* FirstPosition(const StdChar* szStrVal, const StdChar* szSubVal);
const StdChar* FirstPosition(const StdChar* szStrVal, const StdChar ch);

StdString ToUpper(const StdChar* szStr);
StdString ToUpper(const StdString& strStr);

StdString ToLower(const StdChar* szStr);
StdString ToLower(const StdString& strStr);

bool IsDigit(const StdChar* szStr);
bool IsDigit(const StdString& strStr);

bool IsAlpha(const StdChar* szStr);
bool IsAlpha(const StdString& strStr);

StdString Replace(const StdChar* szStrVal, const StdChar* szStrOld, const StdChar* szStrNew);
StdString Replace(const StdString& strVal, const StdString strOld, const StdString strNew);

StdString FromNumber(long lVal);
StdString FromNumber(int nVal);
StdString FromNumber(double fVal);


long ToLong(const StdChar* szStrVal, int nBase, bool& bStat);
long ToLong(const StdString& strVal, int nBase, bool& bStat);
double ToDouble(const StdChar* szStrVal, bool& bStat);
double ToDouble(const StdString& strVal, bool& bStat);

XBASIC_NAMESPACE_END

#endif /*STDSTRING_H_*/
