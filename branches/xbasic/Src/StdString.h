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

#ifndef STDSTRING_H_
#define STDSTRING_H_

#include "XBasicCore.h"
#include <string>
#include <list>
#include <vector>

XBASIC_NAMEPACE_BEGIN

namespace StdString {

//�ַ�����չ����
/**
 * ��ANSI�ַ���ת��ΪANSI�ַ���
 * @return ת����ANSI�ַ���
 */
XBASICAPI std::string GetAnsiString(const std::string strValue);
/**
 * �����ַ���ת��ΪANSI�ַ���
 * @return ת����ANSI�ַ���
 */
XBASICAPI std::string GetAnsiString(const std::wstring strValue);
/**
 * �����ַ���ת��Ϊ���ַ���
 * @return ת���Ŀ��ַ���
 */
XBASICAPI std::wstring GetWideString(const std::wstring strValue);
/**
 * ��ANSI�ַ���ת��Ϊ���ַ���
 * @return ת���Ŀ��ַ���
 */
XBASICAPI std::wstring GetWideString(const std::string strValue);

/**
 * @param szValue Ҫ������ַ���
 * @param pBuf �������
 * @param nBufLen ��Ϊ�������ʱ��Ϊ����Ĵ�С����������ʱ��Ϊʵ�ʵĳ���
 * @return ����ĵ�ַ
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
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::vector<std::string>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param strValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param rgpRet �������
 * @return ������ĸ���
 */
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::vector<std::string>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::list<std::string>& rgpRet);
/**
 * ���������ַ����ָ����
 * @param strValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param rgpRet �������
 * @return ������ĸ���
 */
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::list<std::string>& rgpRet);

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
XBASICAPI std::string TrimLeft(const char* szStrValue, const char* szStrDelim);

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
XBASICAPI std::string TrimLeft(const std::string& strValue, const std::string& strDelim);


/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI std::string TrimRight(const char* szStrValue, const char* szStrDelim);
/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI std::string TrimRight(const std::string& strValue, const std::string& strDelim);
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI std::string Trim(const char* szStrValue, const char* szStrDelim);
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
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
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
XBASICAPI bool EndsWith(const char* szStrValue, const char*szStrSubStr);

/**
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
XBASICAPI bool EndsWith(const std::string& strValue, const std::string& strSubStr);


XBASICAPI bool Contains(const char* szStrValue, const char ch);
XBASICAPI bool Contains(const std::string& strValue, const char ch);
/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
 */
XBASICAPI bool Contains(const char* szStrValue, const char* szStrSubStr);
/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
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
