////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
// 
// FileName    : Config.h
// Purpose     : 
// Version     : 2011-02-11 (19:54) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <StdString.h>

class Config
{
    typedef std::map<StdString, bool>::iterator BoolOptIter;
    typedef std::map<StdString, StdString>::iterator StringOptIter;
    typedef std::map<StdString, long>::iterator DoubleWordOptIter;

    friend class ConfigApp;

public:
    Config(StdString strName);
    ~Config(void);
public:
    bool GetBool(StdString strName, bool bDef = false);
    StdString GetString(StdString strName, StdString strDef = _T(""));
    long GetDoubleWorld(StdString strName, long lDef = 0L);

    void AddBoolValue(StdString strName, bool bValue);
    void AddStringValue(StdString strName, StdString strValue);
    void AddDWORDValue(StdString strName, long dwValue);

    bool RemoveBool(StdString strName);
    bool RemoveString(StdString strName);
    bool RemoveDoubleWord(StdString strName);

    StdString GetName() const;
    void SetName(StdString strName);

private:
    StdString _strName;
    std::map<StdString, bool> _mapBoolOpt;
    std::map<StdString, StdString> _mapStringOpt;
    std::map<StdString, long> _mapDoubleWordOpt;
};

