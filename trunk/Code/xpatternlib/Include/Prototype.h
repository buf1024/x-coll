/*
 * File       : Prototype.h
 * Description: 
 * Version    : 2011-10-26 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XPATTERN_PROTOTYPE_H_
#define XPATTERN_PROTOTYPE_H_

#include "XpatternCore.h"

XPATTERN_NAMESPACE_BEGIN

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

XPATTERN_NAMESPACE_END

#endif /* XPATTERN_PROTOTYPE_H_ */

