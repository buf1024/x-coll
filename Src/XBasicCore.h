/*
 * File       : XBasicCore.h
 * Description: 与平台相关的一些宏定义
 * Version    : 2011-9-24 Created
 * Author     : buf1024@gmail.com
 */
#ifndef XBASICCORE_H_
#define XBASICCORE_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef MSWINDOWS
#include <Windows.h>
#endif

#define USING_NAMESPACE

// 是否使用命名空间
#ifdef USING_NAMESPACE

#define XBASICNAMESPACE XBasic

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

#ifdef MSWINDOWS
  // 是否编译成DLL
  #ifdef XBASICDLL
    #define XBASICAPI __declspec(dllexport)
  #else
    // 是否编译成静态库
    #ifdef XBASICSTAT
      #define XBASICAPI
    #else

      // 使用DLL时 
      #ifdef USEDLL
        #define XBASICAPI __declspec(dllimport)
        // 使用时，连接到不同的库  
        #ifdef _DEBUG
          #pragma comment(lib, "xbasicd.lib")
        #else
          #pragma comment(lib, "xbasic.lib")
        #endif
      #else
        #define XBASICAPI
        // 使用时，连接到不同的库  
        #ifdef _DEBUG
          #pragma comment(lib, "xbasic_statd.lib")
        #else
          #pragma comment(lib, "xbasic_stat.lib")
        #endif
      #endif
    #endif
  #endif

#else

//#define XBASICAPI

#endif

#define NullPtr             (0)
#define BUF_SIZE            (1024)
#define MAX_LINE            (4096)
#define ASSERT(expr)        assert(expr)

#define MIN(a, b)           ((a)>(b)?(b):(a))
#define MAX(a, b)           ((a)>(b)?(a):(b))

#endif /* XBASICCORE_H_ */
