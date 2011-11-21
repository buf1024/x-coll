/*
 * File       : Singleton.h
 * Description: 
 * Version    : 2011-10-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_SINGLETON_H_
#define XBASIC_SINGLETON_H_

#include "XBasicCore.h"

XBASIC_NAMEPACE_BEGIN 

template <typename TheClass>
class Singleton
{
protected:
    Singleton()
    {

    }
public:
    virtual ~Singleton()
    {

    }
public:
    static TheClass* GetInstPtr()
    {
        if (sm_pInst == 0)
        {
            sm_pInst = new TheClass;
        }
        return sm_pInst;
    }
    static TheClass& GetInst()
    {
        if (sm_pInst == 0)
        {
            sm_pInst = new TheClass;
        }
        return *sm_pInst;
    }
    static void ReleaseRC()
    {
        if (sm_pInst != 0)
        {
            delete sm_pInst;
            sm_pInst = 0;
        }
    }
private:
    static TheClass* sm_pInst;
};

template <typename TheClass>
TheClass* Singleton<TheClass>::sm_pInst = 0;


#define DECL_SINGLETON(TheClass)          \
    friend class  Singleton<TheClass>;    \

XBASIC_NAMESPACE_END

#endif /* XBASIC_SINGLETON_H_ */
