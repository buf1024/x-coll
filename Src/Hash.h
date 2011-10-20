/*
 * File       : Hash.h
 * Description: 计算Hash值的接口
 * Version    : 2010-11-9 1.0 Created
 *              2011-9 24 1.1 多操作系统支持
 * Author     : buf1024@gmail.com
 */

#ifndef HASH_H_
#define HASH_H_
/*

#include "XBasicCore.h"

XBASIC_NAMEPACE_BEGIN

class HashImpl;
*
 * 计算Hash值的接口

class XBASICAPI Hash
{
public:
    *
     * 构造函数，要提供某种HASH的实现
     * @param pImpl 某种HASH的实现

    Hash(HashImpl* pImpl);
    ~Hash();
public:
    *
     * 计算 ASCII 形式的字符串HASH值
     * @param strValue 要计算的字符串
     * @return HASH值

    std::string GetStringHash(std::string strValue);
    *
     * 计算宽字符形式的字符串HASH值e
     * @param strValue 要计算的字符串
     * @return HASH值

    std::string GetStringHash(std::wstring strValue);
    *
     * 计算文件的HASH值
     * @param strFile 文件的路径
     * @return HASH值, 如果文件不存在或者出错则返回空字符串

    std::string GetFileHash(std::string strFile);
private:
    HashImpl* m_pImpl; < 具体的实现

};

XBASIC_NAMESPACE_END
*/

#endif /* HASH_H_ */
