#include "Log.h"
#include "TestCmmHdr.h"


USE_XBASIC_NAMESPACE


INIT_STD_LOG("y.xml");

TEST(LoggerTest, LoggerTest)
{
    //Logger* pLogger = GET_LOGGER();

    LOG_DEBUG("LOG_DEBUG LOG\n");
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

