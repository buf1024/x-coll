/*
 * File       : Cryptic.h
 * Description: 
 * Version    : 2011-12-15 Created
 * Author     : buf1024@gmail.com
 */
#ifndef CLOUDSRV_CRYPTIC_H_
#define CLOUDSRV_CRYPTIC_H_
#include "Singleton.h"

USE_XBASIC_NAMESPACE

class CrypticImpl;
class Cryptic
	: public Util::Singleton<Cryptic>
{
	DECL_SINGLETON(Cryptic)
private:
	Cryptic();
public:
	~Cryptic();
public:
	bool Encrypt(const char* pSrc, char* pDest, unsigned int& nLen);
	bool Decrypt(const char* pSrc, char* pDest, unsigned int& nLen);

	void SetImpl(CrypticImpl* pImpl);

private:
	CrypticImpl* _pImpl;
};

class CrypticImpl 
{
public:
	virtual bool Encrypt(const char* pSrc, char* pDest, unsigned int& nLen) = 0;
	virtual bool Decrypt(const char* pSrc, char* pDest, unsigned int& nLen) = 0;
};


class CrypticEmptyImpl
	: public CrypticImpl
{
public:
    CrypticEmptyImpl();
    ~CrypticEmptyImpl();
public:
	virtual bool Encrypt(const char* pSrc, char* pDest, unsigned int& nLen);
	virtual bool Decrypt(const char* pSrc, char* pDest, unsigned int& nLen);
};


#endif // CLOUDSRV_CRYPTIC_H


