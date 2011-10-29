/*
 * File       : SigntonApp.h
 * Description: ȷ��Ӧ�ó���ֻ����һ��
 *              ���ӣ�
 *               ��main���������������ƵĴ���
 *                SingletonApp inst;
 *                if(!inst) //Not Singleton
 *                {
 *                   ... //Do other things
 *                }
 * Version    : 2011-02-11 Created
 *              2010-9-26 �����ϵͳ֧��
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_SINGLETONAPP_H_
#define XBASIC_SINGLETONAPP_H_

#include "XBasicCore.h"
#include "StdString.h"

// ��MSWINDOWS��ʹ���ں˶���

XBASIC_NAMEPACE_BEGIN

class XBASICAPI SingletonApp
{
public:
    SingletonApp(const std::string strName = "");
    ~SingletonApp(void);


public:
    bool operator == (bool bCmp);
    bool operator != (bool bCmp);
    bool operator ! ();
    operator bool ();

private:
    bool m_bInstNotExist;
    FILE* m_pFile;
};

XBASIC_NAMESPACE_END

#endif /* XBASIC_SINGLETONAPP_H_ */
