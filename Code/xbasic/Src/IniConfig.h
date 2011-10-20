/*
 * File       : IniConfig.h
 * Description: Ini配置文件
 * Version    : 2010-10-16 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */

#include "XBasicCore.h"
#include "StdString.h"

#include <list>
#include <map>

XBASIC_NAMEPACE_BEGIN

/**
* Represent a single Section of an ini configuration file
*/
class XBASICAPI Section
{
    typedef std::map< StdString, StdString >::iterator KVIterator;
public:
    /**
    * Construct a section with an specific section name
    * @param strSectionName section name, default to empty
    */
    Section(StdString strSectionName = _T(""));
    ~Section();
public:
    /**
    * Set a section name
    * @param strSectionName the section name
    */
    void SetSectionName(const StdString strSectionName);
    /**
    * Get a section name
    * @return the section name
    */
    StdString GetSectionName() const;

    /** @name Get and Set function*/
    /** @{*/
    /**
    * Insert/update a specific key with a specific value
    * @param strKey Key
    * @param strValue the string value
    */
    void Insert(const StdString strKey, StdString strValue);
    /**
    * Insert/update a specific key with a specific value
    * @param strKey Key
    * @param chValue the character value
    */
    void Insert(const StdString strKey, StdChar chValue);
    /**
    * Insert/update a specific key with a specific value
    * @param strKey Key
    * @param nValue the int value
    */
    void Insert(const StdString strKey, int nValue);
    /**
    * Insert/update a specific key with a specific value
    * @param strKey Key
    * @param lValue the long value
    */
    void Insert(const StdString strKey, long lValue);
    /**
    * Insert/update a specific key with a specific value
    * @param strKey Key
    * @param lValue the double dValue
    */
    void Insert(const StdString strKey, double dValue);
    /**
    * Get a specific key value, if the key not found, return the default one
    * @param strKey Key
    * @param strValue The return value
    * @param strDefault The default value
    * @return true if find the specific key, otherwise false
    */
    bool GetValue(const StdString strKey, StdString& strValue, StdString strDefault = _T(""));

    bool GetValue(const StdString strKey, bool& bValue, bool bDefault = false);
    bool GetValue(const StdString strKey, int& nValue, int nDefault = 0);
    bool GetValue(const StdString strKey, long& lValue, long lDefault = 0L);
    bool GetValue(const StdString strKey, double& dValue, double fDefault = 0.0f);
    /**
    * Delete the specific key/value pair
    * @param strKey Key
    */
    void Delete(const StdString strKey);
    /**Empty the section*/
    void Empty();
    /**@}*/
    /**
    * Save the section to the specific file
    * @param strFilePath the file path
    * @return true if save successfully, otherwise false
    */
    bool Save(StdString strFilePath);

    
    bool Save(FILE* pFile);

private:
    StdString m_strSectionName;
    std::map< StdString, StdString > m_mapKeyValue;
};

/**Represent Ini Confutation File*/
class XBASICAPI IniConfig
{
    typedef std::list<Section*>::iterator ICIterator;
public:
    typedef std::list<Section*>::iterator Iterator;
public:
    /**
    * Init IniConfig class with the specific file.
    * @param strFilePath the file path
    */
    IniConfig(StdString strFilePath = _T(""));
    ~IniConfig();

    /**
    * Set the file path
    * @param strFilePath the file path
    */
    void SetFilePath(const StdString strFilePath);
    /**
    * Get the file path
    * @return the file path
    */
    StdString GetFilePath() const;

    /**
    * Insert the specific section
    * @param pSec The specific section
    * @return true if successfull inserted, otherwise is the section equals false.
    */
    bool Insert(Section* pSec);
    /**
    * Delete the specific section.*
    * @param strSection the specific secion name
    */
    void Delete(const StdString strSection);
    /**
    * Get the specific section
    * @param strSecName The specific section name
    * @return The specific section name, or NULL if not found.
    */
    Section* GetSection(const StdString strSecName);


    /**
    * Load the specific IniConfig from the file.
    * @param strFilePath the file path
    * @return true if load successfully, otherwise false
    */
    bool Load(const StdString strFilePath = _T(""));
    /**
    * Save the IniConfig to the specific file
    * @param strFilePath the file path
    * @return true if save successfully, otherwise false
    */
    bool Save(const StdString strFilePath = _T(""));

    Iterator begin() const
    {
        m_lstSections.begin();
    }
    Iterator end()const
    {
        m_lstSections.end();
    }
private:
    void ClearUp();
private:
    StdString m_strFilePath;
    std::list<Section*> m_lstSections;
};

XBASIC_NAMESPACE_END
