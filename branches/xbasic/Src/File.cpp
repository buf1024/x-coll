/*
 * File       : File.cpp
 * Description: 
 * Version    : 2011-10-25 Created
 * Author     : buf1024@gmail.com
 */
#include "File.h"
#include "Visitor.h"

USE_XBASIC_NAMESPACE;

File::File(void)
{
    pData = new FileDataWrapper;
}

File::~File(void)
{
    delete pData;
}

void File::Accept(Visitor* pVisitor)
{
    if (pVisitor)
    {
        pVisitor->Visit(this);
    }
}
