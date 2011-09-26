/*
 * File       : TestCase.h
 * Description: 
 * Version    : 2011-9-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTCASE_H_
#define TESTCASE_H_

#include "XBasicCore.h"
#include "StdString.h"

XBASIC_NAMEPACE_BEGIN

class XBASICAPI TestCase
{
public:
    TestCase()
    {

    }
    virtual ~TestCase(){}

public:
    virtual void Run() = 0;

    StdString GetName() const
    {
        return m_strName;
    }
    void SetName(StdString strName)
    {
        m_strName = strName;
    }

    TestCase* GetParent() const
    {
        return m_pParent;
    }
    void SetParent(TestCase* pTest)
    {
        m_pParent = pTest;
    }

protected:
    StdString m_strName;

    TestCase* m_pParent;
};

XBASIC_NAMESPACE_END

#endif /* TESTCASE_H_ */
