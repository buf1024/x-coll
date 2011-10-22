/*
 * File       : TestCmmHdr.h
 * Description: 
 * Version    : 2011-9-28 Created
 * Author     : buf1024@gmail.com
 */

#ifndef TESTCMMHDR_H_
#define TESTCMMHDR_H_

#include <gtest/gtest.h>

#ifdef MSWINDOWS

#if _DEBUG
#pragma comment(lib, "gtestd.lib")
#else
#pragma comment(lib, "gtest.lib")
#endif

#pragma warning(disable:4996)

#endif



#endif /* TESTCMMHDR_H_ */
