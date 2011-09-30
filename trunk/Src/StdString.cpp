/*
 * File       : StdString.cpp
 * Description: 
 * Version    : 2011-9-28 Created
 * Author     : buf1024@gmail.com
 */

#include "StdString.h"
#include <algorithm>


XBASIC_NAMEPACE_BEGIN

//extend string service

#ifdef WINDOWS

#pragma warning(disable:4996)


/**
 * Convert an ANSI string to ANSI string
 * @return the ANSI string
 */
XBASICAPI std::string GetAnsiString(const std::string strValue)
{
    return strValue;
}
/**
 * Convert a wide string to ANSI string
 * @return the ANSI string
 */
XBASICAPI std::string GetAnsiString(const std::wstring strValue)
{
    if (strValue.empty())
    {
        return "";
    }

    int nLen = (strValue.length() + 1)*sizeof(wchar_t);
    char* pszBuf = new char[nLen];
    //We don't use C Runtime convert function here
    ::WideCharToMultiByte(CP_ACP, 0L, 
        strValue.c_str(), -1, 
        pszBuf, nLen,
        NULL, NULL);
    std::string strRet = pszBuf;
    delete[] pszBuf;

    return strRet;
}
/**
 * Convert a wide string to wide string
 * @return the wide string
 */
XBASICAPI std::wstring GetWideString(const std::wstring strValue)
{
    return strValue;
}
/**
 * Convert a ANSI string to wide string
 * @return the wide string
 */
XBASICAPI std::wstring GetWideString(const std::string strValue)
{
    if (strValue.empty())
    {
        return L"";
    }

    int nLen = strValue.length() + 1;
    wchar_t* pszBuf = new wchar_t[nLen];
    //We don't use C Runtime convert function here
    ::MultiByteToWideChar(CP_ACP, 0L,
        strValue.c_str(), -1,       
        pszBuf, nLen);
    std::wstring strRet = pszBuf;
    delete[] pszBuf;

    return strRet;
}

/**
 * Convert a ANSI string to std string
 * @return the std string
 */
XBASICAPI StdString GetStdString(std::string strValue)
{
#if _UNICODE
    return GetWideString(strValue);
#else    
    return strValue;
#endif    
}
/**
 * Convert a wide string to std string
 * @return the std string
 */
XBASICAPI StdString GetStdString(const std::wstring strValue)
{
#if _UNICODE
    return strValue;
#else
    return GetAnsiString(strValue);
#endif    
}

/**
 * @see GetCStyleStdString
 */
XBASICAPI const char* GetCStyleAnsiString(const std::string strValue, char* pBuf, int& nBufLen)
{
    if (nBufLen > 0)
    {
        nBufLen = MIN((int)strValue.length(), nBufLen);
        memcpy(pBuf, strValue.c_str(), nBufLen);
        return pBuf;
    }
    return NullPtr;
}
/**
 * @see GetCStyleStdString
 */
XBASICAPI const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf, int& nBufLen)
{
    return GetCStyleAnsiString(
        GetAnsiString(strValue), pBuf, nBufLen);
}
/**
 * @see GetCStyleStdString
 */
XBASICAPI const wchar_t* GetCStyleWideString(const std::wstring strValue, wchar_t* pBuf, int& nBufLen)
{
    if (nBufLen > 0)
    {
        nBufLen = MIN((int)(strValue.length()*sizeof(wchar_t)), nBufLen);
        memcpy(pBuf, strValue.c_str(), nBufLen);
        return pBuf;
    }
    return NullPtr;
}

/**
 * @see GetCStyleStdString
 */
XBASICAPI const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf, int& nBufLen)
{
    return GetCStyleWideString(
        GetWideString(strValue), pBuf, nBufLen);
}

/**
 * @see GetCStyleStdString
 */
XBASICAPI const StdChar* GetCStyleStdString(const std::string strValue, StdChar* pBuf, int& nBufLen)
{
#if _UNICODE
    return GetCStyleWideString(strValue, pBuf, nBufLen);
#else
    return GetCStyleAnsiString(strValue, pBuf, nBufLen);
#endif
}

/**
 * Get the C style string
 * @param strValue the string
 * @param pBuf the buffer to hold the value
 * @return the C style string
 */
XBASICAPI const StdChar* GetCStyleStdString(const std::wstring strValue, StdChar* pBuf, int& nBufLen)
{
#if _UNICODE
    return GetCStyleWideString(strValue, pBuf, nBufLen);
#else
    return GetCStyleAnsiString(strValue, pBuf, nBufLen);
#endif
}

#endif

