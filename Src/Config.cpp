/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#include "Config.h"

USE_XBASIC_NAMESPACE

Config::Config(std::string strName)
: _strName(strName)
{
    _mapWrapper = new MapWrapper;
}

Config::~Config(void)
{
    delete _mapWrapper;
}

bool Config::GetBool(std::string strName, bool bDef)
{
    bool bRet = bDef;
    BoolOptIter iter = _mapWrapper->_mapBoolOpt.find(strName);
    if (iter != _mapWrapper->_mapBoolOpt.end())
    {
        bRet = iter->second;
    }
    return bRet;
}
std::string Config::GetString(std::string strName, std::string strDef)
{
    std::string strRet =  strDef;
    StringOptIter iter = _mapWrapper->_mapStringOpt.find(strName);
    if (iter != _mapWrapper->_mapStringOpt.end())
    {
        strRet = iter->second;
    }
    return strRet;
}
long Config::GetDoubleWorld(std::string strName, long lDef)
{
    long dwRet =  lDef;
    DoubleWordOptIter iter = _mapWrapper->_mapDoubleWordOpt.find(strName);
    if (iter != _mapWrapper->_mapDoubleWordOpt.end())
    {
        dwRet = iter->second;
    }
    return dwRet;
}
double Config::GetDouble(std::string strName, double fDef)
{
    double fRet =  fDef;
    DoubleOptIter iter = _mapWrapper->_mapDoubleOpt.find(strName);
    if (iter != _mapWrapper->_mapDoubleOpt.end())
    {
        fRet = iter->second;
    }
    return fRet;
}

void Config::AddBoolValue(std::string strName, bool bValue)
{
    _mapWrapper->_mapBoolOpt[strName] = bValue;
}
void Config::AddStringValue(std::string strName, std::string strValue)
{
    _mapWrapper->_mapStringOpt[strName] = strValue;
}
void Config::AddDWORDValue(std::string strName, long dwValue)
{
    _mapWrapper->_mapDoubleWordOpt[strName] = dwValue;
}
void Config::AddDoubleValue(std::string strName, double fValue)
{
    _mapWrapper->_mapDoubleOpt[strName] = fValue;
}
bool Config::RemoveBool(std::string strName)
{
    bool bRet = true;
    BoolOptIter iter = _mapWrapper->_mapBoolOpt.find(strName);
    if (iter != _mapWrapper->_mapBoolOpt.end())
    {
        _mapWrapper->_mapBoolOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveString(std::string strName)
{
    bool bRet = true;
    StringOptIter iter = _mapWrapper->_mapStringOpt.find(strName);
    if (iter != _mapWrapper->_mapStringOpt.end())
    {
        _mapWrapper->_mapStringOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDoubleWord(std::string strName)
{
    bool bRet = true;
    DoubleWordOptIter iter = _mapWrapper->_mapDoubleWordOpt.find(strName);
    if (iter != _mapWrapper->_mapDoubleWordOpt.end())
    {
        _mapWrapper->_mapDoubleWordOpt.erase(iter);
    }
    return bRet;
}
bool Config::RemoveDouble(std::string strName)
{
    bool bRet = true;
    DoubleOptIter iter = _mapWrapper->_mapDoubleOpt.find(strName);
    if (iter != _mapWrapper->_mapDoubleOpt.end())
    {
        _mapWrapper->_mapDoubleOpt.erase(iter);
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
