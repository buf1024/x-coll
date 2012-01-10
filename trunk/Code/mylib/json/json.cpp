#include "json.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif

namespace json
{

#define NullPtr                 0

typedef struct _ErrMsg
{
    int nErrCode;
    const char* szErrMsg;
}ErrMsg;

static ErrMsg _gErrMsg[] = {
    { E_SUCCESS, "No error" },
    { E_OUTOF_INDEX, "Out of index" },
    { E_NULL_PTR, "Pointer is null" },
    { E_DUPLICATE_KEY, "Duplicate key" },
    { E_BAD_TYPE_CAST, "Bad type cast" },
    { E_KEY_NOT_EXISTS, "Key does not exists"},
    { E_OPEN_FILE_ERROR, "File error"},
    { E_BRACE_MISSING, "Brace missing" },
    { E_UKNOWN_SYNTAX, "Unkown json syntax" },
    { E_PARSE_JASON_VALUE, "Parse json value error"},
    { E_PARSE_JASON_OBJECT, "Parse json object error"},
    { E_PARSE_JASON_ARRAY, "Parse json array error"},
    { E_EMPTY_STRING, "Empty json string"},
    { E_QUOT_MISSING, "Quot \" missing"},
    { E_KEY_MISSING, "Key missing"},
    { E_SENMICOLON_MISSING, "Semicolon missing"},
    { E_VALUE_MISSING, "Value missing"},
    { E_EXTRAL_COMMA, "Unexpected extra comma"},
    { E_COLON_MISSING, "Colon missing"},
    { E_UNKNOWN_VAULE, "Unkown value"},
    { E_STRING_VALUE_ERROR, "String Value error"},
    { E_NOT_JSON_SYNTAX, "Unexpected json syntax"},
    { E_BRACKET_MISSING, "Bracket missing"},
    { E_ENKNOW_NUMBER, "Unknown number"}
};


const char* getErrMsg(int nErrCode)
{
    const char* szMsg = NullPtr;
    int nLow = 0;
    int nHigh = sizeof(_gErrMsg)/sizeof(_gErrMsg[0]) - 1;
    while(nLow <= nHigh)
    {
        int nMid = (nLow + nHigh) / 2;
        ErrMsg& sErr = _gErrMsg[nMid];
        if(sErr.nErrCode == nErrCode)
        {
            szMsg = sErr.szErrMsg;
            break;
        }
        
        if(sErr.nErrCode < nErrCode)
        {
            nLow = nMid + 1;
        }
        else
        {
            nHigh = nMid - 1;
        }
    }
    
    return szMsg;
}

enum NumberType
{
    Int,
    Double,
    Unkown
};

static NumberType detectNumberType(const char* szStrVal)
{
    NumberType type = Unkown;
    if (szStrVal != NullPtr && *szStrVal != '\0')
    {
        const char* pStart = szStrVal;
        bool bHashDot = false;
        while(*pStart != 0)
        {
            if (*pStart < '0' || *pStart > '9')
            {
                if (*pStart == '.')
                {
                    if (bHashDot)
                    {
                        type = Unkown;
                        break;
                    }
                    else
                    {
                        bHashDot = true;
                        type = Double;
                    }
                }
            }
            pStart++;
        }
        if (type == Unkown)
        {
            type = Int;
        }
    }
    return type;
}

static long long toInt(const char* szStrVal, bool& bStat)
{
    int nVal = 0;
    bStat = true;
    if (szStrVal == NullPtr)
    {
        bStat = false;
    }
    else
    {
        int nRet = -1;
        nRet = sscanf(szStrVal, "%ld", &nVal);
        if (nRet == -1)
        {
            bStat = false;
        }
    }
    return nVal;
}
static double toDouble(const char* szStrVal, bool& bStat)
{
    double dVal = 0.0;
    bStat = true;
    if (szStrVal == NullPtr)
    {
        bStat = false;
    }
    else
    {
        int nRet = -1;
        nRet = sscanf(szStrVal, "%f", &dVal);
        if (nRet == -1)
        {
            bStat = false;
        }
    }
    return dVal;
}

////////////////////////////////////////
// JsonArray
JsonArray::JsonArray(int nCap)
: _nIndex(0)
, _nCap(nCap)
, _pArray(NullPtr)
{
    if(nCap <= 0)
    {
        assert(false);
        _nCap = DEFAULT_ARR_CAPACITY;
    }
    _pArray = new JsonValue[_nCap];
}
JsonArray::JsonArray(const JsonArray& sRight)
{
    assign(sRight);

}
JsonArray::~JsonArray()
{
    freeRes();
}
void JsonArray::assign(const JsonArray& sRight)
{
    _nCap = sRight._nCap;
    _nIndex = sRight._nIndex;
    _pArray = new JsonValue[_nCap];
    for (int i=0; i<_nCap; i++)
    {
        _pArray[i] = sRight._pArray[i];
    }
}
void JsonArray::freeRes()
{
    if(_pArray)
    {
        delete[] _pArray;
        _pArray = NullPtr;
    }
}
JsonArray& JsonArray::operator = (const JsonArray& sRight)
{
    if (this != &sRight)
    {
        freeRes();
        assign(sRight);
    }
    return *this;
}
int JsonArray::set(int nIndex, JsonValue& sVal)
{
    if(nIndex < 0 || nIndex >= _nCap)
    {
        throw JsonException(getErrMsg(E_OUTOF_INDEX));
    }
    _pArray[nIndex] = sVal;
    
    return E_SUCCESS;
}
JsonValue* JsonArray::get(int nIndex) const
{
    if(nIndex < 0 || nIndex >= _nCap)
    {
        throw JsonException(getErrMsg(E_OUTOF_INDEX));
    }
    return &_pArray[nIndex];
}
JsonValue& JsonArray::operator[](int nIndex)
{
    JsonValue* pJV = get(nIndex);
    if (pJV)
    {
        _nIndex++;
        
    }
    return *pJV;
}
const JsonValue& JsonArray::operator[](int nIndex) const
{
    return *get(nIndex);
}
int JsonArray::add(JsonValue& sVal)
{
    if (_nIndex >= _nCap)
    {        
        JsonValue* pVal = new JsonValue[_nCap + DEFAULT_ARR_CAPACITY];
        for (int i=0; i<_nCap; i++)
        {
            pVal[i] = _pArray[i];
        }
        _nCap += DEFAULT_ARR_CAPACITY;
        freeRes();
        _pArray = pVal;
    }
    _pArray[_nIndex++] = sVal;
    return E_SUCCESS;
}
int JsonArray::getSize() const
{
    return _nIndex;
}
int JsonArray::getCapacity() const
{
    return _nCap;
}


////////////////////////////////////////
// JsonValue
JsonValue::JsonValue()
{
    _nType = 0;
    memset(&_sVal, 0, sizeof(&_sVal));
}
JsonValue::JsonValue(bool bVal)
{
    assign(bVal);
}
JsonValue::JsonValue(const char* szVal)
{
    assign(szVal);
}
JsonValue::JsonValue(int nVal)
{
    assign((long long)nVal);
}
JsonValue::JsonValue(long long llVal)
{
    assign(llVal);
}
JsonValue::JsonValue(float fVal)
{
    assign((double)fVal);
}
JsonValue::JsonValue(double fVal)
{
    assign(fVal);
}
JsonValue::JsonValue(const Json& sVal)
{
    assign(sVal);
}
JsonValue::JsonValue(const JsonArray& sArr)
{
    assign(sArr);
}
JsonValue::JsonValue(const JsonValue& sRight)
{
    assign(sRight);
}
JsonValue::~JsonValue()
{
    freeRes();
}
JsonValue& JsonValue::operator = (const JsonValue& sRight)
{
    if (this != &sRight)
    {
        freeRes();
        assign(sRight);
    }
    return *this;
}

JsonValue& JsonValue::operator = (bool bVal)
{
    freeRes();
    assign(bVal);
    return *this;
}
JsonValue& JsonValue::operator = (const char* szVal)
{
    freeRes();
    assign(szVal);
    return *this;
}
JsonValue& JsonValue::operator = (int nVal)
{
    freeRes();
    assign((long long)nVal);
    return *this;
}
JsonValue& JsonValue::operator = (long long llVal)
{
    freeRes();
    assign(llVal);
    return *this;
}
JsonValue& JsonValue::operator = (float fVal)
{
    freeRes();
    assign((double)fVal);
    return *this;
}
JsonValue& JsonValue::operator = (double fVal)
{
    freeRes();
    assign(fVal);
    return *this;
}
JsonValue& JsonValue::operator = (const Json& sVal)
{
    freeRes();
    assign(sVal);
    return *this;
}
JsonValue& JsonValue::operator = (const JsonArray& sArr)
{
    freeRes();
    assign(sArr);
    return *this;
}
JsonValue& JsonValue::operator [] (const char* szKey)
{
    if (szKey == NullPtr)
    {
        throw JsonException(getErrMsg(E_NULL_PTR));
    }
    if (_nType != ObjectType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    Json* pJS = _sVal._pJsonVal;

    JsonValue* pJV = pJS->get(szKey);
    if (pJV == NullPtr)
    {
        JsonValue jv;
        pJV = pJS->set(szKey, jv);
    }
    return *pJV;
}
const JsonValue& JsonValue::operator [] (const char* szKey) const
{
    if (szKey == NullPtr)
    {
        throw JsonException(getErrMsg(E_NULL_PTR));
    }
    if (_nType != ObjectType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    Json* pJS = _sVal._pJsonVal;

    JsonValue* pJV = pJS->get(szKey);
    if (pJV == NullPtr)
    {
        throw JsonException(getErrMsg(E_KEY_NOT_EXISTS));
    }
    return *pJV;
}
void JsonValue::freeRes()
{
    switch(_nType)
    {
    case StringType:
        if (_sVal._strVal != NullPtr)
        {
            delete[] _sVal._strVal;
            _sVal._strVal = NullPtr;
        }
        break;
    case BoolType:
    case IntegerType:
    case DoubleType:
    case NullType:
        break;
    case ObjectType:
        if (_sVal._pJsonVal != NullPtr)
        {
            delete _sVal._pJsonVal;
            _sVal._pJsonVal = NullPtr;
        }
        break;
    case ArrayType:
        if (_sVal._pArrVal != NullPtr)
        {
            delete _sVal._pArrVal;
            _sVal._pArrVal = NullPtr;
        }
        break;
    }
    memset(&_sVal, 0, sizeof(_sVal));
}

void JsonValue::assign(const JsonValue& sRight)
{
    _nType = sRight._nType;
    assign(sRight._sVal);
}
void JsonValue::assign(const JsonVariant& sRight)
{
    memset(&_sVal, 0, sizeof(_sVal));
    switch(_nType)
    {
    case StringType:
        if (sRight._strVal != NullPtr)
        {
            int nLen = strlen(sRight._strVal);
            _sVal._strVal = new char[nLen + 1];
            memcpy(_sVal._strVal, sRight._strVal, nLen + 1);
        }
        break;
    case BoolType:
    case IntegerType:
    case DoubleType:
    case NullType:
        memcpy(&_sVal, &(sRight), sizeof(_sVal));
        break;
    case ObjectType:
        if (sRight._pJsonVal != NullPtr)
        {
            _sVal._pJsonVal = new Json(*(sRight._pJsonVal));
        }
        break;
    case ArrayType:
        if (sRight._pArrVal != NullPtr)
        {
            _sVal._pArrVal = new JsonArray(*(sRight._pArrVal));
        }
        break;
    }
}
void JsonValue::assign(bool bVal)
{
    _nType = BoolType;
    _sVal._boolVal = bVal;
}
void JsonValue::assign(const char* szVal)
{
    if(szVal == NullPtr)
    {
        _nType = NullType;
        _sVal._strVal = NullPtr;
    }
    else
    {
        _nType = StringType;
        int nLen = strlen(szVal);
        _sVal._strVal =  new char[nLen + 1];
        memcpy(_sVal._strVal, szVal, nLen + 1);
    }
}
void JsonValue::assign(long long llVal)
{
    _nType = IntegerType;
    _sVal._llVal = llVal;
}
void JsonValue::assign(double fVal)
{
    _nType = DoubleType;
    _sVal._fVal = fVal;
}
void JsonValue::assign(const Json& sVal)
{
    _nType = ObjectType;
    _sVal._pJsonVal = new Json(sVal);
}
void JsonValue::assign(const JsonArray& sArr)
{
    _nType = ArrayType;
    _sVal._pArrVal = new JsonArray(sArr);
}
JsonValue::operator const char*()
{
    if (_nType != StringType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return _sVal._strVal;
}
JsonValue::operator char*()
{
    if (_nType != StringType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return _sVal._strVal;
}
JsonValue::operator int()
{
    if (_nType != IntegerType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return (int)_sVal._llVal;
}
JsonValue::operator long long()
{
    if (_nType != IntegerType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return _sVal._llVal;
}
JsonValue::operator float()
{
    if (_nType != DoubleType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return (float)_sVal._fVal;
}
JsonValue::operator double()
{
    if (_nType != DoubleType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return (float)_sVal._fVal;
}
JsonValue::operator Json()
{
    if (_nType != ObjectType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return *(_sVal._pJsonVal);
}
JsonValue::operator JsonArray()
{
    if (_nType != ArrayType)
    {
        throw JsonException(getErrMsg(E_BAD_TYPE_CAST));
    }
    return *(_sVal._pArrVal);
}

////////////////////////////////////////
// JsonValueItem
JsonValueItem::JsonValueItem(const char* szKey, JsonValue* pJV)
: _szKey(0)
, _pVal(0)
, _pNextVal(0)
{
    if (szKey)
    {
        setKey(szKey);
    }
    if(pJV)
    {
        _pVal = new JsonValue(*pJV);
    }
}
JsonValueItem::JsonValueItem(const JsonValueItem& sRight)
{
    assign(sRight);
}
JsonValueItem::~JsonValueItem()
{
    freeRes();
}
JsonValueItem& JsonValueItem::operator = (const JsonValueItem& sRight)
{
    if (this != &sRight)
    {
        freeRes();
        assign(sRight);
    }
    return *this;
}
void JsonValueItem::freeRes()
{
    if (_pVal)
    {
        delete _pVal;
        _pVal = NullPtr;
    }
    if (_pNextVal)
    {
        delete _pNextVal;
        _pNextVal = NullPtr;
    }
    if(_szKey)
    {
        delete[] _szKey;
        _szKey = NullPtr;
    }
}
void JsonValueItem::assign(const JsonValueItem& sRight)
{
    if (sRight._pVal != NullPtr)
    {
        _pVal = new JsonValue(*sRight._pVal);
    }
    else
    {
        _pVal = NullPtr;
    }
    if (sRight._pNextVal != NullPtr)
    {
        _pNextVal = new JsonValueItem(*sRight._pNextVal);
    }
    else
    {
        _pNextVal = NullPtr;
    }
    if(sRight._szKey != NullPtr)
    {
        int nLen = strlen(sRight._szKey);
        _szKey = new char[nLen + 1];
        memcpy(_szKey, sRight._szKey, nLen + 1);
    }
    else
    {
        _szKey = NullPtr;
    }
}
int JsonValueItem::setKey(const char* szKey)
{
    if (szKey != NullPtr)
    {
        if(_szKey != NullPtr) delete[] _szKey;
        int nLen = strlen(szKey);
        _szKey = new char[nLen + 1];
        memcpy(_szKey, szKey, nLen + 1);
    }
    return E_SUCCESS;
}
const char* JsonValueItem::getKey() const
{
    return _szKey;
}
////////////////////////////////////////
// Json
Json::Json()
: _pGrpVal(NullPtr)
, _nLen(0)
{
}
Json::~Json()
{
    freeRes();
}
Json::Json(const Json& sRight)
{
    assign(sRight);
}
Json& Json::operator = (const Json& sRight)
{
    if (this != &sRight)
    {
        freeRes();
        assign(sRight);
    }
    return *this;
}
int Json::parse(const char* pBuf)
{
    if (pBuf == NullPtr)
    {
        return E_NULL_PTR;
    }

    
    skipSpaces(pBuf);
    if (!eofBuffer(pBuf))
    {
        Json* pJS = NullPtr;
        int nRet = parseJson(pJS, pBuf);
        if (nRet == E_SUCCESS)
        {
            freeRes();
            assign(*pJS);
        }
        return nRet;
        
    }
    return E_EMPTY_STRING;
}
int Json::load(const char* pFilePath)
{
    if (pFilePath == NullPtr)
    {
        return E_NULL_PTR;
    }
    FILE* pFile = fopen(pFilePath, "r");
    if (pFile == NullPtr)
    {
        return E_OPEN_FILE_ERROR;
    }

    std::string str;
    fseek(pFile, 0, SEEK_SET);
    long long lStart = ftell(pFile);
    fseek(pFile, 0, SEEK_END);
    long long lEnd = ftell(pFile);
    str.reserve((unsigned int)(lEnd - lStart));
     fseek(pFile, 0, SEEK_SET);
    int rd = 0;
    char szBuf[513];
    while (true)
    {
        rd = fread(szBuf, 1, 512, pFile);
        szBuf[rd] = 0;
        if (rd <= 0)
        {
            break;
        }
        str += szBuf;
    }
    fclose(pFile);


    return parse(str.c_str());
}

int Json::save(const char* pFilePath)
{
    if (pFilePath == NullPtr)
    {
        return E_NULL_PTR;
    }
    FILE* pFile = fopen(pFilePath, "w");
    if (pFile == NullPtr)
    {
        return E_OPEN_FILE_ERROR;
    }

    std::string strDump;
    dumpFormat(strDump);

    int nLen = strDump.length();
    int wr = 0;
    int i = 0;
    const char* szBuf = strDump.c_str();
    while(nLen > 0)
    {
        wr = fwrite(szBuf + i, 1, nLen >= 512 ? 512 : nLen, pFile);
        i += wr;
        nLen -= wr;
    }

    fclose(pFile);

    return E_SUCCESS;
}

JsonValue* Json::set(const char* szKey, JsonValue& sVal)
{
    if (szKey == NullPtr)
    {
        throw JsonException(getErrMsg(E_NULL_PTR));
    }
    JsonValue* pRet = NullPtr;
    if (_pGrpVal == NullPtr)
    {
        _pGrpVal = new JsonValueItem(szKey, &sVal);
        pRet = _pGrpVal->_pVal;
    }
    else
    {
        JsonValueItem* pGrpCur = _pGrpVal;
        JsonValueItem* pGrpPre = NullPtr;
        JsonValue* pJV = NullPtr;
        while(pGrpCur != NullPtr)
        {
            pJV = pGrpCur->_pVal;
            int nCmp = strcmp(szKey, pGrpCur->_szKey);
            if ( nCmp == 0)
            {
                return NullPtr;
            }
            else if (nCmp < 0)
            {
                // pGrpPre ²åÈë
                break;
            }
            else
            {
                pGrpPre = pGrpCur;
                pGrpCur = pGrpPre->_pNextVal;
            }
        }
        if (pGrpPre == NullPtr)
        {
            pGrpPre = new JsonValueItem(szKey, &sVal);
            pRet = pGrpPre->_pVal;
            pGrpPre->_pNextVal = _pGrpVal;
            _pGrpVal = pGrpPre;
        }
        else
        {
            pGrpCur = new JsonValueItem(szKey, &sVal);
            pRet = pGrpCur->_pVal;
            pGrpCur->_pNextVal = pGrpPre->_pNextVal;
            pGrpPre->_pNextVal = pGrpCur;
        }
    }
    _nLen++; 
    return pRet;
}
JsonValue* Json::get(const char* szKey) const
{
    JsonValue* pJV = NullPtr;
    if (szKey)
    {
        JsonValueItem* pJVI = _pGrpVal;
        while(pJVI)
        {
            if (strcmp(szKey, pJVI->_szKey) == 0)
            {
                pJV = pJVI->_pVal;
                break;;
            }
            pJVI = pJVI->_pNextVal;
        }
    }
    return pJV;
}

void Json::dump(std::string& strDump) const
{
    dumpValueGroup(_pGrpVal, strDump, 0);
}
void Json::dumpFormat(std::string& strDump, int nSpace) const
{
    dumpValueGroup(_pGrpVal, strDump, nSpace);
}

void Json::dumpValueGroup(JsonValueItem* pGroup, std::string& strDump, int nSpace) const
{
    strDump += "{";
    if (nSpace > 0)
    {
        strDump += "\n";
    }
    JsonValueItem* pGrp = pGroup;
    while(pGrp)
    {
        JsonValue* pJV = pGrp->_pVal;
        for (int i=0; i<nSpace; i++)
        {
            strDump += " ";
        }
        strDump += "\"";
        strDump += pGrp->_szKey;
        strDump += "\" : ";
        
        dumpValue(pJV, strDump, nSpace);
        
        pGrp = pGrp->_pNextVal;
        if (pGrp != NullPtr)
        {
            if (nSpace > 0)
            {
                strDump += ",\n";
            }
            else
            {
                strDump += ",";
            }
            
        }
    }
    if (nSpace > 0)
    {
        strDump += "\n";
        for (int i=0; i<nSpace - FORMAT_SPACE; i++)
        {
            strDump += " ";
        }
    }
    
    strDump += "}";
}
void Json::dumpArray(JsonArray* pArr, std::string& strDump, int nSpace) const
{
    if (pArr)
    {
        strDump += "[";
        if (nSpace > 0)
        {
            strDump += "\n";
        }
        int nSize = pArr->getSize() - 1;
        for(int i=0; i <= nSize; i++)
        {
            JsonValue* pJV = pArr->get(i);
            for (int j=0; j<nSpace; j++)
            {
                strDump += " ";
            }
            dumpValue(pJV, strDump, nSpace);
            if (i != nSize)
            {
                if (nSpace > 0)
                {
                    strDump += ",\n";
                }
                else
                {
                    strDump += ",";
                }
            }

        }
        if (nSpace > 0)
        {
            strDump += "\n";
            for (int i=0; i<nSpace - FORMAT_SPACE; i++)
            {
                strDump += " ";
            }
        }        
        strDump += "]";
    }
}
void Json::dumpValue(JsonValue* pJV, std::string& strDump, int nSpace) const
{
    if (pJV)
    {
        switch(pJV->_nType)
        {
        case StringType:
            if (pJV->_sVal._strVal != NullPtr)
            {
                strDump += "\"";
                strDump += pJV->_sVal._strVal;
                strDump += "\"";
            }
            else
            {
                strDump += "\"\"";
            }
            break;
        case BoolType:
            if (pJV->_sVal._boolVal)
            {
                strDump += "true";
            }
            else
            {
                strDump += "false";
            }
            break;
        case IntegerType:
            {
                char szBuf[9] = {0};
                sprintf(szBuf, "%ld", pJV->_sVal._llVal);
                strDump += szBuf;
            }
            break;
        case DoubleType:
            {
                char szBuf[9] = {0};
                sprintf(szBuf, "%lf", pJV->_sVal._fVal);
                strDump += szBuf;
            }
            break;
        case NullType:
            strDump += "null";
            break;
        case ObjectType:
            if (pJV->_sVal._pJsonVal != NullPtr)
            {
                pJV->_sVal._pJsonVal->dumpValueGroup(
                    pJV->_sVal._pJsonVal->_pGrpVal, strDump, nSpace >0 ? nSpace + FORMAT_SPACE : nSpace);
            }
            else
            {
                strDump += "{}";
            }
            break;
        case ArrayType:
            if (pJV->_sVal._pArrVal != NullPtr)
            {
                dumpArray(pJV->_sVal._pArrVal, strDump, nSpace >0 ? nSpace + FORMAT_SPACE : nSpace);
            }
            else
            {
                strDump += "[]";
            }
            break;
        }
    }
}

void Json::freeRes()
{
    if (_pGrpVal)
    {
        delete _pGrpVal;
        _pGrpVal = NullPtr;
    }
}
void Json::assign(const Json& sRight)
{
    if (sRight._pGrpVal)
    {
        _pGrpVal = new JsonValueItem(*sRight._pGrpVal);
    }
    else
    {
        _pGrpVal = NullPtr;
    }
    _nLen = sRight._nLen;
}
JsonValue& Json::operator [] (const char* szKey)
{
    if (szKey == NullPtr)
    {
        throw JsonException(getErrMsg(E_NULL_PTR));
    }
    JsonValue* pJV = get(szKey);
    if (pJV == NullPtr)
    {
        JsonValue jv;
        pJV = set(szKey, jv);
    }
    return *pJV;
}
const JsonValue& Json::operator [] (const char* szKey) const
{
    if (szKey == NullPtr)
    {
        throw JsonException(getErrMsg(E_NULL_PTR));
    }
    JsonValue* pJV = get(szKey);
    if (pJV == NullPtr)
    {
        throw JsonException(getErrMsg(E_KEY_NOT_EXISTS));
    }
    return *pJV;
}

void Json::skipSpaces(const char*& szBuf)
{
    while(eofBuffer(szBuf) == false)
    {
        if (*szBuf == ' ' ||
            *szBuf == '\t' ||
            *szBuf == '\r' ||
            *szBuf == '\n')
        {
            szBuf++;
        }
        else
        {
            bool bSkipCmt = false;
            if (*szBuf == '/')
            {
                if (*(szBuf + 1) && *(szBuf + 1) == '/')
                {
                    bSkipCmt = true;
                }
            }
            else
            {
                if (*szBuf == '#')
                {
                    bSkipCmt = true;
                }
            }
            if (bSkipCmt)
            {
                while(eofBuffer(szBuf) == false)
                {
                    szBuf++;
                    if(*szBuf == '\n')
                    {
                        szBuf++;
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
}
bool Json::eofBuffer(const char*& szBuf)
{
    if (szBuf == NullPtr || *szBuf == '\0')
    {
        return true;
    }
    return false;
}
int Json::parseJson(Json*& pJS, const char*& szBuf)
{
    if (szBuf == NullPtr)
    {
        return E_NULL_PTR;
    }
    if (*szBuf != '{')
    {
        return E_BRACE_MISSING;
    }
    
    int nRet = E_NOT_JSON_SYNTAX;
    bool nComma = false;
    bool bEndBrace = false;
    bool bHasVal = false;
    szBuf++;
    skipSpaces(szBuf);
    while(!eofBuffer(szBuf))
    {
        nRet = E_SUCCESS;
        if (*szBuf == '\"')
        {
            int nStrLen = 0;
            const char* pStart = NullPtr;
            nRet = parseKey(szBuf, pStart, nStrLen);
            if ( nRet != E_SUCCESS)
            {
                break;
            }
            if (nStrLen == 0)
            {
                nRet = E_KEY_MISSING;
                break;
            }
            skipSpaces(szBuf);
            if (eofBuffer(szBuf))
            {
                nRet = E_COLON_MISSING;
                break;
            }

            if (*szBuf != ':')
            {
                nRet = E_COLON_MISSING;
                break;
            }

            szBuf++;
            skipSpaces(szBuf);
            if (eofBuffer(szBuf))
            {
                nRet = E_KEY_MISSING;
                break;
            }

            JsonValue* pJV = NullPtr;
            nRet = parseJsonValue(pJV, szBuf);
            if (nRet != E_SUCCESS)
            {
                nRet = E_PARSE_JASON_VALUE;
                break;
            }
            nComma = false;
            if (pJS == NullPtr)
            {
                pJS = new Json;                       
            }
            char* szKey = new char[nStrLen + 1];
            memset(szKey, 0, nStrLen + 1);
            memcpy(szKey, pStart, nStrLen);
            if (!pJS->set(szKey, *pJV))
            {
                nRet = E_DUPLICATE_KEY;
                break;
            }
            delete[] szKey;
            bHasVal = true;
        }
        else if (*szBuf == ',')
        {
            if (bHasVal == true)
            {
                nComma = true;
                szBuf++;
            }
            else
            {
                nRet = E_EXTRAL_COMMA;
                break;
            }
            
        }
        else if (*szBuf == '}')
        {
            if (nComma)
            {
                nRet = E_EXTRAL_COMMA;
            }
            else
            {
                bEndBrace = true;
                szBuf++;
            }            
            break;
        }
        else
        {
            nRet = E_KEY_MISSING;
            printf("xxx");
            break;
        }
  //      szBuf++;
        skipSpaces(szBuf);
    }
    if (!bEndBrace)
    {
        nRet = E_PARSE_JASON_OBJECT;
    }
    if(nRet != E_SUCCESS)
    {
        if (pJS != NullPtr)
        {
            delete pJS;
            pJS = NullPtr;
        }
    }
    return nRet;
}
int Json::parseKey(const char*& szBuf, const char*& pStart, int& nLen)
{
    nLen = 0;
    if (szBuf == NullPtr)
    {
        return E_NULL_PTR;
    }
    if (*szBuf != '\"')
    {
        return E_QUOT_MISSING;
    }
    szBuf++;
    pStart = szBuf;
    const char* pEnd = NullPtr;
    while(!eofBuffer(szBuf))
    {
        if (*szBuf == '\"')
        {
            pEnd = szBuf;
            szBuf++;
            break;
        }
        szBuf++;
    }
    if (pEnd == NullPtr)
    {
        return E_KEY_MISSING;
    }
    nLen = (int)(pEnd - pStart);
    return E_SUCCESS;
}
int Json::parseJsonValue(JsonValue*& pJV, const char*& szBuf)
{
    if (szBuf == NullPtr)
    {
        return E_NULL_PTR;
    }
    int nRet = E_SUCCESS;
    if (!eofBuffer(szBuf))
    {
        if (*szBuf == '{')
        {
            Json* pJS = NullPtr;
            nRet = parseJson(pJS, szBuf);
            if (nRet != E_SUCCESS)
            {
                nRet = E_PARSE_JASON_OBJECT;
            }
            else
            {
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue(*pJS);
                }
            }
            
        }
        else if (*szBuf == '[')
        {
            JsonArray* pJArr = NullPtr;
            nRet = parseJsonArray(pJArr, szBuf);
            if (nRet != E_SUCCESS)
            {
                nRet = E_PARSE_JASON_ARRAY;
            }
            else
            {
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue(*pJArr);
                }
            }
            
        }
        else if (*szBuf == 'n')
        {
            // null
            if (strncmp(szBuf, "null", 4) == 0)
            {
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue((char*)0);
                }
                szBuf += 4;
            }
            else
            {
                nRet = E_UNKNOWN_VAULE;
            }
        }
        else if (*szBuf == 'f')
        {
            // false
            if (strncmp(szBuf, "false", 5) == 0)
            {
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue(false);
                }
                szBuf += 5;
            }
            else
            {
                nRet = E_UNKNOWN_VAULE;
            }
        }
        else if (*szBuf == 't')
        {
            // true
            if (strncmp(szBuf, "true", 4) == 0)
            {
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue(true);
                }
                szBuf += 4;
            }
            else
            {
                nRet = E_UNKNOWN_VAULE;
            }
        }
        else if (*szBuf == '\"')
        {
            int nStrLen = 0;
            const char* pStart = NullPtr;
            nRet = parseKey(szBuf, pStart, nStrLen);
            if(nRet != E_SUCCESS)
            {
                nRet = E_STRING_VALUE_ERROR;
            }
            else
            {
                char* szVal = new char[nStrLen + 1];
                memset(szVal, 0, nStrLen + 1);
                memcpy(szVal, pStart, nStrLen);
                if (pJV == NullPtr)
                {
                    pJV = new JsonValue(szVal);
                }
            }
        }
        else
        {
            // integer&double
            const char* pStart = szBuf;
            while(!eofBuffer(szBuf))
            {
                if (*szBuf == ' ' ||
                    *szBuf == '\t' ||
                    *szBuf == ',' ||
                    *szBuf == ']' ||
                    *szBuf == '}' ||
                    *szBuf == '\r' ||
                    *szBuf == '\n')
                {
                    if (*szBuf != ']' &&
                        *szBuf != '}')
                    {
                        szBuf++;
                    }
                    
                    break;
                }
                else
                {
                    szBuf++;
                }
            }
            std::string str(pStart, szBuf - pStart - 1);
            NumberType type = detectNumberType(str.c_str());
            switch (type)
            {
            case Unkown:
                nRet = E_ENKNOW_NUMBER;
                break;
            case Int:
                {
                    bool bStat = false;
                    long long llv = toInt(str.c_str(), bStat);
                    if (bStat)
                    {
                        pJV = new JsonValue(llv);
                    }
                }
                break;
            case Double:
                {
                    bool bStat = false;
                    double dv = toDouble(str.c_str(), bStat);
                    if (bStat)
                    {
                        pJV = new JsonValue(dv);
                    }
                }
                break;
            }
            
        }
        if(nRet != E_SUCCESS)
        {
            if (pJV != NullPtr)
            {
                delete pJV;
                pJV = NullPtr;
            }
        }
    }
    else
    {
        nRet = E_VALUE_MISSING;
    }
    

    return nRet;
}
int Json::parseJsonArray(JsonArray*& pJArr, const char*& szBuf)
{
    if (szBuf == NullPtr)
    {
        return E_NULL_PTR;
    }
    if (*szBuf != '[')
    {
        return E_BRACKET_MISSING;
    }
    int nRet = E_BRACKET_MISSING;
    bool nComma = false;
    bool bEndBrace = false;
    bool bHasVal = false;
    szBuf++;
    skipSpaces(szBuf);
    while (!eofBuffer(szBuf))
    {
        if (*szBuf == ',')
        {
            if(bHasVal)
            {
                szBuf++;
                nComma = true;
            }
            else
            {
                nRet = E_EXTRAL_COMMA;
                break;
            }
        }
        else if (*szBuf == ']')
        {
            if (nComma)
            {
                nRet = E_EXTRAL_COMMA;
            }
            else
            {
                bEndBrace = true;
                szBuf++;
            }
            break;
        }
        else if (*szBuf == '[')
        {
            JsonArray* pNewJArr = NullPtr;
            nRet = parseJsonArray(pNewJArr, szBuf);
            if(nRet != E_SUCCESS)
            {
                break;
            }
            if (pJArr == NullPtr)
            {
                pJArr = new JsonArray;
            }
            JsonValue jv(*pNewJArr);
            pJArr->add(jv);

            bHasVal = true;
            nComma = false;
        }
        else
        {
            JsonValue* pNewJV = NullPtr;
            nRet = parseJsonValue(pNewJV, szBuf);
            if(nRet != E_SUCCESS)
            {
                break;
            }
            if (pJArr == NullPtr)
            {
                pJArr = new JsonArray;
            }
            pJArr->add(*pNewJV);
            bHasVal = true;
            nComma = false;
        }
        skipSpaces(szBuf);
    }
    if (!bEndBrace)
    {
        nRet = E_BRACKET_MISSING;
    }
    if (nRet != E_SUCCESS)
    {
        if (pJArr != NullPtr)
        {
            delete pJArr;
        }
    }
    return nRet;
}

}


#ifdef _MSC_VER
#pragma warning(pop)
#endif
