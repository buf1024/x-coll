/*
 * File       : Visitor.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XPATTERN_VISITOR_H_
#define XPATTERN_VISITOR_H_

#include "XpatternCore.h"

XPATTERN_NAMESPACE_BEGIN

class Element;
class Visitor
{
public:
    Visitor(){}
    virtual ~Visitor(){}
public:
    virtual void Visit(Element* pElem){}
};

XPATTERN_NAMESPACE_END

#endif /* XPATTERN_VISITOR_H_ */

