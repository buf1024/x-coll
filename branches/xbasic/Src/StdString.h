/*
 * File       : StdString.h
 * Description: �ַ���������չ
 * Version    : 2011-05-09 Created
 *              2011-9 24 1.1 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */

#ifndef STDSTRING_H_
#define STDSTRING_H_

#include "XBasicCore.h"

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

// ֻ��WINODWS�Ŷ�����ַ���
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
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::vector<StdString>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param strValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param rgpRet �������
 * @return ������ĸ���
 */
int Split(const StdString& strValue, const StdString& strDelim, std::vector<StdString>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::list<StdString>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param strValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param rgpRet �������
 * @return ������ĸ���
 */
int Split(const StdString& strValue, const StdString& strDelim, std::list<StdString>& rgpRet);

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
StdString TrimLeft(const StdChar* szStrValue, const StdChar* szStrDelim);

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
StdString TrimLeft(const StdString& strValue, const StdString& strDelim);


/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
StdString TrimRight(const StdChar* szStrValue, const StdChar* szStrDelim);
/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
StdString TrimRight(const StdString& strValue, const StdString& strDelim);
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see TrimRight
 */
StdString Trim(const StdChar* szStrValue, const StdChar* szStrDelim);
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
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
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
bool EndsWith(const StdChar* szStrValue, const StdChar*szStrSubStr);

/**
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
bool EndsWith(const StdString& strValue, const StdString& strSubStr);


bool Contains(const StdChar* szStrValue, const StdChar ch);
bool Contains(const StdString& strValue, const StdChar ch);
/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
 */
bool Contains(const StdChar* szStrValue, const StdChar* szStrSubStr);
/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
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
