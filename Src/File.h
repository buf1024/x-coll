/*
 * File       : File.h
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XBASIC_FILE_H_
#define XBASIC_FILE_H_

#include "Element.h"
#include <list> //ÎÞÐò

XBASIC_NAMEPACE_BEGIN

class XBASICAPI File :
    public Element
{
public:
    File(void);
    virtual ~File(void);

public:
    virtual void Accept(Visitor* pVisitor);

    int List(std::list<File*>& lstFiles);

private:
    typedef struct FileDataWrapper
    {
        std::list<File*> m_lstFiles;
    }FileDataWrapper;

private:
    FileDataWrapper* pData;

};

XBASIC_NAMESPACE_END

#endif /* XBASIC_FILE_H_ */
