/*
 * File       : Element.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XPATTERN_ELEMENT_H_
#define XPATTERN_ELEMENT_H_

#include "XpatternCore.h"

XPATTERN_NAMESPACE_BEGIN

class Visitor;
class Element
{
public:
    Element(void)
    {

    }
    virtual ~Element(void)
    {

    }

public:
    virtual void Accept(Visitor* pVisitor)
    {

    }
};

XPATTERN_NAMESPACE_END

#endif /* XPATTERN_ELEMENT_H_ */


