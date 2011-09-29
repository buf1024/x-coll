/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#include "Config.h"
#include "ConfigApp.h"
#include "tinyxml.h"

#ifdef WINDOWS
#pragma warning(disable:4996)
#endif

USE_XBASIC_NAMESPACE;

ConfigApp::ConfigApp(void)
{
}

ConfigApp::~ConfigApp(void)
{
    for (ConfigAppIter iter = _mapConfigAppOpt.begin();
        iter != _mapConfigAppOpt.end(); ++iter)
    {
        delete iter->second;
    }
}

Config* ConfigApp::GetConfig(StdString strName)
{
    Config* pConfig = NULL;
    ConfigAppIter iter = _mapConfigAppOpt.find(strName);
    if (iter != _mapConfigAppOpt.end())
    {
        pConfig = iter->second;
    }
    return pConfig;
}
void ConfigApp::AddConfig(Config* pConfig)
{
    if (pConfig)
    {
        StdString strName = pConfig->GetName();
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
bool ConfigApp::RemoveConfig(StdString strName)
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

bool ConfigApp::Load(StdString strFileName)
{

    TiXmlDocument doc;
    bool bOK = doc.LoadFile(GetAnsiString(strFileName));
    if (!bOK) return false;

    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElemRoot = NULL;
    TiXmlElement* pElem = NULL;

    //Root, ConfigApp
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
        Config* pConfig = new Config(GetStdString(szConfName));
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
            StdString strName(GetStdString(szName));
            const char *szValue = pElemConf->GetText();
            std::string strValue = szValue == NULL ? "" : szValue;
            if (std::string(szType) == CONFIG_BOOL_OPT)
            {
                pConfig->AddBoolValue(strName, std::string(strValue) == "0" ? 0 : 1);
            }
            else if (std::string(szType) == CONFIG_STRING_OPT)
            {
                pConfig->AddStringValue(strName, GetStdString(strValue));
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
bool ConfigApp::Save(StdString strFileName)
{
    TiXmlDocument doc;
    TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "yes");
    TiXmlElement* pConfApp = new TiXmlElement(CONFIG_APP_TAG);
    for (ConfigAppIter iter = _mapConfigAppOpt.begin();
        iter != _mapConfigAppOpt.end(); ++iter)
    {
        Config* pConf = iter->second;
        TiXmlElement* pConfElem = new TiXmlElement(CONFIG_TAG);
        pConfElem->SetAttribute(CONFIG_NAME_ATTR, GetAnsiString(pConf->_strName));
        //bool opt
        for(Config::BoolOptIter bIter = pConf->_mapBoolOpt.begin();
            bIter != pConf->_mapBoolOpt.end(); ++bIter)
        {
            TiXmlElement* pBool = new TiXmlElement(CONFIG_VALUE_TAG);
            pBool->SetAttribute(CONFIG_NAME_ATTR, GetAnsiString(bIter->first));
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
            pString->SetAttribute(CONFIG_NAME_ATTR, GetAnsiString(strIter->first));
            pString->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_STRING_OPT);
            TiXmlText* pText = new TiXmlText(GetAnsiString(strIter->second));
            pString->LinkEndChild(pText);
            pConfElem->LinkEndChild(pString);
        }
        //dword opt
        for(Config::DoubleWordOptIter dwIter = pConf->_mapDoubleWordOpt.begin();
            dwIter != pConf->_mapDoubleWordOpt.end(); ++dwIter)
        {
            TiXmlElement* pDW = new TiXmlElement(CONFIG_VALUE_TAG);
            pDW->SetAttribute(CONFIG_NAME_ATTR, GetAnsiString(dwIter->first));
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
            pDW->SetAttribute(CONFIG_NAME_ATTR, GetAnsiString(dwIter->first));
            pDW->SetAttribute(CONFIG_TYPE_ATTR, CONFIG_DOUBLE_OPT);
            TiXmlText* pText = new TiXmlText(GetStringFromDouble(dwIter->second));
            pDW->LinkEndChild(pText);
            pConfElem->LinkEndChild(pDW);
        }

        pConfApp->LinkEndChild(pConfElem);
    }
    doc.LinkEndChild(pDecl);
    doc.LinkEndChild(pConfApp);
    doc.SaveFile(GetAnsiString(strFileName));
    return true;
}

std::string ConfigApp::GetStringFromLong(long dwValue)
{
    char szBuf[32] = {0};
#ifndef WINDOWS
    snprintf(szBuf, 32, "%ld", dwValue);
#else
    _snprintf_s(szBuf, 32, 32, "%ld", dwValue);
#endif
    return szBuf;
}
std::string ConfigApp::GetStringFromDouble(double fValue)
{
    char szBuf[32] = {0};
#ifndef WINDOWS
    snprintf(szBuf, 32, "%lf", fValue);
#else
    _snprintf_s(szBuf, 32, 32, "%lf", fValue);
#endif
    return szBuf;
}

long ConfigApp::GetLongFromString(std::string strValue)
{
    if (strValue.empty())
    {
        return 0L;
    }
    long dwValue = 0L;
    sscanf_s(strValue.c_str(), "%ld", &dwValue);
    return dwValue;
}

double ConfigApp::GetDoubleFromString(std::string strValue)
{
    if (strValue.empty())
    {
        return 0L;
    }
    double fValue = 0.0;
    sscanf(strValue.c_str(), "%lf", &fValue);
    return fValue;
}

