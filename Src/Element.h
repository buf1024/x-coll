/*
 * File       : Element.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */
#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "XBasicCore.h"

XBASIC_NAMEPACE_BEGIN

class Visitor;
class XBASICAPI Element
{
public:
    Element(void){}
    virtual ~Element(void){}

public:
    virtual void Accept(Visitor* pVisitor) = 0;
};

XBASIC_NAMESPACE_END

#endif /* ELEMENT_H_ */


