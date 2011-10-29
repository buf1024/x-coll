/*
 * File       : SigntonApp.h
 * Description: 确保应用程序只启动一次
 *              例子：
 *               在main函数里，添加以下类似的代码
 *                SingletonApp inst;
 *                if(!inst) //Not Singleton
 *                {
 *                   ... //Do other things
 *                }
 * Version    : 2011-02-11 Created
 *              2010-9-26 多操作系统支持
 * Author     : buf1024@gmail.com
 */

#ifndef XBASIC_SINGLETONAPP_H_
#define XBASIC_SINGLETONAPP_H_

#include "XBasicCore.h"
#include "StdString.h"

// 在MSWINDOWS不使用内核对象

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
