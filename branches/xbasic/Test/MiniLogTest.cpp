#include "TestCmmHdr.h"
#include "Minilog.h"

USE_XBASIC_NAMESPACE


TEST(MinilogTest, Minilog)
{

	SET_LOG_PATH("E:\\");
    SET_LOG_FILE("hello");
	SET_LOG_LEVEL("WArn");
	LOG_DEBUG("%s %d\n", "hello", 207)
	LOG_INFO("%s %d\n", "hello", 207)
	LOG_WARN("%s %d\n", "hello", 207)
	LOG_ERROR("%s %d\n", "hello", 207)
	LOG_FATAL("%s %d\n", "hello", 207)

    //LOG_INFO("LOG_INFO LOG %s\n", "我是中国人， 你TMD是谁？");
    //
    //LOG_WARN("LOG_WARN LOG\n");
    //LOG_ERROR("LOG_ERROR LOG\n");
    //LOG_FATAL("LOG_FATAL LOG\n");

    //char szBuf[2048*10 + 500];
    //memset(szBuf, 0, 2048*10 + 500);
    //for (int i=0; i<2048*10 + 500 - 1; i++)
    //{
    //    szBuf[i] = 'b';
    //}
    //szBuf[2048*10 + 500 - 2] = 'z';
    //LOG_INFO("%s", szBuf);
    //int i=0;
    //i++;
}

