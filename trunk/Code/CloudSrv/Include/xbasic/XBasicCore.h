/*
 * File       : XBasicCore.h
 * Description: 与平台相关的一些宏定义
 * Version    : 2011-9-24 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XBASIC_XBASICCORE_H_
#define XBASIC_XBASICCORE_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 目前在WINDOWS下面只支持MSVC
#ifdef _MSC_VER
#include <Windows.h>
#pragma warning(disable:4996)
#endif

#define USING_NAMESPACE

// 是否使用命名空间
#ifdef USING_NAMESPACE

#define XBASICNAMESPACE xbasic

#define XBASIC_NAMEPACE_BEGIN                                                            \
    namespace XBASICNAMESPACE {                                                          \

#define XBASIC_NAMESPACE_END                                                             \
    }                                                                                    \

#define USE_XBASIC_NAMESPACE using namespace XBASICNAMESPACE;

#else

#define XBASIC_NAMEPACE_BEGIN
#define XBASIC_NAMESPACE_END
#define USE_XBASIC_NAMESPACE

#endif

#ifndef XBASICSTAT
#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "xbasic_statd.lib")
#else
#pragma comment(lib, "xbasic_stat.lib")
#endif
#endif
#endif

#define XBASICAPI

#define NullPtr             (0)
#define BUF_SIZE            (1024)
#define MAX_LINE            (4096)
#define ASSERT(expr)        assert(expr)

#define MIN(a, b)           ((a)>(b)?(b):(a))
#define MAX(a, b)           ((a)>(b)?(a):(b))
#define UnRefParam(param)   ((void)(param))

#endif /* XBASIC_XBASICCORE_H_ */
