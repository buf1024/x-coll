/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-02-11 Created
 *              2011-09-29 多操作系统支持
 * Author     : buf1024@gmail.com
 */
#ifndef CONFIGAPP_H_
#define CONFIGAPP_H_

#include "StdString.h"
#include <map>


#define CONFIG_APP_TAG    "ConfigApp"
#define CONFIG_TAG        "Config"
#define CONFIG_VALUE_TAG  "Value"
#define CONFIG_NAME_ATTR  "name"
#define CONFIG_TYPE_ATTR  "type"
#define CONFIG_BOOL_OPT   "BOOL"
#define CONFIG_DWORD_OPT  "DWORD"
#define CONFIG_DOUBLE_OPT "Double"
#define CONFIG_STRING_OPT "String"


XBASIC_NAMEPACE_BEGIN

class Config;
class XBASICAPI ConfigApp
{
    typedef std::map<std::string, Config*>::iterator ConfigAppIter;
public:
    ConfigApp(void);
    ~ConfigApp(void);
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

private:
    std::string GetStringFromLong(long dwValue);
    std::string GetStringFromDouble(double fValue);
    long GetLongFromString(std::string strValue);
    double GetDoubleFromString(std::string strValue);
private:
    typedef struct  MapWrapper
    {
        std::map<std::string, Config*> _mapConfigAppOpt;
    }MapWrapper;
    
    MapWrapper* _mapWrapper;

    std::string _strEncoding;
    std::string _strStandalone;
    std::string _strVer;
};

XBASIC_NAMESPACE_END

#endif /* CONFIGAPP_H_ */
