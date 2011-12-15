/*
* File       : XmlConfig.h
* Description: 
* Version    : 2011-02-11 Created
*              2011-09-29 多操作系统支持
* Author     : buf1024@gmail.com
*/
#ifndef XBASIC_XMLCONFIG_H_
#define XBASIC_XMLCONFIG_H_

#include "StdString.h"
#include <map>


#define CONFIG_APP_TAG    "XmlConfig"
#define CONFIG_TAG        "Config"
#define CONFIG_VALUE_TAG  "Value"
#define CONFIG_NAME_ATTR  "name"
#define CONFIG_TYPE_ATTR  "type"
#define CONFIG_BOOL_OPT   "BOOL"
#define CONFIG_DWORD_OPT  "DWORD"
#define CONFIG_DOUBLE_OPT "Double"
#define CONFIG_STRING_OPT "String"


XBASIC_NAMEPACE_BEGIN

class XmlConfig;

class XBASICAPI Config
{
    typedef std::map<std::string, bool>::iterator BoolOptIter;
    typedef std::map<std::string, std::string>::iterator StringOptIter;
    typedef std::map<std::string, long>::iterator DoubleWordOptIter;
    typedef std::map<std::string, double>::iterator DoubleOptIter;

    friend class XmlConfig;

public:
    Config(std::string strName);
    ~Config(void);
public:
    bool GetBool(std::string strName, bool& bRet, bool bDef = false);
    bool GetString(std::string strName, std::string& strRet, std::string strDef = "");
    bool GetDoubleWorld(std::string strName, long& lRet, long lDef = 0L);
    bool GetDouble(std::string strName, double& fRet, double fDef = 0.0);

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


class XBASICAPI XmlConfig
{
    typedef std::map<std::string, Config*>::iterator ConfigAppIter;
public:
    typedef std::map<std::string, Config*>::const_iterator Iterator;
public:
    XmlConfig(void);
    ~XmlConfig(void);
public:
    Config* GetConfig(std::string strName);
    void AddConfig(Config* pConfig);
    bool RemoveConfig(std::string strName);

    bool Load(std::string strFileName);
    bool Save(std::string strFileName);

    void SetEncoding(const std::string strEncoding);
    const std::string GetEncoding() const;

    void SetStandalone(std::string strStandalone);
    const std::string GetStandalone() const;    

public:
    Iterator begin() const
    {
        return _mapConfigAppOpt.begin();
    }
    Iterator end() const
    {
        return _mapConfigAppOpt.end();
    }

private:   
    std::map<std::string, Config*> _mapConfigAppOpt;
    std::string _strEncoding;
    std::string _strStandalone;
    std::string _strVer;
};

XBASIC_NAMESPACE_END

#endif /* XBASIC_XMLCONFIG_H_ */
