/*
 * File       : StdString.h
 * Description: �ַ���������չ
 * Version    : 2011-05-09 Created
 *              2011-09-24 1.1 �����ϵͳ֧��
 *              2011-10-20 1.2 �ĳɽ�֧��char������ĳЩwchar_t��
 *                             ��Ϊ��ʹ��ȥ��std::string��char
 *                             ��ҪװB����Ӣ�ĸĳ�����ע��
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_STDSTRING_H_
#define XBASIC_STDSTRING_H_

#include "XBasicCore.h"

#include <string>
#include <list>
#include <vector>

XBASIC_NAMEPACE_BEGIN

namespace StdString {

//�ַ�����չ����
/**
 * ��ANSI/���ַ���ת��ΪANSI/���ַ���
 * @param strValue Ҫת����ANSI/���ַ���
 * @return ��ת����ANSI/���ַ���
 */
std::string GetAnsiString(const std::string& strValue);
/**
 * @see GetAnsiString
 */
std::string GetAnsiString(const std::wstring& strValue);
/**
 * @see GetAnsiString
 */
std::wstring GetWideString(const std::string& strValue);
/**
 * @see GetAnsiString
 */
std::wstring GetWideString(const std::wstring& strValue);

/**
 * ��ȡC�����ַ���
 * @param szValue Ҫ������ַ���
 * @param pBuf �������
 * @param nBufLen ��Ϊ�������ʱ��Ϊ����Ĵ�С����������ʱ��Ϊʵ�ʵĳ���
 * @return ����ĵ�ַ
 */
const char* GetCStyleAnsiString(const std::string& strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
const char* GetCStyleAnsiString(const std::wstring& strValue, char* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
const wchar_t* GetCStyleWideString(const std::wstring& strValue, wchar_t* pBuf, int& nBufLen);
/**
 * @see GetCStyleAnsiString
 */
const wchar_t* GetCStyleWideString(const std::string& strValue, wchar_t* pBuf, int& nBufLen);

/**
 * �����ַ����ĳ���
 * @param szStrValue Ҫ������ַ���
 * @return �ַ���������������򷵻ظ���
 */
int StringLenth(const char* szStrVal);
/**
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
int Split(const char* szStrValue, const char* szStrDelim, std::vector<std::string>& rgpRet);
/**
 * @see Split
 */
int Split(const std::string& strValue, const std::string& strDelim, std::vector<std::string>& rgpRet);
/**
 * @see Split
 */
int Split(const char* szStrValue, const char* szStrDelim, std::list<std::string>& rgpRet);
/**
 * @see Split
 */
int Split(const std::string& strValue, const std::string& strDelim, std::list<std::string>& rgpRet);

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
std::string TrimLeft(const char* szStrValue, const char* szStrDelim);

/**
 * @see TrimLeft
 */
std::string TrimLeft(const std::string& strValue, const std::string& strDelim);


/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
std::string TrimRight(const char* szStrValue, const char* szStrDelim);
/**
 * @see TrimRight
 */
std::string TrimRight(const std::string& strValue, const std::string& strDelim);
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see TrimRight
 */
std::string Trim(const char* szStrValue, const char* szStrDelim);
/**
 * @see Trim
 */
std::string Trim(const std::string& strValue, const std::string& strDelim);

/**
 * ����ַ���A�Ƿ����ַ���B��ʼ
 * @param strValue �������ַ���A
 * @param strSubStr ��ʼ���ַ���B
 * @return false �ַ���A�������ַ���B��ʼ���߳���, true ���ַ��������ַ���B��ʼ
 */
bool StartsWith(const char* szStrValue, const char*szStrSubStr);
/**
 * @see StartsWith
 */
bool StartsWith(const std::string& strValue, const std::string& strSubStr);
/**
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
bool EndsWith(const char* szStrValue, const char*szStrSubStr);

/**
 * @see EndsWith
 */
bool EndsWith(const std::string& strValue, const std::string& strSubStr);

/**
 * ����A�ַ����Ƿ����B�ַ�
 * @param strValue �����Ե��ַ���
 * @param ch B�ַ�
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ�
 */
bool Contains(const char* szStrValue, const char ch);
/**
 * @see EndsWith
 */
bool Contains(const std::string& strValue, const char ch);
/**
 * @see EndsWith
 */
bool Contains(const char* szStrValue, const char* szStrSubStr);
/**
 * @see EndsWith
 */
bool Contains(const std::string& strValue, const std::string& strSubStr);
/**
 * �ҳ�A�ַ�������B�ַ�����ʼ�ĵ�ַ
 * @param szStrVal A�ַ���
 * @param szSubVal B�ַ���
 */
const char* FirstPosition(const char* szStrVal, const char* szSubVal);
/**
 * @see FirstPosition
 */
const char* FirstPosition(const char* szStrVal, const char ch);


std::string ToUpper(const char* szStr);
std::string ToUpper(const std::string& strStr);

std::string ToLower(const char* szStr);
std::string ToLower(const std::string& strStr);

bool IsDigit(const char* szStr);
bool IsDigit(const std::string& strStr);

bool IsAlpha(const char* szStr);
bool IsAlpha(const std::string& strStr);

std::string Replace(const char* szStrVal, const char* szStrOld, const char* szStrNew);
std::string Replace(const std::string& strVal, const std::string strOld, const std::string strNew);

std::string FromNumber(long lVal);
std::string FromNumber(int nVal);
std::string FromNumber(double fVal);

long ToLong(const char* szStrVal, bool& bStat);
long ToLong(const std::string& strVal, bool& bStat);

long ToInt(const char* szStrVal, bool& bStat);
long ToInt(const std::string& strVal, bool& bStat);

double ToDouble(const char* szStrVal, bool& bStat);
double ToDouble(const std::string& strVal, bool& bStat);

}

XBASIC_NAMESPACE_END

#endif /* XBASIC_STDSTRING_H_*/
