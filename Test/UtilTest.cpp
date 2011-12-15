#include "TestCmmHdr.h"
#include "Util.h"

USE_XBASIC_NAMESPACE


TEST(UtilTest, IsAppInstRuning)
{
    long bRunning = Util::IsAppInstRuning("xbasic");
}

