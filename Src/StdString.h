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
