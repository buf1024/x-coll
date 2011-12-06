/*
 * File       : Prototype.h
 * Description: 
 * Version    : 2011-10-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_PROTOTYPE_H_
#define XBASIC_PROTOTYPE_H_

namespace Util
{

template<typename TheClass>
class Prototype
{
public:
    Prototype()
    {

    }
    virtual ~Prototype()
    {

    }

public:
    virtual TheClass* Clone()
    {
        return new TheClass(*(static_cast<TheClass*>(this)));
    }
};

#define DECL_PROTOTYPE(TheClass)

}

#endif /* XBASIC_PROTOTYPE_H_ */

