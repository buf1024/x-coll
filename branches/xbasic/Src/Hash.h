/*
 * File       : Hash.h
 * Description: ����Hashֵ�Ľӿ�
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */
#ifndef HASH_H_
#define HASH_H_

#include "XBasicCore.h"
#include "StdString.h"

XBASIC_NAMEPACE_BEGIN

class HashImpl;
/**
 * ����Hashֵ�Ľӿ�
 */

class XBASICAPI Hash
{
public:
   /**
     * ���캯����Ҫ�ṩĳ��HASH��ʵ��
     * @param pImpl ĳ��HASH��ʵ��
     */

    Hash(HashImpl* pImpl);
    ~Hash();
public:
    /**
     * ���� ASCII ��ʽ���ַ���HASHֵ
     * @param strValue Ҫ������ַ���
     * @return HASHֵ
     */

    std::string GetStringHash(std::string strValue);
    /**
     * ������ַ���ʽ���ַ���HASHֵe
     * @param strValue Ҫ������ַ���
     * @return HASHֵ
     */

    std::string GetStringHash(std::wstring strValue);
    /**
     * �����ļ���HASHֵ
     * @param strFile �ļ���·��
     * @return HASHֵ, ����ļ������ڻ��߳����򷵻ؿ��ַ���
     */

    std::string GetFileHash(std::string strFile);
private:
    HashImpl* m_pImpl; /*< �����ʵ��*/

};


XBASIC_NAMESPACE_END


#endif /* HASH_H_ */


