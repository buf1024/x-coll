/*
 * File       : xbasic.h
 * Description: 整个库所提供的功能。
 *              通情况如果只用到其中的一些功能，则使用静态库，只包含相关的头文件，不要使用这个头文件。
 *              这个头文件提供给懒人使用的。
 * Version    : 2011-9-24 Created
 * Author     : buf1024@gmail.com
 */



sdfadfasdf






#ifndef XBASIC_H_
#define XBASIC_H_

#include "XBasicCore.h"

// 字符串服务扩展

// xml 格式的应用程序配置
#include "Config.h"
#include "ConfigApp.h"

// Ini 格式的应用程序配置
#include "IniConfig.h"

// 基本的文件服务
#include "FileService.h"

// 计算Hash值
#include "Hash.h"
#include "HashImpl.h"
#include "HashCRC32Impl.h"
#include "HashMD5Impl.h"
#include "HashSHA1Impl.h"

// 实例是否已经运行
#include "SingletonInst.h"

// 日志服务

// 测试框架

#endif /* XBASIC_H_ */