/**
 * 计算字符串的长度
 * @param szStrValue 要计算的字符串
 * @return 字符个数，如果出错则返回负数
 */
XBASICAPI int StringLenth(const StdChar* szStrVal)
{
    if (szStrVal == NullPtr)
    {
        return -1;
    }
    const StdChar* pChar = szStrVal;
    while(*pChar != _T('\0'))
    {
        pChar++;
    }

    return (int)(pChar - szStrVal);
    
}
XBASICAPI int Split(const StdChar* szStrValue, const StdChar* szStrDelim, std::vector<StdString>& rgpRet)
{
    
    std::list<StdString> lstRet;
    int nRet = Split(szStrValue, szStrDelim, lstRet);
    
    rgpRet.clear();
    
    if (nRet > 0)
    { 
        rgpRet.resize(lstRet.size());
        std::copy(rgpRet.begin(), rgpRet.end(), lstRet.begin());
    }

    return nRet;
    
}
XBASICAPI int Split(const StdString& strValue, const StdString& strDelim, std::vector<StdString>& rgpRet)
{
    return Split(strValue.c_str(), strDelim.c_str(), rgpRet);
}
/**
 * 将给出的字符串分割到组里
 * @param szStrValue 要分割的字符串
 * @param strDelim 分割符
 * @param szStrDelim 结果集合
 * @return 结果集的个数，如果出错则返回负数
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
    
    while((pStrFirst = FirstPosition(pStrValTmp, szStrDelim)))
    {
        nCount = pStrFirst - pStrValTmp;
        rgpRet.push_back(StdString(pStrValTmp, nCount));
        pStrValTmp = pStrValTmp + nCount + StringLenth(szStrDelim);
        if (*pStrValTmp == _T('\0'))
        {
            rgpRet.push_back(_T(""));
        }     
    }
    if (*pStrValTmp != _T('\0'))
    {
        rgpRet.push_back(pStrValTmp);
    }
    

    return rgpRet.size();
}
/**
 * 将给出的字符串分割到组里
 * @param strValue 要分割的字符串
 * @param strDelim 分割符
 * @param rgpRet 结果集合
 * @return 结果集的个数
 */
XBASICAPI int Split(const StdString& strValue, const StdString& strDelim, std::list<StdString>& rgpRet)
{
    return Split(strValue.c_str(), strDelim.c_str(), rgpRet);
}

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
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
 * 去掉字符串A左边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
XBASICAPI StdString TrimLeft(const StdString& strValue, const StdString& strDelim)
{
    return TrimLeft(strValue.c_str(), strDelim.c_str());
}


/**
 * 去掉字符串A右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
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
 * 去掉字符串A右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI StdString TrimRight(const StdString& strValue, const StdString& strDelim)
{
    return TrimRight(strValue.c_str(), strDelim.c_str());
}
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param szStrValue 要处理的字符串
 * @param szStrDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI StdString Trim(const StdChar* szStrValue, const StdChar* szStrDelim)
{
    StdString strLeft = TrimLeft(szStrValue, szStrDelim);
    return TrimRight(strLeft.c_str(), szStrDelim);
}
/**
 * 去掉字符串A左边和右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 去掉字符串A左边和右边包含字符串B的部分
 * @see TrimLeft
 * @see TrimRight
 */
XBASICAPI StdString Trim(const StdString& strValue, const StdString& strDelim)
{
    return Trim(strValue.c_str(), strDelim.c_str());
}

/**
 * 检查字符串A是否以字符串B开始
 * @param strValue 被检查的字符串A
 * @param strSubStr 开始的字符串B
 * @return false 字符串A不是以字符串B开始或者出借, true 查字符串是以字符串B开始
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
 * 检查字符串A是否以字符串B开始
 * @param strValue 被检查的字符串A
 * @param strSubStr 开始的字符串B
 * @return false 字符串A不是以字符串B开始或者出借, true 查字符串是以字符串B开始
 */
XBASICAPI bool StartsWith(const StdString& strValue, const StdString& strSubStr)
{
    return StartsWith(strValue.c_str(), strSubStr.c_str());
}
/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
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
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
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
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const StdChar* szStrValue, const StdChar* szStrSubStr)
{
    return FirstPosition(szStrValue, szStrSubStr) != NullPtr;
}

/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const StdString& strValue, const StdString& strSubStr)
{
    return Contains(strValue.c_str(), strSubStr.c_str());
}

XBASICAPI const StdChar* FirstPosition(const StdChar* szStrValue, const StdChar* szStrSubStr)
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
XBASICAPI const StdChar* FirstPosition(const StdChar* szStrVal, const StdChar ch)
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


