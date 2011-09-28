/*
 * File       : StdString.cpp
 * Description: 
 * Version    : 2011-9-28 Created
 * Author     : buf1024@gmail.com
 */

#include "XBasicCore.h"
#include "StdString.h"


XBASIC_NAMEPACE_BEGIN

//extend string service

#ifdef WINDOWS

///**
// * Convert an ANSI string to ANSI string
// * @return the ANSI string
// */
//XBASICAPI std::string GetAnsiString(const std::string strValue)
//{
//    return strValue;
//}
///**
// * Convert a wide string to ANSI string
// * @return the ANSI string
// */
//XBASICAPI std::string GetAnsiString(const std::wstring strValue)
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
//XBASICAPI std::wstring GetWideString(const std::wstring strValue)
//{
//    return strValue;
//}
///**
// * Convert a ANSI string to wide string
// * @return the wide string
// */
//
//XBASICAPI std::wstring GetWideString(const std::string strValue)
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
//XBASICAPI StdString GetStdString(std::string strValue)
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
//XBASICAPI StdString GetStdString(const std::wstring strValue)
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
//XBASICAPI const char* GetCStyleAnsiString(const std::string strValue, char* pBuf)
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
//XBASICAPI const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf)
//{
//    return GetCStyleAnsiString(
//        GetAnsiString(strValue), pBuf);
//}
///**
// * @see GetCStyleStdString
// */
//XBASICAPI const wchar_t* GetCStyleWideString(const std::wstring strValue, wchar_t* pBuf)
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
//XBASICAPI const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf)
//{
//    return GetCStyleWideString(
//        GetWideString(strValue), pBuf);
//}
//
///**
// * @see GetCStyleStdString
// */
//XBASICAPI const StdChar* GetCStyleStdString(const std::string strValue, StdChar* pBuf)
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
//XBASICAPI const StdChar* GetCStyleStdString(const std::wstring strValue, StdChar* pBuf)
//{
//#if _UNICODE
//    return GetCStyleWideString(strValue, pBuf);
//#else
//    return GetCStyleAnsiString(strValue, pBuf);
//#endif
//}
//
#endif

/**
 * �����ַ����ĳ���
 * @param szStrValue Ҫ������ַ���
 * @return �ַ���������������򷵻ظ���
 */
XBASICAPI int StringLenth(const StdChar* szStrVal)
{
    if (szStrVal == NullPtr)
    {
        return -1;
    }
    unsigned int nCount = 0;
    const StdChar* pChar = szStrVal;
    while((*pChar++) != _T('\0'));

    return (int)(pChar - szStrVal -1);
    
}
/**
 * ���������ַ����ָ����
 * @param szStrValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param szStrDelim �������
 * @return ������ĸ�������������򷵻ظ���
 */
XBASICAPI int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::list<StdString>& rgpRet)
{
    if(szStrValue == NullPtr ||
            szStrDelim == NullPtr || *szStrDelim == _T('\0'))
        return -1;
    rgpRet.clear();

    const StdChar* pStrFirst = NullPtr;
    const StdChar* pStrValTmp = szStrValue;
    int nCount = 0;
    
    while((pStrFirst = FirtPosition(pStrValTmp, szStrDelim)))
    {
        nCount = pStrFirst - pStrValTmp;
        rgpRet.push_back(StdString(pStrValTmp, nCount));
        pStrValTmp = pStrValTmp + nCount + StringLenth(szStrDelim);
        if (*pStrValTmp == _T('\0'))
        {
            rgpRet.push_back(_T(""));
        }     
    }

    return rgpRet.size();
}
/**
 * ���������ַ����ָ����
 * @param strValue Ҫ�ָ���ַ���
 * @param strDelim �ָ��
 * @param rgpRet �������
 * @return ������ĸ���
 */
XBASICAPI int Split(const StdString& strValue, const StdString& strDelim, std::list<StdString>& rgpRet)
{
    return Split(strValue.c_str(), strDelim.c_str(), rgpRet);
}

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
XBASICAPI StdString TrimLeft(const StdChar* szStrValue, const StdChar* szStrDelim)
{
    if (szStrValue == NullPtr ||
        szStrDelim == NullPtr)
    {
        return StdString();
    }
    const StdChar* pStr = szStrValue;
    while(*pStr != _T('\0'))
    {
        if (Contains(szStrDelim, *pStr))
        {
            pStr++;
        }
        else
        {
            break;
        }
        
    }
        
    return StdString(pStr);
}

