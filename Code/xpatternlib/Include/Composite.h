/*
 * File       : Composite.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XPATTERN_COMPOSITE_H_
#define XPATTERN_COMPOSITE_H_

#include "Component.h"

XPATTERN_NAMESPACE_BEGIN

class Composite
    : public Component
{
public:
    Composite(){}
    virtual ~Composite(){}

public:
};

XPATTERN_NAMESPACE_END

#endif /* XPATTERN_COMPOSITE_H_ */
