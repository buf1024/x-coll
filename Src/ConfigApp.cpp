////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
// 
// FileName    : ConfigApp.cpp
// Purpose     : 
// Version     : 2011-02-11 (20:23) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "Config.h"
#include "ConfigApp.h"

#include "tinyxml.h"

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

    pElem = pElemRoot->FirstChildElement();

    while(pElem)
    {        
        //Config
        const char* szConfName = pElem->Attribute("name");
        if (!szConfName)
        {
            continue;
        }
        Config* pConfig = new Config(GetStdString(szConfName));
        TiXmlElement* pElemConf = pElem->FirstChildElement();
        
        while(pElemConf)
        {
            if (std::string(pElemConf->Value()) != std::string("Value")) 
            {
                continue;
            }
            const char* szName = pElemConf->Attribute("name");
            const char* szType = pElemConf->Attribute("type");
            if (!szType || !szName)
            {
                continue;
            }
            StdString strName(GetStdString(szName));
            const char *szValue = pElemConf->GetText();
            std::string strValue = szValue == NULL ? "" : szValue;
            if (std::string(szType) == "BOOL")
            {
                pConfig->AddBoolValue(strName, std::string(strValue) == "0" ? 0 : 1);
            }
            else if (std::string(szType) == "String")
            {
                pConfig->AddStringValue(strName, GetStdString(strValue));
            }
            else if (std::string(szType) == "DWORD")
            {
                pConfig->AddDWORDValue(strName, GetLongFromString(strValue));
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
    TiXmlElement* pConfApp = new TiXmlElement("ConfigApp");
    for (ConfigAppIter iter = _mapConfigAppOpt.begin();
        iter != _mapConfigAppOpt.end(); ++iter)
    {
        Config* pConf = iter->second;
        TiXmlElement* pConfElem = new TiXmlElement("Config");
        pConfElem->SetAttribute("name", GetAnsiString(pConf->_strName));
        //bool opt
        for(Config::BoolOptIter bIter = pConf->_mapBoolOpt.begin();
            bIter != pConf->_mapBoolOpt.end(); ++bIter)
        {
            TiXmlElement* pBool = new TiXmlElement("Value");
            pBool->SetAttribute("name", GetAnsiString(bIter->first));
            pBool->SetAttribute("type", "BOOL");
            TiXmlText* pText = new TiXmlText(bIter->second ? "1" : "0");
            pBool->LinkEndChild(pText);
            pConfElem->LinkEndChild(pBool);
        }
        //string opt
        for(Config::StringOptIter strIter = pConf->_mapStringOpt.begin();
            strIter != pConf->_mapStringOpt.end(); ++strIter)
        {
            TiXmlElement* pString = new TiXmlElement("Value");
            pString->SetAttribute("name", GetAnsiString(strIter->first));
            pString->SetAttribute("type", "String");
            TiXmlText* pText = new TiXmlText(GetAnsiString(strIter->second));
            pString->LinkEndChild(pText);
            pConfElem->LinkEndChild(pString);
        }
        //dword opt
        for(Config::DoubleWordOptIter dwIter = pConf->_mapDoubleWordOpt.begin();
            dwIter != pConf->_mapDoubleWordOpt.end(); ++dwIter)
        {
            TiXmlElement* pDW = new TiXmlElement("Value");
            pDW->SetAttribute("name", GetAnsiString(dwIter->first));
            pDW->SetAttribute("type", "DWORD");
            TiXmlText* pText = new TiXmlText(GetStringFromLong(dwIter->second));
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
    _snprintf_s(szBuf, 32, 32, "%ld", dwValue);
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