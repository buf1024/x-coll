/*
 * File       : Cryptic.cpp
 * Description: 
 * Version    : 2011-12-15 Created
 * Author     : buf1024@gmail.com
 */
#include "Cryptic.h"
#include <string.h>

Cryptic::Cryptic()
: _pImpl(NullPtr)
{

}
Cryptic::~Cryptic()
{
    if (_pImpl != NullPtr)
    {
        delete _pImpl;
        _pImpl = NullPtr;
    }
}
bool Cryptic::Encrypt(const char* pSrc, char* pDest, unsigned int& nLen)
{
    return _pImpl->Encrypt(pSrc, pDest, nLen);
}
bool Cryptic::Decrypt(const char* pSrc, char* pDest, unsigned int& nLen)
{
    return _pImpl->Decrypt(pSrc, pDest, nLen);
}

void Cryptic::SetImpl(CrypticImpl* pImpl)
{
    if (pImpl != NullPtr)
    {
        if(_pImpl != NullPtr)
        {
            delete _pImpl;
        }
        _pImpl = pImpl;
    }
}

CrypticEmptyImpl::CrypticEmptyImpl()
{

}
CrypticEmptyImpl::~CrypticEmptyImpl()
{
}
bool CrypticEmptyImpl::Encrypt(const char* pSrc, char* pDest, unsigned int& nLen)
{
    memcpy(pDest, pSrc, nLen);
    return true;
}
bool CrypticEmptyImpl::Decrypt(const char* pSrc, char* pDest, unsigned int& nLen)
{
    memcpy(pDest, pSrc, nLen);
    return true;
}

