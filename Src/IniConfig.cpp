/*
 * File       : IniConfig.cpp
 * Description: Ini配置文件
 * Version    : 2010-10-16 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#include "IniConfig.h"

#include <stdio.h>

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
		TCHAR szBuf[32] = {0};
	//	_sntprintf_s(szBuf, 32, 32, _T("%c"), chValue);
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, int nValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
	//	_sntprintf_s(szBuf, 32, 32, _T("%d"), nValue);
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, long lValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
	//	_sntprintf_s(szBuf, 32, 32, _T("%ld"), lValue);
		m_mapKeyValue[strKey] = szBuf;
	}

}
void Section::Insert(const StdString strKey, double dValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
	//	_sntprintf_s(szBuf, 32, 32, _T("%lf"), dValue);
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

bool Section::Load(StdString strFilePath)
{
	m_mapKeyValue.clear();
	bool bRet = false;
	int nSize = 256;
	unsigned long nRet = 0;
	TCHAR* szBuf = new TCHAR[nSize];
	while(true)
	{
		if (nSize == 32767) break;
		nRet = GetPrivateProfileSection(m_strSectionName.c_str(), szBuf, nSize, strFilePath.c_str());
		if (nRet == nSize - 2)
		{
			delete[] szBuf;
			nSize = nSize + 256;
			szBuf = new TCHAR[nSize];
		}
		else
		{
			if (nRet > 0)
			{
				bRet = true;
			}
			break;
			
		}
	}
	if (bRet)
	{
		TCHAR* pTmp = szBuf;
		while(!((*pTmp == 0) && (*(pTmp - 1) == 0)))
		{
			StdString str = pTmp;
			int idx = str.find(_T('='));
			StdString strKey(str.begin(), str.begin() + idx);
			StdString strValue(str.begin() + idx +1, str.end());
			m_mapKeyValue[strKey] = strValue;
			pTmp = pTmp + str.length() + 1;
		}
        delete[] szBuf;
	}
	
	return bRet;
}

bool Section::Save(StdString strFilePath)
{
	bool bRet = false;
	if (!m_strSectionName.empty())
	{
		for (KVIterator iter = m_mapKeyValue.begin(); iter != m_mapKeyValue.end(); ++iter)
		{
			WritePrivateProfileString(m_strSectionName.c_str(), iter->first.c_str(),
				iter->second.c_str(), strFilePath.c_str());
		}
		bRet = true;
	}
	return bRet;
}

// IniConfig

IniConfig::IniConfig(StdString strFilePath)
{
	Load(strFilePath);
}
IniConfig::~IniConfig()
{
	ClearUp();
}

void IniConfig::SetFilePath(const StdString strFilePath)
{
	m_strFilePath = strFilePath;
    Load(m_strFilePath);
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
	m_strFilePath = strFilePath;

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
#ifndef _UNICODE
        fgets(szLine, MAX_LINE - 1, pFile);
#else
        fgetws(szLine, MAX_LINE - 1, pFile);
#endif
        StdString& strTrim = Trim(szLine, _T(" "));
        pTmp = strTrim.c_str();

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
	bool bRet = true;
	for(ICIterator iter = m_lstSections.begin();
		iter != m_lstSections.end();
		++iter)
	{
		if(!(*iter)->Save(strFilePath))
		{
			bRet = false;
			break;
		}
	}
	return bRet;
	 
}
void IniConfig::ClearUp()
{
	m_strFilePath = _T("");
	for(ICIterator iter = m_lstSections.begin();
		iter != m_lstSections.end();
		++iter)
	{
		delete *iter;
	}
}