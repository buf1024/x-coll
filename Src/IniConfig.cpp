/*
 * File       : IniConfig.cpp
 * Description: Ini配置文件
 * Version    : 2010-10-16 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#include "IniConfig.h"

#include <stdio.h>

#ifdef WINDOWS
#pragma warning(disable:4996)
#endif

USE_XBASIC_NAMESPACE;

Section::Section(StdString strSectionName /* = _T("") */)
:m_strSectionName(strSectionName)
{
	m_mapKeyValue.clear();
}
Section::~Section()
{

}

void Section::SetSectionName(const StdString strSectionName)
{
	m_strSectionName = strSectionName;
}
StdString Section::GetSectionName() const
{
	return m_strSectionName;
}

void Section::Insert(const StdString strKey, StdString strValue)
{
	if (!strKey.empty())
	{
		m_mapKeyValue[strKey] = strValue;
	}
	
}
void Section::Insert(const StdString strKey, TCHAR chValue)
{
	if (!strKey.empty())
	{
		StdChar szBuf[32] = {0};
#ifdef WINDOWS
#if _UNICODE
        _snwprintf_s(szBuf, 32, 32, _T("%c"), chValue);
#else
        _snprintf(szBuf, 32, _T("%c"), chValue);
#endif
#else
        snprintf(szBuf, 32, _T("%c"), chValue);
#endif
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, int nValue)
{
	if (!strKey.empty())
	{
		StdChar szBuf[32] = {0};
#if WINDOWS
#if _UNICODE
        _snwprintf_s(szBuf, 32, 32, _T("%d"), nValue);
#else
        _snprintf(szBuf, 32, _T("%d"), nValue);
#endif
#else
        snprintf(szBuf, 32, _T("%d"), nValue);
#endif
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, long lValue)
{
	if (!strKey.empty())
	{
		StdChar szBuf[32] = {0};
#ifdef WINDOWS
#if _UNICODE
        _snwprintf_s(szBuf, 32, 32, _T("%ld"), lValue);
#else
        _snprintf(szBuf, 32, _T("%ld"), lValue);
#endif
#else
        snprintf(szBuf, 32, _T("%ld"), lValue);
#endif
		m_mapKeyValue[strKey] = szBuf;
	}

}
void Section::Insert(const StdString strKey, double dValue)
{
	if (!strKey.empty())
	{
		StdChar szBuf[32] = {0};
#if WINDOWS
#if _UNICODE
        _snwprintf_s(szBuf, 32, 32, _T("%lf"), dValue);
#else
        _snprintf(szBuf, 32, _T("%lf"), dValue);
#endif
#else
        snprintf(szBuf, 32, _T("%lf"), dValue);
#endif
		m_mapKeyValue[strKey] = szBuf;
	}
}
bool Section::GetValue(const StdString strKey, StdString& strValue, StdString strDefault)
{
	bool bRet = false;
	if (!strKey.empty())
	{
		KVIterator iter = m_mapKeyValue.find(strKey);
		if (iter != m_mapKeyValue.end())
		{
			strValue = iter->second;
			bRet = true;
		}
		else
		{
			strValue = strDefault;
		}
		
	}
	
	return bRet;
}

bool Section::GetValue(const StdString strKey, bool& bValue, bool bDefault)
{
    StdString strVal;
    if (GetValue(strKey, strVal))
    {
        strVal = ToLower(strVal);
        if (strVal == _T("1") || strVal == _T("true"))
        {
            return true;
        }
    }
    bValue = bDefault;
    return false;    
}
bool Section::GetValue(const StdString strKey, int& nValue, int nDefault)
{
    StdString strVal;
    if (GetValue(strKey, strVal))
    {
        int nRet = 0;
#if _UNICODE
        nRet = swscanf(strVal.c_str(), _T("%d"), &nValue);
#else
        nRet = sscanf(strVal.c_str(), _T("%d"), &nValue);
#endif
        if (nRet <= 0)
        {
            nValue = nDefault;
            return false;
        }
        return true;
    }
    nValue = nDefault;
    return false;   
}
bool Section::GetValue(const StdString strKey, long& lValue, long lDefault)
{
    StdString strVal;
    if (GetValue(strKey, strVal))
    {
        int nRet = 0;
#if _UNICODE
        nRet = swscanf(strVal.c_str(), _T("%ld"), &lValue);
#else
        nRet = sscanf(strVal.c_str(), _T("%ld"), &lValue);
#endif
        if (nRet <= 0)
        {
            lValue = lDefault;
            return false;
        }
        return true;
    }
    lValue = lDefault;
    return false;   
}
bool Section::GetValue(const StdString strKey, double& fValue, double fDefault)
{
    StdString strVal;
    if (GetValue(strKey, strVal))
    {
        int nRet = 0;
#if _UNICODE
        nRet = swscanf(strVal.c_str(), _T("%lf"), &fValue);
#else
        nRet = sscanf(strVal.c_str(), _T("%lf"), &fValue);
#endif
        if (nRet <= 0)
        {
            fValue = fDefault;
            return false;
        }
        return true;
    }
    fValue = fDefault;
    return false;
}

void Section::Delete(const StdString strKey)
{
	if (!strKey.empty())
	{
		KVIterator iter = m_mapKeyValue.find(strKey);
		if (iter != m_mapKeyValue.end())
		{
			m_mapKeyValue.erase(iter);
		}
	}

}
void Section::Empty()
{
	m_strSectionName = _T("");
	m_mapKeyValue.clear();
}

bool Section::Save(StdString strFilePath)
{
    FILE* pFile = NullPtr;
#ifndef _UNICODE
    pFile = fopen(strFilePath.c_str(), _T("w+"));
#else
    pFile = _wfopen(strFilePath.c_str(), _T("w+"));
#endif

    return Save(pFile);
}

bool Section::Save(FILE* pFile)
{
    if (pFile != NullPtr && !m_strSectionName.empty())
    {
        StdString strLine = _T("[");
        strLine.append(m_strSectionName);
        strLine.append(_T("]"));
        strLine.append(_T("\n"));

        std::string strBuf;
#ifdef WINDOWS
        strBuf = GetAnsiString(strLine);
#else
        strBuf = strLine;
#endif
        fwrite(strBuf.c_str(), sizeof(char), strBuf.length(), pFile);
        
        for (KVIterator iter = m_mapKeyValue.begin(); iter != m_mapKeyValue.end(); ++iter)
        {
            strLine = iter->first;
            strLine.append(_T("="));
            strLine.append(iter->second);
            strLine.append(_T("\n"));

#ifdef WINDOWS
            strBuf = GetAnsiString(strLine);
#else
            strBuf = strLine.c_str();
#endif
            fwrite(strBuf.c_str(), sizeof(char), strBuf.length(), pFile);
        }
        return true;
    }
    return false;
}

// IniConfig

IniConfig::IniConfig(StdString strFilePath)
{
    m_strFilePath = strFilePath;
    if (!m_strFilePath.empty())
    {
        Load(m_strFilePath);
    }    
}
IniConfig::~IniConfig()
{
	ClearUp();
}

void IniConfig::SetFilePath(const StdString strFilePath)
{
	m_strFilePath = strFilePath;
}
StdString IniConfig::GetFilePath() const
{
	return m_strFilePath;
}

bool IniConfig::Insert(Section* pSec)
{
    ASSERT(pSec != NullPtr);
	
    bool bRet = false;
	if (pSec)
	{
		if (GetSection(pSec->GetSectionName()) == NULL)
		{
			m_lstSections.push_back(pSec);
			bRet = true;
		}
	}
	return bRet;

}
void IniConfig::Delete(const StdString strSection)
{
    for(ICIterator iter = m_lstSections.begin();
        iter != m_lstSections.end();
        ++iter)
    {
        if ((*iter)->GetSectionName() == strSection)
        {
            delete *iter;
            m_lstSections.erase(iter);
            break;
        }
    }
	
}
Section* IniConfig::GetSection(const StdString strSecName)
{
	Section* pSec = NullPtr;
	
    for(ICIterator iter = m_lstSections.begin();
		iter != m_lstSections.end();
		++iter)
	{
		if ((*iter)->GetSectionName() == strSecName)
		{
			pSec = *iter;
			break;
		}
	}

	return pSec;
}

bool IniConfig::Load(const StdString strFilePath)
{
    ClearUp();
    if (!strFilePath.empty())
    {
        m_strFilePath = strFilePath;
    }
    if (m_strFilePath.empty())
    {
        return false;
    }
    

    FILE* pFile = NullPtr;
#ifndef _UNICODE
	pFile = fopen(strFilePath.c_str(), _T("r"));
#else
    pFile = _wfopen(strFilePath.c_str(), _T("r"));
#endif

    if (pFile == NullPtr)
    {
        return false;
    }

    StdChar szLine[MAX_LINE] = _T("");

    const StdChar* pTmp = NullPtr;

    Section* pCurSec = NullPtr;

    while(feof(pFile) != EOF)
    {
        szLine[0] = _T('\0');
#ifndef _UNICODE
        if (fgets(szLine, MAX_LINE - 1, pFile) == NullPtr)
        {
            break;
        }
#else
        if (fgetws(szLine, MAX_LINE - 1, pFile) == NullPtr)
        {
            break;
        }
#endif
        StdString strTrim = Trim(szLine, _T(" \r\n"));
        pTmp = strTrim.c_str();

        int n = StringLenth(pTmp);
        if (StringLenth(pTmp) <= 0){
            continue;
        }
        if (*pTmp == _T('#') || *pTmp == _T(';'))
        {
            continue;
        }
        // Start section
        if (*pTmp == _T('['))
        {
            const StdChar* pNameDel = ++pTmp;
            while(*pTmp != _T('\0') && *pTmp != _T(']'))
            {
                pTmp++;
            }
            if (*pTmp == _T('\0'))
            {
                fclose(pFile);
                return false;
            }
            pCurSec = new Section(StdString(pNameDel, pTmp - pNameDel));
            m_lstSections.push_back(pCurSec);
            continue;
        }
        if (pCurSec != NullPtr)
        {
            std::list<StdString> lstKV;
            int nCount = Split(pTmp, _T("="), lstKV);
            if (nCount != 2)
            {
                fclose(pFile);
                return false;
            }
            StdString strKey = lstKV.front();
            StdString strVal = lstKV.back();
            pCurSec->Insert(strKey, strVal);
            
        }
    }

    fclose(pFile);
	
    return true;
}
bool IniConfig::Save(const StdString strFilePath)
{
    StdString strFileSaved;
    if (strFilePath.empty())
    {
        strFileSaved = m_strFilePath;
    }
    else
    {
        strFileSaved = strFilePath;
    }

    FILE* pFile = NullPtr;
#ifndef _UNICODE
    pFile = fopen(strFileSaved.c_str(), _T("w+"));
#else
    pFile = _wfopen(strFileSaved.c_str(), _T("w+"));
#endif

    if (pFile == NullPtr)
    {
        return false;
    }

    for(ICIterator iter = m_lstSections.begin();
		iter != m_lstSections.end();
		++iter)
	{
		(*iter)->Save(pFile);
	}
	
    fclose(pFile);

    return true;
	 
}
void IniConfig::ClearUp()
{
	//m_strFilePath = _T("");
	for(ICIterator iter = m_lstSections.begin();
		iter != m_lstSections.end();
		++iter)
	{
		delete *iter;
	}
}