/*
 * File       : ParamValue.h
 * Description: 结果参数封装
 * Version    : 2011-9-29 Created
 * Author     : buf1024@gmail.com
 */

#include "XBasicCore.h"
#include "StdString.h"

#ifndef UTIL_H_
#define UTIL_H_

XBASIC_NAMEPACE_BEGIN


class XBASICAPI ParamValue
{
public:
    ParamValue()
    {
        m_strVal = "";
        memset(&m_sVal, 0, sizeof(m_sVal));
    }
    ParamValue(const std::string strVal)
    {
        m_strVal = strVal;
    }
    ParamValue(int nVal)
    {
        m_sVal.nVal = nVal;
    }
    ParamValue(long lVal)
    {
        m_sVal.lVal = lVal;
    }
    ParamValue(double fVal)
    {
        m_sVal.fVal = fVal;
    }
    ~ParamValue()
    {

    }

public:

    ParamValue& operator = (const ParamValue& sVal)
    {
        if (&sVal != this)
        {
            m_strVal = sVal.m_strVal;
            memcpy(&m_sVal, &sVal.m_sVal, sizeof(sVal));
        }
        return *this;
    }

    operator bool ()
    {
        return m_sVal.bVal;
    }

    operator int ()
    {
        return m_sVal.nVal;
    }
    operator long ()
    {
        return m_sVal.lVal;
    }
    operator double ()
    {
        return m_sVal.fVal;
    }

    operator std::string ()
    {
        return m_strVal;
    }

private:
    std::string m_strVal;
    union
    {
        bool bVal;
        int nVal;
        long lVal;
        double fVal;
    }m_sVal;

};

XBASIC_NAMESPACE_END

#endif /* UTIL_H_ */