/**
 * ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A��߰����ַ���B�Ĳ���
 * @see TrimRight
 * @see Trim
 */
XBASICAPI StdString TrimLeft(const StdString& strValue, const StdString& strDelim)
{
    return TrimLeft(strValue.c_str(), strDelim.c_str());
}


/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI StdString TrimRight(const StdChar* szStrValue, const StdChar* szStrDelim)
{
    if (szStrValue == NullPtr ||
        szStrDelim == NullPtr)
    {
        return StdString();
    }
    int nLen = StringLenth(szStrValue);
    const StdChar* pStr = szStrValue + nLen;
    while(pStr != szStrValue)
    {
        pStr--;
        if (!Contains(szStrDelim, *pStr))
        {
            pStr++;
            break;
        }
        
    }
    return StdString(szStrValue, pStr - szStrValue);
}
/**
 * ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return �Ѿ�ȥ���ַ���A�ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI StdString TrimRight(const StdString& strValue, const StdString& strDelim)
{
    return TrimRight(strValue.c_str(), strDelim.c_str());
}
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param szStrValue Ҫ������ַ���
 * @param szStrDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI StdString Trim(const StdChar* szStrValue, const StdChar* szStrDelim)
{
    StdString strLeft = TrimLeft(szStrValue, szStrDelim);
    return TrimRight(strLeft.c_str(), szStrDelim);
}
/**
 * ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @param strValue Ҫ������ַ���
 * @param strDelim �������ַ���
 * @return ȥ���ַ���A��ߺ��ұ߰����ַ���B�Ĳ���
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI StdString Trim(const StdString& strValue, const StdString& strDelim)
{
    return Trim(strValue.c_str(), strDelim.c_str());
}

/**
 * ����ַ���A�Ƿ����ַ���B��ʼ
 * @param strValue �������ַ���A
 * @param strSubStr ��ʼ���ַ���B
 * @return false �ַ���A�������ַ���B��ʼ���߳���, true ���ַ��������ַ���B��ʼ
 */
XBASICAPI bool StartsWith(const StdChar* szStrValue, const StdChar*szStrSubStr)
{
    if (szStrValue == NullPtr || szStrSubStr == NullPtr)
    {
        return false;
    }

    const StdChar* pStr = szStrValue;
    const StdChar* pSub = szStrSubStr;

    while(*pSub != _T('\0') && *pStr != _T('\0'))
    {
        if (*pStr != *pSub)
        {
            break;
        }   
        pStr++;
        pSub++;
    }
    if (*pSub == _T('\0'))
    {
        return true;
    }
    return false;
    
}
/**
 * ����ַ���A�Ƿ����ַ���B��ʼ
 * @param strValue �������ַ���A
 * @param strSubStr ��ʼ���ַ���B
 * @return false �ַ���A�������ַ���B��ʼ���߳���, true ���ַ��������ַ���B��ʼ
 */
XBASICAPI bool StartsWith(const StdString& strValue, const StdString& strSubStr)
{
    return StartsWith(strValue.c_str(), strSubStr.c_str());
}
/**
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
XBASICAPI bool EndsWith(const StdChar* szStrValue, const StdChar*szStrSubStr)
{

    if (szStrValue == NullPtr || szStrSubStr == NullPtr)
    {
        return false;
    }

    int nStrLen = StringLenth(szStrValue);
    int nSubLen = StringLenth(szStrSubStr);

    if (nStrLen < nSubLen)
    {
        return false;
    }    

    const StdChar* pSub = szStrSubStr + nSubLen;
    const StdChar* pStr = szStrValue + nStrLen;

    while(pSub != szStrSubStr)
    {
        if (*(--pSub) != *(--pStr))
        {
            return false;
        }
        
    }    
    
    return true;
}


/**
 * ����A�ַ����Ƿ���B�ַ�������
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A��B�ַ�������, false �ַ���A����B�ַ�������
 */