StdString ToUpper(const StdChar* szStr)
{
    if (szStr == NullPtr)
    {
        return _T("");
    }
    const StdChar* pStr = szStr;
    const int nDiff = _T('z') - _T('Z');
    StdString strUpper;
    StdChar ch;
    while(*pStr != _T('\0'))
    {
        ch = *pStr;
        if (ch >= _T('a') && ch <= _T('z'))
        {
            ch -= nDiff;
        }
        strUpper += ch;    
        pStr++;
    }
    return strUpper;  
}
StdString ToUpper(const StdString& strStr)
{
    return ToUpper(strStr.c_str());
}

StdString ToLower(const StdChar* szStr)
{
    if (szStr == NullPtr)
    {
        return _T("");
    }
    const StdChar* pStr = szStr;
    const int nDiff = _T('z') - _T('Z');
    StdString strLower;
    StdChar ch;
    while(*pStr != _T('\0'))
    {
        ch = *pStr;
        if (ch >= _T('A') && ch <= _T('Z'))
        {
           ch += nDiff;
        }
        strLower += ch;
        pStr++;
    }
    return strLower;
}
StdString ToLower(const StdString& strStr)
{
    return ToLower(strStr.c_str());
}

bool IsDigit(const StdChar* szStr)
{
    if (szStr == NullPtr)
    {
        return _T("");
    }
    const StdChar* pStr = szStr;
    while(*pStr != _T('\0'))
    {
        if (*pStr < _T('0') || *pStr > _T('9'))
        {
            return false;
        }
        pStr++;
    }
    return true; 
}
bool IsDigit(const StdString& strStr)
{
    return IsDigit(strStr.c_str());
}

bool IsAlpha(const StdChar* szStr)
{
    if (szStr == NullPtr)
    {
        return _T("");
    }
    const StdChar* pStr = szStr;
    while(*pStr != _T('\0'))
    {
        if (!(*pStr >= _T('a') && *pStr <= _T('z')) ||
            !(*pStr >= _T('A') && *pStr <= _T('Z')))
        {
            return false;
        }
        pStr++;
    }
    return true; 
}
bool IsAlpha(const StdString& strStr)
{
    return IsAlpha(strStr.c_str());
}

XBASICAPI StdString Replace(const StdChar* szStrVal, const StdChar* szStrOld, const StdChar* szStrNew)
{
    if (szStrVal == NullPtr || *szStrVal == _T('\0'))
    {
        return _T("");
    }
    if (szStrOld == NullPtr || szStrNew == NullPtr)
    {
        return szStrVal;
    }
    StdString strRet;
    const StdChar* pTmpStr = szStrVal;
    int nLenOld = StringLenth(szStrOld);
    while(true)
    {
        const StdChar* pPosStr = FirstPosition(pTmpStr, szStrOld);
        if (pPosStr == NullPtr)
        {
            break;
        }
        strRet.append(StdString(pTmpStr, pPosStr - pTmpStr));
        strRet.append(szStrNew);
        pTmpStr = pPosStr + nLenOld;
        
    }
    if (*pTmpStr != _T('\0'))
    {
        strRet.append(pTmpStr);
    }
    return strRet;
    
}
XBASICAPI StdString Replace(const StdString& strVal, const StdString strOld, const StdString strNew)
{
    return Replace(strVal.c_str(), strOld.c_str(), strNew.c_str());
}

XBASICAPI StdString FromNumber(long lVal)
{
    StdChar szTmp[8] = _T("");
#if WINDOWS
#ifdef _UNICODE
    if(lVal < 0){
        _snwprintf_s(szTmp, 8, sizeof(szTmp), _T("-%ld"), -lVal);
    }else{
        _snwprintf_s(szTmp, 8, sizeof(szTmp), _T("%ld"), lVal);
    }
#else
    if(lVal < 0){
        _snprintf(szTmp, sizeof(szTmp), _T("-%ld"), -lVal);
    }else{
        _snprintf(szTmp, sizeof(szTmp), _T("%ld"), lVal);
    }
#endif
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
XBASICAPI long ToLong(const StdString& strVal, int nBase, bool& bStat)
{
    return ToLong(strVal.c_str(), nBase, bStat);
}
XBASICAPI double ToDouble(const StdChar* szStrVal, bool& bStat)
{
    return 0.0;
}
XBASICAPI double ToDouble(const StdString& strVal, bool& bStat)
{
    return ToDouble(strVal.c_str(), bStat);
}

XBASIC_NAMESPACE_END
