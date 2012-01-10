/*
 * File       : Config.h
 * Description: 
 * Version    : 2011-11-23 Created
 * Author     : buf1024@gmail.com
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 目前在WINDOWS下面只支持MSVC
#ifdef _MSC_VER
#include <Windows.h>
#pragma warning(disable:4996)
#endif

#define NullPtr             (0)
#define BUF_SIZE            (1024)
#define MAX_LINE            (4096)
#define ASSERT(expr)        assert(expr)

#define MIN(a, b)           ((a)>(b)?(b):(a))
#define MAX(a, b)           ((a)>(b)?(a):(b))

#define UnRefParam(param)   ((void)(param))

