/*
 * File       : Singleton.h
 * Description: 
 * Version    : 2011-10-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace Util
{

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

}

#endif /* SINGLETON_H_ */
