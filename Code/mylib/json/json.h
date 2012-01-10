#ifndef X_JSON_H_
#define X_JSON_H_

#include <string>
#include <stdexcept>

namespace json
{

#define E_SUCCESS               0
#define E_OUTOF_INDEX           100
#define E_NULL_PTR              110
#define E_DUPLICATE_KEY         120
#define E_BAD_TYPE_CAST         130
#define E_KEY_NOT_EXISTS        140
#define E_OPEN_FILE_ERROR       150
#define E_BRACE_MISSING         500
#define E_UKNOWN_SYNTAX         510
#define E_PARSE_JASON_VALUE     520
#define E_PARSE_JASON_OBJECT    530
#define E_PARSE_JASON_ARRAY     540
#define E_EMPTY_STRING          550
#define E_QUOT_MISSING          560
#define E_KEY_MISSING           570
#define E_SENMICOLON_MISSING    580
#define E_VALUE_MISSING         590
#define E_EXTRAL_COMMA          600
#define E_COLON_MISSING         610
#define E_UNKNOWN_VAULE         620
#define E_STRING_VALUE_ERROR    630
#define E_NOT_JSON_SYNTAX       640
#define E_BRACKET_MISSING       650
#define E_ENKNOW_NUMBER         660

#define DEFAULT_ARR_CAPACITY    16
#define FORMAT_SPACE            4

enum
{
    StringType  = 10,
    BoolType    = 20,   // false true null
    IntegerType = 30,
    DoubleType  = 40,
    ObjectType  = 50,
    ArrayType   = 60,
    NullType    = 70
};

const char* getErrMsg(int nErrCode);

class JsonException
    : std::exception
{
public:
    JsonException(const char* szMsg)
        : std::exception(szMsg)
    {

    }
    ~JsonException()
    {

    }
};

class JsonValue;
class JsonArray
{
public:
    JsonArray(int nCap = DEFAULT_ARR_CAPACITY);
    JsonArray(const JsonArray& sRight);
    ~JsonArray();

    JsonArray& operator = (const JsonArray& sRight);
public:
    int set(int nIndex, JsonValue& sVal);
    JsonValue* get(int nIndex) const;
    
    JsonValue& operator[](int nIndex);
    const JsonValue& operator[](int nIndex) const;
    
    int add(JsonValue& sVal);
    
    int getSize() const;
    int getCapacity() const;

private:
    void freeRes();
    void assign(const JsonArray& sRight);
        
private:
    int _nIndex;
    int _nCap;
    JsonValue* _pArray;
};

class Json;
class JsonValue
{
    typedef union _JsonVariant
    {
        bool _boolVal;
        char* _strVal;    
        long long _llVal;
        double _fVal;
        Json* _pJsonVal;
        JsonArray* _pArrVal;
    }JsonVariant;

    friend class Json;
public:
    JsonValue();
    JsonValue(bool bVal);
    JsonValue(const char* szVal);
    JsonValue(int nVal);
    JsonValue(long long llVal);
    JsonValue(float fVal);
    JsonValue(double fVal);
    JsonValue(const Json& sVal);
    JsonValue(const JsonArray& sArr);
    JsonValue(const JsonValue& sRight);    
    
    ~JsonValue();

    JsonValue& operator = (const JsonValue& sRight);

    JsonValue& operator = (bool bVal);
    JsonValue& operator = (const char* szVal);
    JsonValue& operator = (int nVal);
    JsonValue& operator = (long long llVal);
    JsonValue& operator = (float fVal);
    JsonValue& operator = (double fVal);
    JsonValue& operator = (const Json& sVal);
    JsonValue& operator = (const JsonArray& sArr);

    JsonValue& operator [] (const char* szKey);
    const JsonValue& operator [] (const char* szKey) const;

public:
    operator const char*();
    operator char*();
    operator int();
    operator long long();
    operator float();
    operator double();
    operator Json();
    operator JsonArray();

private:
    void freeRes();
    void assign(const JsonValue& sRight);
    void assign(bool bVal);
    void assign(const char* szVal);
    void assign(int nVal);
    void assign(long long llVal);
    void assign(float fVal);
    void assign(double fVal);
    void assign(const Json& sVal);
    void assign(const JsonArray& sArr);
    void assign(const JsonVariant& sRight);

private:
    JsonVariant _sVal;
    int _nType;
};

class JsonValueItem
{
    friend class Json;
public:
    JsonValueItem(const char* szKey = 0, JsonValue* pJV = 0);
    JsonValueItem(const JsonValueItem& sRight);
    ~JsonValueItem();
    JsonValueItem& operator = (const JsonValueItem& sRight);
    void freeRes();
    void assign(const JsonValueItem& sRight);
    
    int setKey(const char* szKey);
    const char* getKey() const;

private:
    char* _szKey;
    JsonValue* _pVal;
    JsonValueItem* _pNextVal;
};

class Json
{
public:
    Json();
    Json(const Json& sRight);
    ~Json();
    
    Json& operator = (const Json& sRight);
public:
    int parse(const char* pBuf);
    int load(const char* pFilePath);
    int save(const char* pFilePath);
    
    JsonValue* set(const char* szKey, JsonValue& sVal);
    JsonValue* get(const char* szKey) const;
        
    void dump(std::string& strDump) const;
    void dumpFormat(std::string& strDump, int nSpace = FORMAT_SPACE) const;

    unsigned getItemSize() const { return _nLen;}

public:
    JsonValue& operator [] (const char* szKey);
    const JsonValue& operator [] (const char* szKey) const;

private:    
    void dumpValueGroup(JsonValueItem* pGroup, std::string& strDump, int nSpace) const;
    void dumpArray(JsonArray* pArr, std::string& strDump, int nSpace) const;
    void dumpValue(JsonValue* pJV, std::string& strDump, int nSpace) const;
    
    void freeRes();
    void assign(const Json& sRight);

    inline void skipSpaces(const char*& szBuf);
    inline bool eofBuffer(const char*& szBuf);
    int parseKey(const char*& szBuf, const char*& pStart, int& nLen);
    int parseJson(Json*& pJS, const char*& szBuf);
    int parseJsonValue(JsonValue*& pJV, const char*& szBuf);
    int parseJsonArray(JsonArray*& pJArr, const char*& szBuf);
private:
    JsonValueItem* _pGrpVal;
    unsigned int _nLen;
};
}


#endif // X_JSON_H_
