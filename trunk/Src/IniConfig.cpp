////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : IniConfig.cpp
// Purpose     : 
// Version     : 2010-10-16 0:19:55 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "IniConfig.h"

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
		_sntprintf_s(szBuf, 32, 32, _T("%c"), chValue);
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, int nValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
		_sntprintf_s(szBuf, 32, 32, _T("%d"), nValue);
		m_mapKeyValue[strKey] = szBuf;
	}
}
void Section::Insert(const StdString strKey, long lValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
		_sntprintf_s(szBuf, 32, 32, _T("%ld"), lValue);
		m_mapKeyValue[strKey] = szBuf;
	}

}
void Section::Insert(const StdString strKey, double dValue)
{
	if (!strKey.empty())
	{
		TCHAR szBuf[32] = {0};
		_sntprintf_s(szBuf, 32, 32, _T("%lf"), dValue);
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
}
StdString IniConfig::GetFilePath() const
{
	return m_strFilePath;
}

bool IniConfig::Insert(Section* pSec)
{
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
	Section* pSec = GetSection(strSection);
	if (pSec)
	{
		m_lstSections.remove(pSec);
        delete pSec;
	}
	
}
Section* IniConfig::GetSection(const StdString strSecName)
{
	Section* pSec = NULL;
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
	bool bRet = false;
	ClearUp();
	SetFilePath(strFilePath);
#if _UNICODE
	std::wfstream file(strFilePath.c_str(), std::ios_base::in);
#else
    std::fstream file(strFilePath.c_str(), std::ios_base::in);
#endif

	if (file.is_open())
	{
		std::list<StdString> lstSections;
		while(!file.eof())
		{
			TCHAR szBuf[64] = {0};
			file.getline(szBuf, 64);
			StdString str = szBuf;
			if (str[0] == _T('[') && str[str.length()-1] == _T(']'))
			{
				str.erase(str.begin());
				str.erase(str.end()-1);				
				if (!str.empty())
				{
					lstSections.push_back(str);
				}
				
			}			
		}
		bool bOp = true;
		for(std::list<StdString>::iterator  iter = lstSections.begin();
			iter != lstSections.end();
			++iter)
		{
			Section* pSec = new Section(*iter);
			if (pSec->Load(strFilePath))
			{
				Insert(pSec);
			}
			else
			{
				bOp = false;
				break;
			}
			
		}
		if (!bOp)
		{
			ClearUp();
		}
		bRet = bOp;
	}

	return bRet;
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