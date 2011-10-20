/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */
#include "Config.h"

USE_XBASIC_NAMESPACE;

Config::Config(StdString strName)
: _strName(strName)
{
}

Config::~Config(void)
{
}

bool Config::GetBool(StdString strName, bool bDef)
{
    bool bRet = bDef;
    BoolOptIter iter = _mapBoolOpt.find(strName);
    if (iter != _mapBoolOpt.end())
    {
        bRet = iter->second;
    }
    return bRet;
}
StdString Config::GetString(StdString strName, StdString strDef)
{
    StdString strRet =  strDef;
    StringOptIter iter = _mapStringOpt.find(strName);
    if (iter != _mapStringOpt.end())
    {
        strRet = iter->second;
    }
    return strRet;
}
long Config::GetDoubleWorld(StdString strName, long lDef)
{
    long dwRet =  lDef;
    DoubleWordOptIter iter = _mapDoubleWordOpt.find(strName);
    if (iter != _mapDoubleWordOpt.end())
    {
        dwRet = iter->second;
    }
    return dwRet;
}
double Config::GetDouble(StdString strName, double fDef)
{
    double fRet =  fDef;
    DoubleOptIter iter = _mapDoubleOpt.find(strName);
    if (iter != _mapDoubleOpt.end())
    {
        fRet = iter->second;
    }
    return fRet;
}

void Config::AddBoolValue(StdString strName, bool bValue)
{
    _mapBoolOpt[strName] = bValue;
}
void Config::AddStringValue(StdString strName, StdString strValue)
{
    _mapStringOpt[strName] = strValue;
}
void Config::AddDWORDValue(StdString strName, long dwValue)
{
    _mapDoubleWordOpt[strName] = dwValue;
}
void Config::AddDoubleValue(StdString strName, double fValue)
{
    _mapDoubleOpt[strName] = fValue;
}
bool Config::RemoveBool(StdString strName)
{
    bool bRet = true;
    BoolOptIter iter = _mapBoolOpt.find(strName);
    if (iter != _mapBoolOpt.end())
    {
        _mapBoolOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveString(StdString strName)
{
    bool bRet = true;
    StringOptIter iter = _mapStringOpt.find(strName);
    if (iter != _mapStringOpt.end())
    {
        _mapStringOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDoubleWord(StdString strName)
{
    bool bRet = true;
    DoubleWordOptIter iter = _mapDoubleWordOpt.find(strName);
    if (iter != _mapDoubleWordOpt.end())
    {
        _mapDoubleWordOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDouble(StdString strName)
{
    bool bRet = true;
    DoubleOptIter iter = _mapDoubleOpt.find(strName);
    if (iter != _mapDoubleOpt.end())
    {
        _mapDoubleOpt.erase(iter);
    }
    return bRet;
}

StdString Config::GetName() const
{
    return _strName;
}
void Config::SetName(StdString strName)
{
    _strName = strName;
}
