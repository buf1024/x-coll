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


#define CONFIG_APP_TAG    "CONFIGAPP"
#define CONFIG_TAG        "CONFIG"
#define CONFIG_VALUE_TAG  "VALUE"
#define CONFIG_NAME_ATTR  "NAME"
#define CONFIG_TYPE_ATTR  "TYPE"
#define CONFIG_BOOL_OPT   "BOOL"
#define CONFIG_DWORD_OPT  "DWORD"
#define CONFIG_DOUBLE_OPT "DOUBLE"
#define CONFIG_STRING_OPT "STRING"


XBASIC_NAMEPACE_BEGIN

class Config;
class XBASICAPI ConfigApp
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
    std::string GetStringFromDouble(double fValue);
    long GetLongFromString(std::string strValue);
    double GetDoubleFromString(std::string strValue);
private:
    std::map<StdString, Config*> _mapConfigAppOpt;
};

XBASIC_NAMESPACE_END

#endif /* CONFIGAPP_H_ */
