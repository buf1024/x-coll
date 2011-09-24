////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
// 
// FileName    : ConfigApp.h
// Purpose     : 
// Version     : 2011-02-11 (20:23) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>

#include <StdString.h>


class Config;
class ConfigApp
{
    typedef std::map<StdString, Config*>::iterator ConfigAppIter;
public:
    ConfigApp(void);
    ~ConfigApp(void);
public:
    Config* GetConfig(StdString strName);
    void AddConfig(Config* pConfig);
    bool RemoveConfig(StdString strName);

    bool Load(StdString strFileName);
    bool Save(StdString strFileName);

private:
    std::string GetStringFromLong(long dwValue);
    long GetLongFromString(std::string strValue);
private:
    std::map<StdString, Config*> _mapConfigAppOpt;
};

