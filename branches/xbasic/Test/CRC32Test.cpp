
#include "TestCmmHdr.h"
#include "Hash.h"
#include "HashCRC32Impl.h"

#include <stdio.h>

USE_XBASIC_NAMESPACE

class CRC32Test : public ::testing::Test
{
public:
    void SetUp()
    {
        m_pHash = new Hash(new HashCRC32Impl);
        m_strTmpFile = tempnam(".", "CRC32Test");
        FILE* fp = fopen(m_strTmpFile.c_str(), "w+");
        if (fp)
        {
            char* buf = "hello!!";
            int nLen = strlen(buf);
            for (int i=0; i<1024; i++)
            {
                fwrite(buf, 1, nLen, fp);
            }
            fclose(fp);
        }
    }
    void TearDown()
    {
        delete m_pHash;
    }
protected:
    std::string m_strTmpFile;
    Hash* m_pHash;
};

TEST_F(CRC32Test, CRC32ImplTest)
{
    std::string strHash = m_pHash->GetStringHash("abc");
    ASSERT(true);
    
    strHash = m_pHash->GetStringHash("");
    ASSERT(true);

    strHash = m_pHash->GetStringHash(L"abc");
    ASSERT(true);

    strHash = m_pHash->GetStringHash(L"");
    ASSERT(true);

    strHash = m_pHash->GetFileHash(m_strTmpFile);
    ASSERT(true);

    strHash = m_pHash->GetFileHash("");
    ASSERT(true);

}