XBASICAPI bool EndsWith(const StdString& strValue, const StdString& strSubStr)
{
    return EndsWith(strValue.c_str(), strSubStr.c_str());
}

XBASICAPI bool Contains(const StdChar* szStrValue, const StdChar ch)
{
    if (szStrValue == NullPtr)
    {
        return false;
    }    
#ifndef _UNICODE
    return strchr(szStrValue, ch)  != NullPtr;
#else
    return wcschr(szStrValue, ch) != NullPtr;
#endif
    
}
XBASICAPI bool Contains(const StdString& strValue, const StdChar ch)
{
    return Contains(strValue.c_str(), ch);
}

/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
 */
XBASICAPI bool Contains(const StdChar* szStrValue, const StdChar* szStrSubStr)
{
    return FirtPosition(szStrValue, szStrSubStr) != NullPtr;
}

/**
 * ����A�ַ����Ƿ����B�ַ���
 * @param strValue �����Ե��ַ���
 * @param strSubStr �������ַ���
 * @return true �ַ���A����B�ַ���, false �ַ���A������B�ַ���
 */
XBASICAPI bool Contains(const StdString& strValue, const StdString& strSubStr)
{
    return Contains(strValue.c_str(), strSubStr.c_str());
}

XBASICAPI const StdChar* FirtPosition(const StdChar* szStrValue, const StdChar* szStrSubStr)
{
    if(szStrValue == NullPtr ||
        szStrSubStr == NullPtr)
    {
        return false;
    }

    const StdChar* pSub = szStrValue;

    int nSub = StringLenth(szStrSubStr);
#ifndef _UNICODE
    while((pSub = strchr(pSub, *szStrSubStr)))
#else
    while(pSub = wcschr(pSub, *szStrSubStr))
#endif
    {
        const StdChar* pSubTmp = szStrSubStr;
        const StdChar* pStrTmp = pSub;
        while(*pSubTmp != _T('\0') && *pStrTmp != _T('\0'))
        {
            if (*pSubTmp != *pStrTmp)
            {
                break;
            }    
            pSubTmp++;
            pStrTmp++;
        }
        if (*pSubTmp == _T('\0'))
        {
            return pSub;
        }
        pSub++;
    }
    return NullPtr;

}
XBASICAPI const StdChar* FirtPosition(const StdChar* szStrVal, const StdChar ch)
{
    if (szStrVal == NullPtr)
    {
        return NullPtr;
    }
    const StdChar* pRet = NullPtr;

#ifndef _UNICODE
    pRet = strchr(szStrVal, ch);
#else
    pRet = wcschr(szStrVal, ch);
#endif

    return pRet;
}

XBASICAPI StdString FromNumber(long lVal)
{
    StdChar szTmp[8] = _T("");
#ifdef _UNICODE
    if(lVal < 0){
        _snwprintf_s(szTmp, 8, sizeof(szTmp), _T("-%ld"), -lVal);
    }else{
        _snwprintf_s(szTmp, 8, sizeof(szTmp), _T("%ld"), lVal);
    }
#else
    if(lVal < 0){
        snprintf(szTmp, sizeof(szTmp), _T("-%ld"), -lVal);
    }else{
        snprintf(szTmp, sizeof(szTmp), _T("%ld"), lVal);
    }
#endif
    return szTmp;
}

XBASICAPI StdString FromNumber(int nVal)
{
    return FromNumber((long)nVal);
}

XBASICAPI StdString FromNumber(double fVal)
{
    return StdString(_T(""));
}
XBASICAPI long ToLong(const StdChar* szStrVal, int nBase, bool& bStat)
{
    return 0L;
}
XBASICAPI long ToLong(StdString& strVal, int nBase, bool& bStat)
{
    return ToLong(strVal.c_str(), nBase, bStat);
}
XBASICAPI double ToDouble(const StdChar* szStrVal, bool& bStat)
{
    return 0.0;
}
XBASICAPI double ToDouble(StdString& strVal, bool& bStat)
{
    return ToDouble(strVal.c_str(), bStat);
}

XBASIC_NAMESPACE_END
