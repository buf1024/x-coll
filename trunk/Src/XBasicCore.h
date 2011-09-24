/*
 * File       : XBasicCore.h
 * Description: 与平台相关的一些定义和一些公共的字义
 * Version    : 2011-9-24 Created
 * Author     : buf1024@gmail.com
 */

#ifndef XBASICCORE_H_
#define XBASICCORE_H_

// 是否使用名命空间
#ifdef USING_NAMESPACE

#define XBASICNAMESPACE XBasic

#define XBASIC_NAMEPACE_BEGIN                                                            \
    namespace xbasic {                                                                   \

#define XBASIC_NAMESPACE_END                                                             \
    }                                                                                    \

#else

#define XBASIC_NAMEPACE_BEGIN
#define XBASIC_NAMESPACE_END

#endif

#ifdef WINDOWS
// 编译成动态库时
#ifdef XBASICDLL
  #define XBASICAPI __decspec(dllexport)
#else
  // 编译静态态库时
  #ifdef XBASICSTAT
    #define XBASICAPI
  #else
    // 编译成动态库,连接到此库时
    #define XBASICAPI __decspec(dllimport)
  #endif

  // 调试或非调试要连接到的库
  #ifdef _DEBUG
    #pragma comment(lib, "xbasic.lib")
  #else
    #pragma comment(lib, "xbasicd.lib")
  #endif
#endif


#else

#define XBASICAPI

#endif

#define NullPtr             (0)

#define Min(a, b)           ((a)>(b)?(b):(a))
#define Max(a, b)           ((a)>(b)?(a):(b))

#endif /* XBASICCORE_H_ */
