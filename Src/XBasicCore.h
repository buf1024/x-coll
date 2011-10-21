/*
 * File       : XBasicCore.h
 * Description: ��ƽ̨��ص�һЩ�궨��
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

// �Ƿ�ʹ�������ռ�
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
  // �Ƿ�����DLL
  #ifdef XBASICDLL
    #define XBASICAPI __declspec(dllexport)
  #else
    // �Ƿ����ɾ�̬��
    #ifdef XBASICSTAT
      #define XBASICAPI
    #else

      // ʹ��DLLʱ 
      #ifdef USEDLL
        #define XBASICAPI __declspec(dllimport)
        // ʹ��ʱ�����ӵ���ͬ�Ŀ�  
        #ifdef _DEBUG
          #pragma comment(lib, "xbasicd.lib")
        #else
          #pragma comment(lib, "xbasic.lib")
        #endif
      #else
        #define XBASICAPI
        // ʹ��ʱ�����ӵ���ͬ�Ŀ�  
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
