/*
 * File       : StdString.h
 * Description: 字符串功能扩展
 * Version    : 2011-05-09 Created
 *              2011-09-24 1.1 多操作系统支持
 *              2011-10-20 1.2 改成仅支持char，保留某些wchar_t，
 *                             因为蛋痛，去掉std::string，char
 *                             不要装B，将英文改成中文注释
 * Author     : buf1024@gmail.com
 */

#ifndef STDSTRING_H_
#define STDSTRING_H_

#include "XBasicCore.h"
#include <string>
#include <list>
#include <vector>

XBASIC_NAMEPACE_BEGIN

namespace StdString {

//字符串扩展功能
/**
 * 将ANSI字符串转换为ANSI字符串
 * @return 转换的ANSI字符串
 */
XBASICAPI std::string GetAnsiString(const std::string strValue);
/**
 * 将宽字符串转换为ANSI字符串
 * @return 转换的ANSI字符串
 */
XBASICAPI std::string GetAnsiString(const std::wstring strValue);
/**
 * 将宽字符串转换为宽字符串
 * @return 转换的宽字符串
 */
XBASICAPI std::wstring GetWideString(const std::wstring strValue);
/**
 * 将ANSI字符串转换为宽字符串
 * @return 转换的宽字符串
 */
XBASICAPI std::wstring GetWideString(const std::string strValue);

/**
 * @param szValue 要计算的字符串
 * @param pBuf 结果缓存
 * @param nBufLen 作为传入参数时，为缓存的大小，传出参数时，为实际的长度
 * @return 缓存的地址
 */
XBASICAPI const char* GetCStyleAnsiString(const std::string strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
XBASICAPI const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
XBASICAPI const wchar_t* GetCStyleWideString(const std::wstring strValue, wchar_t* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
XBASICAPI const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf, int& nBufLen);



XBASICAPI int StringLenth(const char* szStrVal);
/**
 * 将给出的字符串分割到组里
 * @param szStrValue 要分割的字符串
 * @param strDelim 分割符
 * @param szStrDelim 结果集合
 * @return 结果集的个数，如果出错则返回负数
 */
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::vector<std::string>& rgpRet);
/**
 * 将给出的字符串分割到组里
 * @param strValue 要分割的字符串
 * @param strDelim 分割符
 * @param rgpRet 结果集合
 * @return 结果集的个数
 */
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::vector<std::string>& rgpRet);
/**
 * 将给出的字符串分割到组里
 * @param szStrValue 要分割的字符串
 * @param strDelim 分割符
 * @param szStrDelim 结果集合
 * @return 结果集的个数，如果出错则返回负数
 */
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::list<std::string>& rgpRet);
/**
 * 将给出的字符串分割到组里
 * @param strValue 要分割的字符串
 * @param strDelim 分割符
 * @param rgpRet 结果集合
 * @return 结果集的个数
 */
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::list<std::string>& rgpRet);

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
XBASICAPI std::string TrimLeft(const char* szStrValue, const char* szStrDelim);

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
XBASICAPI std::string TrimLeft(const std::string& strValue, const std::string& strDelim);


/**
 * 去掉字符串A右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI std::string TrimRight(const char* szStrValue, const char* szStrDelim);
/**
 * 去掉字符串A右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI std::string TrimRight(const std::string& strValue, const std::string& strDelim);
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI std::string Trim(const char* szStrValue, const char* szStrDelim);
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI std::string Trim(const std::string& strValue, const std::string& strDelim);

/**
 * Check whether a string is starts with another string
 * @param strValue the string that will be checked
 * @param strSubStr the started string
 * @return true is a string is starts with another string, false otherwise
 */
XBASICAPI bool StartsWith(const char* szStrValue, const char*szStrSubStr);
/**
 * Check whether a string is starts with another string
 * @param strValue the string that will be checked
 * @param strSubStr the started string
 * @return true is a string is starts with another string, false otherwise
 */
XBASICAPI bool StartsWith(const std::string& strValue, const std::string& strSubStr);
/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
 */
XBASICAPI bool EndsWith(const char* szStrValue, const char*szStrSubStr);

/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
 */
XBASICAPI bool EndsWith(const std::string& strValue, const std::string& strSubStr);


XBASICAPI bool Contains(const char* szStrValue, const char ch);
XBASICAPI bool Contains(const std::string& strValue, const char ch);
/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const char* szStrValue, const char* szStrSubStr);
/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const std::string& strValue, const std::string& strSubStr);
XBASICAPI const char* FirstPosition(const char* szStrVal, const char* szSubVal);
XBASICAPI const char* FirstPosition(const char* szStrVal, const char ch);

XBASICAPI std::string ToUpper(const char* szStr);
XBASICAPI std::string ToUpper(const std::string& strStr);

XBASICAPI std::string ToLower(const char* szStr);
XBASICAPI std::string ToLower(const std::string& strStr);

XBASICAPI bool IsDigit(const char* szStr);
XBASICAPI bool IsDigit(const std::string& strStr);

XBASICAPI bool IsAlpha(const char* szStr);
XBASICAPI bool IsAlpha(const std::string& strStr);

XBASICAPI std::string Replace(const char* szStrVal, const char* szStrOld, const char* szStrNew);
XBASICAPI std::string Replace(const std::string& strVal, const std::string strOld, const std::string strNew);

XBASICAPI std::string FromNumber(long lVal);
XBASICAPI std::string FromNumber(int nVal);
XBASICAPI std::string FromNumber(double fVal);


XBASICAPI long ToLong(const char* szStrVal, int nBase, bool& bStat);
XBASICAPI long ToLong(const std::string& strVal, int nBase, bool& bStat);
XBASICAPI double ToDouble(const char* szStrVal, bool& bStat);
XBASICAPI double ToDouble(const std::string& strVal, bool& bStat);

}

XBASIC_NAMESPACE_END

#endif /*STDSTRING_H_*/
