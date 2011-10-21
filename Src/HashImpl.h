/*
 * File       : HashImpl.h
 * Description: ����Hashֵ�Ľӿڵĳ���ʵ��
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */

#ifndef HASHIMPL_H_
#define HASHIMPL_H_


#include "XBasicCore.h"
#include "StdString.h"

XBASIC_NAMEPACE_BEGIN


class XBASICAPI HashImpl
{
public:
    HashImpl(){}
    virtual ~HashImpl(){}
public:
    virtual std::string GetStringHash(std::string strValue) = 0;
    virtual std::string GetStringHash(std::wstring strValue) = 0;
    virtual std::string GetFileHash(std::string strFile) = 0;

};

XBASIC_NAMESPACE_END


#endif /* HASHIMPL_H_ */
