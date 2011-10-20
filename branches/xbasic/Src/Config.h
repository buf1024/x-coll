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
    typedef std::map<std::string, bool>::iterator BoolOptIter;
    typedef std::map<std::string, std::string>::iterator StringOptIter;
    typedef std::map<std::string, long>::iterator DoubleWordOptIter;
    typedef std::map<std::string, double>::iterator DoubleOptIter;

    friend class ConfigApp;

public:
    Config(std::string strName);
    ~Config(void);
public:
    bool GetBool(std::string strName, bool bDef = false);
    std::string GetString(std::string strName, std::string strDef = "");
    long GetDoubleWorld(std::string strName, long lDef = 0L);
    double GetDouble(std::string strName, double fDef = 0.0);

    void AddBoolValue(std::string strName, bool bValue);
    void AddStringValue(std::string strName, std::string strValue);
    void AddDWORDValue(std::string strName, long dwValue);
    void AddDoubleValue(std::string strName, double fValue);

    bool RemoveBool(std::string strName);
    bool RemoveString(std::string strName);
    bool RemoveDoubleWord(std::string strName);
    bool RemoveDouble(std::string strName);

    std::string GetName() const;
    void SetName(std::string strName);

private:
    std::string _strName;
    std::map<std::string, bool> _mapBoolOpt;
    std::map<std::string, std::string> _mapStringOpt;
    std::map<std::string, long> _mapDoubleWordOpt;
    std::map<std::string, double> _mapDoubleOpt;
};

XBASIC_NAMESPACE_END

#endif /* CONFIG_H_ */
