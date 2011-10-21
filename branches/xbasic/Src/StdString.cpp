/*
 * File       : std::string.cpp
 * Description: 
 * Version    : 2011-9-28 Created
 * Author     : buf1024@gmail.com
 */

#include "StdString.h"
#include <algorithm>
#include <stdlib.h>

#ifdef WINDOWS
#pragma warning(disable:4996)
#endif

XBASIC_NAMEPACE_BEGIN




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
 * @see GetCStylestd::string
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
 * @see GetCStylestd::string
 */
XBASICAPI const char* GetCStyleAnsiString(const std::wstring strValue, char* pBuf, int& nBufLen)
{
    return GetCStyleAnsiString(
        GetAnsiString(strValue), pBuf, nBufLen);
}
/**
 * @see GetCStylestd::string
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
 * @see GetCStylestd::string
 */
XBASICAPI const wchar_t* GetCStyleWideString(const std::string strValue, wchar_t* pBuf, int& nBufLen)
{
    return GetCStyleWideString(
        GetWideString(strValue), pBuf, nBufLen);
}


/**
 * 计算字符串的长度
 * @param szStrValue 要计算的字符串
 * @return 字符个数，如果出错则返回负数
 */
XBASICAPI int StringLenth(const char* szStrVal)
{
    if (szStrVal == NullPtr)
    {
        return -1;
    }
    const char* pChar = szStrVal;
    while(*pChar != '\0')
    {
        pChar++;
    }

    return (int)(pChar - szStrVal);
    
}
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::vector<std::string>& rgpRet)
{
    
    std::list<std::string> lstRet;
    int nRet = Split(szStrValue, szStrDelim, lstRet);
    
    rgpRet.clear();
    
    if (nRet > 0)
    { 
        rgpRet.resize(lstRet.size());
        std::copy(rgpRet.begin(), rgpRet.end(), lstRet.begin());
    }

    return nRet;
    
}
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::vector<std::string>& rgpRet)
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
XBASICAPI int Split(const char* szStrValue, const char* szStrDelim, std::list<std::string>& rgpRet)
{
    if(szStrValue == NullPtr ||
            szStrDelim == NullPtr || *szStrDelim == '\0')
        return -1;
    rgpRet.clear();

    const char* pStrFirst = NullPtr;
    const char* pStrValTmp = szStrValue;
    int nCount = 0;
    
    while((pStrFirst = FirstPosition(pStrValTmp, szStrDelim)))
    {
        nCount = pStrFirst - pStrValTmp;
        rgpRet.push_back(std::string(pStrValTmp, nCount));
        pStrValTmp = pStrValTmp + nCount + StringLenth(szStrDelim);
        if (*pStrValTmp == '\0')
        {
            rgpRet.push_back("");
        }     
    }
    if (*pStrValTmp != '\0')
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
XBASICAPI int Split(const std::string& strValue, const std::string& strDelim, std::list<std::string>& rgpRet)
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
XBASICAPI std::string TrimLeft(const char* szStrValue, const char* szStrDelim)
{
    if (szStrValue == NullPtr ||
        szStrDelim == NullPtr)
    {
        return std::string();
    }
    const char* pStr = szStrValue;
    while(*pStr != '\0')
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
        
    return std::string(pStr);
}

/**
 * 去掉字符串A左边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A左边包含字符串B的部分
 * @see TrimRight
 * @see Trim
 */
XBASICAPI std::string TrimLeft(const std::string& strValue, const std::string& strDelim)
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
XBASICAPI std::string TrimRight(const char* szStrValue, const char* szStrDelim)
{
    if (szStrValue == NullPtr ||
        szStrDelim == NullPtr)
    {
        return std::string();
    }
    int nLen = StringLenth(szStrValue);
    const char* pStr = szStrValue + nLen;
    while(pStr != szStrValue)
    {
        pStr--;
        if (!Contains(szStrDelim, *pStr))
        {
            pStr++;
            break;
        }
        
    }
    return std::string(szStrValue, pStr - szStrValue);
}
/**
 * 去掉字符串A右边包含字符串B的部分
 * @param strValue 要处理的字符串
 * @param strDelim 包含的字符串
 * @return 已经去掉字符串A右边包含字符串B的部分
 * @see TrimLeft
 * @see Trim
 */
XBASICAPI std::string TrimRight(const std::string& strValue, const std::string& strDelim)
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
XBASICAPI std::string Trim(const char* szStrValue, const char* szStrDelim)
{
    std::string strLeft = TrimLeft(szStrValue, szStrDelim);
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
XBASICAPI std::string Trim(const std::string& strValue, const std::string& strDelim)
{
    return Trim(strValue.c_str(), strDelim.c_str());
}

/**
 * 检查字符串A是否以字符串B开始
 * @param strValue 被检查的字符串A
 * @param strSubStr 开始的字符串B
 * @return false 字符串A不是以字符串B开始或者出借, true 查字符串是以字符串B开始
 */
XBASICAPI bool StartsWith(const char* szStrValue, const char*szStrSubStr)
{
    if (szStrValue == NullPtr || szStrSubStr == NullPtr)
    {
        return false;
    }

    const char* pStr = szStrValue;
    const char* pSub = szStrSubStr;

    while(*pSub != '\0' && *pStr != '\0')
    {
        if (*pStr != *pSub)
        {
            break;
        }   
        pStr++;
        pSub++;
    }
    if (*pSub == '\0')
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
XBASICAPI bool StartsWith(const std::string& strValue, const std::string& strSubStr)
{
    return StartsWith(strValue.c_str(), strSubStr.c_str());
}
/**
 * 测试A字符串是否以B字符串结束
 * @param strValue 被测试的字符串
 * @param strSubStr 结束的字符串
 * @return true 字符串A以B字符串结束, false 字符串A不以B字符串结束
 */
XBASICAPI bool EndsWith(const char* szStrValue, const char*szStrSubStr)
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

    const char* pSub = szStrSubStr + nSubLen;
    const char* pStr = szStrValue + nStrLen;

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
XBASICAPI bool EndsWith(const std::string& strValue, const std::string& strSubStr)
{
    return EndsWith(strValue.c_str(), strSubStr.c_str());
}

XBASICAPI bool Contains(const char* szStrValue, const char ch)
{
    if (szStrValue == NullPtr)
    {
        return false;
    }
    return strchr(szStrValue, ch)  != NullPtr;
    
}
XBASICAPI bool Contains(const std::string& strValue, const char ch)
{
    return Contains(strValue.c_str(), ch);
}

/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const char* szStrValue, const char* szStrSubStr)
{
    return FirstPosition(szStrValue, szStrSubStr) != NullPtr;
}

/**
 * 测试A字符串是否包括B字符串
 * @param strValue 被测试的字符串
 * @param strSubStr 包含的字符串
 * @return true 字符串A包括B字符串, false 字符串A不包括B字符串
 */
XBASICAPI bool Contains(const std::string& strValue, const std::string& strSubStr)
{
    return Contains(strValue.c_str(), strSubStr.c_str());
}

XBASICAPI const char* FirstPosition(const char* szStrValue, const char* szStrSubStr)
{
    if(szStrValue == NullPtr ||
        szStrSubStr == NullPtr)
    {
        return false;
    }

    const char* pSub = szStrValue;

    //int nSub = StringLenth(szStrSubStr);
    while((pSub = strchr(pSub, *szStrSubStr)))
    {
        const char* pSubTmp = szStrSubStr;
        const char* pStrTmp = pSub;
        while(*pSubTmp != '\0' && *pStrTmp != '\0')
        {
            if (*pSubTmp != *pStrTmp)
            {
                break;
            }    
            pSubTmp++;
            pStrTmp++;
        }
        if (*pSubTmp == '\0')
        {
            return pSub;
        }
        pSub++;
    }
    return NullPtr;

}
XBASICAPI const char* FirstPosition(const char* szStrVal, const char ch)
{
    if (szStrVal == NullPtr)
    {
        return NullPtr;
    }
    return strchr(szStrVal, ch);
}


std::string ToUpper(const char* szStr)
{
    if (szStr == NullPtr)
    {
        return "";
    }
    const char* pStr = szStr;
    const int nDiff = 'z' - 'Z';
    std::string strUpper;
    char ch;
    while(*pStr != '\0')
    {
        ch = *pStr;
        if (ch >= 'a' && ch <= 'z')
        {
            ch -= nDiff;
        }
        strUpper += ch;    
        pStr++;
    }
    return strUpper;  
}
std::string ToUpper(const std::string& strStr)
{
    return ToUpper(strStr.c_str());
}

std::string ToLower(const char* szStr)
{
    if (szStr == NullPtr)
    {
        return "";
    }
    const char* pStr = szStr;
    const int nDiff = 'z' - 'Z';
    std::string strLower;
    char ch;
    while(*pStr != '\0')
    {
        ch = *pStr;
        if (ch >= 'A' && ch <= 'Z')
        {
           ch += nDiff;
        }
        strLower += ch;
        pStr++;
    }
    return strLower;
}
std::string ToLower(const std::string& strStr)
{
    return ToLower(strStr.c_str());
}

bool IsDigit(const char* szStr)
{
    if (szStr == NullPtr)
    {
        return "";
    }
    const char* pStr = szStr;
    while(*pStr != '\0')
    {
        if (*pStr < '0' || *pStr > '9')
        {
            return false;
        }
        pStr++;
    }
    return true; 
}
bool IsDigit(const std::string& strStr)
{
    return IsDigit(strStr.c_str());
}

bool IsAlpha(const char* szStr)
{
    if (szStr == NullPtr)
    {
        return "";
    }
    const char* pStr = szStr;
    while(*pStr != '\0')
    {
        if (!(*pStr >= 'a' && *pStr <= 'z') ||
            !(*pStr >= 'A' && *pStr <= 'Z'))
        {
            return false;
        }
        pStr++;
    }
    return true; 
}
bool IsAlpha(const std::string& strStr)
{
    return IsAlpha(strStr.c_str());
}

XBASICAPI std::string Replace(const char* szStrVal, const char* szStrOld, const char* szStrNew)
{
    if (szStrVal == NullPtr || *szStrVal == '\0')
    {
        return "";
    }
    if (szStrOld == NullPtr || szStrNew == NullPtr)
    {
        return szStrVal;
    }
    std::string strRet;
    const char* pTmpStr = szStrVal;
    int nLenOld = StringLenth(szStrOld);
    while(true)
    {
        const char* pPosStr = FirstPosition(pTmpStr, szStrOld);
        if (pPosStr == NullPtr)
        {
            break;
        }
        strRet.append(std::string(pTmpStr, pPosStr - pTmpStr));
        strRet.append(szStrNew);
        pTmpStr = pPosStr + nLenOld;
        
    }
    if (*pTmpStr != '\0')
    {
        strRet.append(pTmpStr);
    }
    return strRet;
    
}
XBASICAPI std::string Replace(const std::string& strVal, const std::string strOld, const std::string strNew)
{
    return Replace(strVal.c_str(), strOld.c_str(), strNew.c_str());
}

XBASICAPI std::string FromNumber(long lVal)
{
    char szTmp[8] = "";

#ifdef WINDOWS
    if(lVal < 0){
        _snprintf(szTmp, sizeof(szTmp), "-%ld", -lVal);
    }else{
        _snprintf(szTmp, sizeof(szTmp), "%ld", lVal);
    }
#else
    if(lVal < 0){
        snprintf(szTmp, sizeof(szTmp), "-%ld", -lVal);
    }else{
        snprintf(szTmp, sizeof(szTmp), "%ld", lVal);
    }
#endif
    return szTmp;
}

XBASICAPI std::string FromNumber(int nVal)
{
    return FromNumber((long)nVal);
}

XBASICAPI std::string FromNumber(double fVal)
{
    return std::string("");
}

XBASICAPI long ToLong(const char* szStrVal, int nBase, bool& bStat)
{
    return 0L;
}
XBASICAPI long ToLong(const std::string& strVal, int nBase, bool& bStat)
{
    return ToLong(strVal.c_str(), nBase, bStat);
}
XBASICAPI double ToDouble(const char* szStrVal, bool& bStat)
{
    return 0.0;
}
XBASICAPI double ToDouble(const std::string& strVal, bool& bStat)
{
    return ToDouble(strVal.c_str(), bStat);
}

XBASIC_NAMESPACE_END
