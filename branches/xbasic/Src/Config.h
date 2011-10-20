/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#ifndef CONFIG_H_
#define CONFIG_H_

#include "StdString.h"
#include <map>

XBASIC_NAMEPACE_BEGIN

class XBASICAPI Config
{
    typedef std::map<StdString, bool>::iterator BoolOptIter;
    typedef std::map<StdString, StdString>::iterator StringOptIter;
    typedef std::map<StdString, long>::iterator DoubleWordOptIter;
    typedef std::map<StdString, double>::iterator DoubleOptIter;

    friend class ConfigApp;

public:
    Config(StdString strName);
    ~Config(void);
public:
    bool GetBool(StdString strName, bool bDef = false);
    StdString GetString(StdString strName, StdString strDef = _T(""));
    long GetDoubleWorld(StdString strName, long lDef = 0L);
    double GetDouble(StdString strName, double fDef = 0.0);

    void AddBoolValue(StdString strName, bool bValue);
    void AddStringValue(StdString strName, StdString strValue);
    void AddDWORDValue(StdString strName, long dwValue);
    void AddDoubleValue(StdString strName, double fValue);

    bool RemoveBool(StdString strName);
    bool RemoveString(StdString strName);
    bool RemoveDoubleWord(StdString strName);
    bool RemoveDouble(StdString strName);

    StdString GetName() const;
    void SetName(StdString strName);

private:
    StdString _strName;
    std::map<StdString, bool> _mapBoolOpt;
    std::map<StdString, StdString> _mapStringOpt;
    std::map<StdString, long> _mapDoubleWordOpt;
    std::map<StdString, double> _mapDoubleOpt;
};

XBASIC_NAMESPACE_END

#endif /* CONFIG_H_ */
