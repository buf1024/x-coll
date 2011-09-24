////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : IniConfig.h
// Purpose     : Ini Configuration File
// Version     : 2010-10-16 0:19:12 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file IniConfig.h */
#pragma once
#include <list>
#include <map>
#include <string>
#include <fstream>

#include "StdString.h"

#include <tchar.h>

/**
* Represent a single Section of an ini configuration file
*/
class Section
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

    /**
    * Delete the specific key/value pair
    * @param strKey Key
    */
    void Delete(const StdString strKey);
    /**Empty the section*/
    void Empty();
    /**@}*/
    /**
    * Load the specific section from the file.
    * we should set the specific section first
    * @param strFilePath the file path
    * @return true if load successfully, otherwise false
    */
    bool Load(StdString strFilePath);
    /**
    * Save the section to the specific file
    * @param strFilePath the file path
    * @return true if save successfully, otherwise false
    */
    bool Save(StdString strFilePath);

private:
    StdString m_strSectionName;
    std::map< StdString, StdString > m_mapKeyValue;
};

/**Represent Ini Confutation File*/
class IniConfig
{
    typedef std::list<Section*>::iterator ICIterator;
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
    bool Load(const StdString strFilePath);
    /**
    * Save the IniConfig to the specific file
    * @param strFilePath the file path
    * @return true if save successfully, otherwise false
    */
    bool Save(const StdString strFilePath);
private:
    void ClearUp();
private:
    StdString m_strFilePath;
    std::list<Section*> m_lstSections;
};