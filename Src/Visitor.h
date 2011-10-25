/*
 * File       : Visitor.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */

#ifndef VISITOR_H_
#define VISITOR_H_

XBASIC_NAMEPACE_BEGIN
class Element;
class XBASICAPI Visitor
{
public:
    Visitor(){}
    virtual ~Visitor(){}

    virtual void Visit(Element* pElem){}
};

XBASIC_NAMESPACE_END


#endif /* VISITOR_H_ */

