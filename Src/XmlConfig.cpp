/*
 * File       : XmlConfig.cpp
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#include "XmlConfig.h"
#include "tinyxml.h"

USE_XBASIC_NAMESPACE


Config::Config(std::string strName)
: _strName(strName)
{
}

Config::~Config(void)
{
}

bool Config::GetBool(std::string strName, bool& bRet, bool bDef)
{
    BoolOptIter iter = _mapBoolOpt.find(strName);
    if (iter != _mapBoolOpt.end())
    {
        bRet = iter->second;
        return true;
    }
    bRet = bDef;
    return false;
}
bool Config::GetString(std::string strName, std::string& strRet, std::string strDef)
{
    StringOptIter iter = _mapStringOpt.find(strName);
    if (iter != _mapStringOpt.end())
    {
        strRet = iter->second;
        return true;
    }
    strRet = strDef;
    return false;
}
bool Config::GetDoubleWorld(std::string strName, long& lRet, long lDef)
{
    DoubleWordOptIter iter = _mapDoubleWordOpt.find(strName);
    if (iter != _mapDoubleWordOpt.end())
    {
        lRet = iter->second;
        return true;
    }
    lRet = lDef;
    return false;
}
bool Config::GetDouble(std::string strName, double& fRet, double fDef)
{
    DoubleOptIter iter = _mapDoubleOpt.find(strName);
    if (iter != _mapDoubleOpt.end())
    {
        fRet = iter->second;
        return true;
    }
    fRet = fDef;
    return false;
}

void Config::AddBoolValue(std::string strName, bool bValue)
{
    _mapBoolOpt[strName] = bValue;
}
void Config::AddStringValue(std::string strName, std::string strValue)
{
    _mapStringOpt[strName] = strValue;
}
void Config::AddDWORDValue(std::string strName, long dwValue)
{
    _mapDoubleWordOpt[strName] = dwValue;
}
void Config::AddDoubleValue(std::string strName, double fValue)
{
    _mapDoubleOpt[strName] = fValue;
}
bool Config::RemoveBool(std::string strName)
{
    bool bRet = true;
    BoolOptIter iter = _mapBoolOpt.find(strName);
    if (iter != _mapBoolOpt.end())
    {
        _mapBoolOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveString(std::string strName)
{
    bool bRet = true;
    StringOptIter iter = _mapStringOpt.find(strName);
    if (iter != _mapStringOpt.end())
    {
        _mapStringOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDoubleWord(std::string strName)
{
    bool bRet = true;
    DoubleWordOptIter iter = _mapDoubleWordOpt.find(strName);
    if (iter != _mapDoubleWordOpt.end())
    {
        _mapDoubleWordOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDouble(std::string strName)
{
    bool bRet = true;
    DoubleOptIter iter = _mapDoubleOpt.find(strName);
    if (iter != _mapDoubleOpt.end())
    {
        _mapDoubleOpt.erase(iter);
    }
    return bRet;
}

std::string Config::GetName() const
{
    return _strName;
}
void Config::SetName(std::string strName)
{
    _strName = strName;
}


XmlConfig::XmlConfig(void)
{
}

XmlConfig::~XmlConfig(void)
{
    for (ConfigAppIter iter = _mapConfigAppOpt.begin();
        iter != _mapConfigAppOpt.end(); ++iter)
    {
        delete iter->second;
    }
}

Config* XmlConfig::GetConfig(std::string strName)
{
    Config* pConfig = NULL;
    ConfigAppIter iter = _mapConfigAppOpt.find(strName);
    if (iter != _mapConfigAppOpt.end())
    {
        pConfig = iter->second;
    }
    return pConfig;
}
void XmlConfig::AddConfig(Config* pConfig)
{
    if (pConfig)
    {
        std::string strName = pConfig->GetName();
        ConfigAppIter iter = _mapConfigAppOpt.find(strName);
        if (iter != _mapConfigAppOpt.end())
        {
            if (pConfig != iter->second)
            {
                delete iter->second;
            }       
        }
        _mapConfigAppOpt[strName] = pConfig;
    }
}
bool XmlConfig::RemoveConfig(std::string strName)
{
    bool bRet = true;
    ConfigAppIter iter = _mapConfigAppOpt.find(strName);
    if (iter != _mapConfigAppOpt.end())
    {
        delete iter->second;    
        _mapConfigAppOpt.erase(iter);
    }
    return bRet;
}

bool XmlConfig::Load(std::string strFileName)
{

    TiXmlDocument doc;
    bool bOK = doc.LoadFile(strFileName);
    if (!bOK) return false;

    TiXmlDeclaration* pDecl = doc.FirstChild()->ToDeclaration();
    if (pDecl != NULL)
    {
        _strEncoding = pDecl->Encoding();
        _strStandalone = pDecl->Standalone();
        _strVer = pDecl->Version();
    }
    else
    {
        _strEncoding = "utf-8";
        _strStandalone = "yes";
        _strVer = "1.0";
    }
    

    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElemRoot = NULL;
    TiXmlElement* pElem = NULL;

    //Root, XmlConfig
    pElemRoot = hDoc.FirstChildElement().Element();
    if (!pElemRoot) return false; 
    if (pElemRoot->Value() != std::string(CONFIG_APP_TAG))
    {
        return false;
    }

    pElem = pElemRoot->FirstChildElement();

    while(pElem)
    {        
        //Config
        if (pElem->Value() != std::string(CONFIG_TAG))
        {
            continue;
        }
        const char* szConfName = pElem->Attribute(CONFIG_NAME_ATTR);
        if (!szConfName)
        {
            continue;
        }
        Config* pConfig = new Config(szConfName);
        TiXmlElement* pElemConf = pElem->FirstChildElement();
        
        while(pElemConf)
        {
            if (std::string(pElemConf->Value()) != std::string(CONFIG_VALUE_TAG)) 
            {
                continue;
            }
            const char* szName = pElemConf->Attribute(CONFIG_NAME_ATTR);
            const char* szType = pElemConf->Attribute(CONFIG_TYPE_ATTR);
            if (!szType || !szName)
            {
                continue;
            }
            std::string strName = szName;
            const char *szValue = pElemConf->GetText();
            std::string strValue = szValue == NULL ? "" : szValue;
            if (std::string(szType) == CONFIG_BOOL_OPT)
            {
                pConfig->AddBoolValue(strName, std::string(strValue) == "0" ? 0 : 1);
            }
            else if (std::string(szType) == CONFIG_STRING_OPT)
            {
                pConfig->AddStringValue(strName, strValue);
            }
            else if (std::string(szType) == CONFIG_DWORD_OPT)
            {
                pConfig->AddDWORDValue(strName, GetLongFromString(strValue));
            }
            else if (std::string(szType) == "Double")
            {
                pConfig->AddDoubleValue(strName, GetDoubleFromString(strValue));
            }
            else
            {
                continue;
            }
            pElemConf = pElemConf->NextSiblingElement();
        }
        AddConfig(pConfig);
        pElem = pElem->NextSiblingElement();
    }

    return true;
}
bool XmlConfig::Save(std::string strFileName)
{
    TiXmlDocument doc;
    TiXmlDeclaration* pDecl = new TiXmlDeclaration(
        _strVer.empty() ? "1.0" : _strVer.c_str(),
        _strEncoding.empty() ? "utf-8" : _strEncoding.c_str(),
        _strStandalone.empty() ? "yes" : _strStandalone.c_str());
    TiXmlElement* pConfApp = new TiXmlElement(CONFIG_APP_TAG);
    for (ConfigAppIter iter = _mapConfigAppOpt.begin();
        iter != _mapConfigAppOpt.end(); ++iter)
    {
        Config* pConf = iter->second;
        TiXmlElement* pConfElem = new TiXmlElement(CONFIG_TAG);
        pConfElem->SetAttribute(CONFIG_NAME_ATTR, pConf->_strName);
        //bool opt
        for(Config::BoolOptIter bIter = pConf->_mapBoolOpt.begin();
            bIter != pConf->_mapBoolOpt.end(); ++bIter)
        {
            TiXmlElement* pBool = new TiXmlElement(CONFIG_VALUE_TAG);
            pBool->SetAttribute(CONFIG_NAME_ATTR, bIter->first);
            pBool->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_BOOL_OPT);
            TiXmlText* pText = new TiXmlText(bIter->second ? "1" : "0");
            pBool->LinkEndChild(pText);
            pConfElem->LinkEndChild(pBool);
        }
        //string opt
        for(Config::StringOptIter strIter = pConf->_mapStringOpt.begin();
            strIter != pConf->_mapStringOpt.end(); ++strIter)
        {
            TiXmlElement* pString = new TiXmlElement(CONFIG_VALUE_TAG);
            pString->SetAttribute(CONFIG_NAME_ATTR, strIter->first);
            pString->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_STRING_OPT);
            TiXmlText* pText = new TiXmlText(strIter->second);
            pString->LinkEndChild(pText);
            pConfElem->LinkEndChild(pString);
        }
        //dword opt
        for(Config::DoubleWordOptIter dwIter = pConf->_mapDoubleWordOpt.begin();
            dwIter != pConf->_mapDoubleWordOpt.end(); ++dwIter)
        {
            TiXmlElement* pDW = new TiXmlElement(CONFIG_VALUE_TAG);
            pDW->SetAttribute(CONFIG_NAME_ATTR, dwIter->first);
            pDW->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_DWORD_OPT);
            TiXmlText* pText = new TiXmlText(GetStringFromLong(dwIter->second));
            pDW->LinkEndChild(pText);
            pConfElem->LinkEndChild(pDW);
        }

        //double opt
        for(Config::DoubleOptIter dwIter = pConf->_mapDoubleOpt.begin();
            dwIter != pConf->_mapDoubleOpt.end(); ++dwIter)
        {
            TiXmlElement* pDW = new TiXmlElement(CONFIG_VALUE_TAG);
            pDW->SetAttribute(CONFIG_NAME_ATTR, dwIter->first);
            pDW->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_DOUBLE_OPT);
            TiXmlText* pText = new TiXmlText(GetStringFromDouble(dwIter->second));
            pDW->LinkEndChild(pText);
            pConfElem->LinkEndChild(pDW);
        }

        pConfApp->LinkEndChild(pConfElem);
    }
    doc.LinkEndChild(pDecl);
    doc.LinkEndChild(pConfApp);
    doc.SaveFile(strFileName);
    return true;
}

void XmlConfig::SetEncoding(const std::string strEncoding)
{
    _strEncoding = strEncoding;
}

const std::string XmlConfig::GetEncoding() const
{
    return _strEncoding;
}

void XmlConfig::SetStandalone(std::string strStandalone)
{
    _strStandalone = strStandalone;
}
const std::string XmlConfig::GetStandalone() const
{
    return _strStandalone;
}

std::string XmlConfig::GetStringFromLong(long dwValue)
{
    char szBuf[32] = {0};
#ifndef _MSC_VER
    snprintf(szBuf, 32, "%ld", dwValue);
#else
    _snprintf_s(szBuf, 32, 32, "%ld", dwValue);
#endif
    return szBuf;
}
std::string XmlConfig::GetStringFromDouble(double fValue)
{
    char szBuf[32] = {0};
#ifndef _MSC_VER
    snprintf(szBuf, 32, "%lf", fValue);
#else
    _snprintf_s(szBuf, 32, 32, "%lf", fValue);
#endif
    return szBuf;
}

long XmlConfig::GetLongFromString(std::string strValue)
{
    if (strValue.empty())
    {
        return 0L;
    }
    long dwValue = 0L;
    sscanf(strValue.c_str(), "%ld", &dwValue);
    return dwValue;
}

double XmlConfig::GetDoubleFromString(std::string strValue)
{
    if (strValue.empty())
    {
        return 0L;
    }
    double fValue = 0.0;
    sscanf(strValue.c_str(), "%lf", &fValue);
    return fValue;
}

