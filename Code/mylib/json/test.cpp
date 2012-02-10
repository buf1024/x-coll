// Copyright 1985-2012 Luo Guochun, http://imlgc.com
#include "json.h"
#include <iostream>
#include "test.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif

using namespace std;
using namespace json;

TEST(Json, ConstructJson)
{
    
    Json json;
    JsonValue jv = true;
    json["a"] = jv;
    jv = json;    
    json["b"]=jv;
    json["b"]["ab"] = jv;
    jv = json;
    json.Set("c", jv);
    jv = (char*)0;
    json.Set("d", jv);
    jv = json;
    json.Set("0", jv);
    JsonArray sArr;
    sArr[0] = (char*)0;
    sArr[1] = true;
    sArr[2] = "abcdefg";
    sArr[3] = true;
    sArr[4] = json;
    jv = sArr;
    json.Set("e", jv);
    
    json.Save("testdata/constructjson_dump.json");
}
TEST(Json, ParseJson)
{
    std::vector<std::string> pass;
    for (int i=0; i<5; i++)
    {
        std::string file = "testdata/pass";
        char szBuf[9] = {0};
        file += _itoa(i + 1, szBuf, 10);
        file += ".json";
        pass.push_back(file);
    }
    
    for(int i=0; i < (int)pass.size(); i++)
    {
        Json* pJV = 0;
        int nRet = Json::Load(pJV, pass[i].c_str());
        ASSERT_EQ(0, nRet);
        ASSERT_TRUE(pJV != 0);
        
        std::string strFile = pass[i];
        strFile += "_dump.json";
        nRet = pJV->Save(strFile.c_str());
        ASSERT_EQ(0, nRet);
    }
    pass.clear();
    for (int i=0; i<33; i++)
    {
        std::string file = "testdata/fail";
        char szBuf[9] = {0};
        file += _itoa(i + 1, szBuf, 10);
        file += ".json";
        pass.push_back(file);
    }
    for(int i=0; i < (int)pass.size(); i++)
    {
        Json* pJV = 0;
        int nRet = Json::Load(pJV, pass[i].c_str());
        ASSERT_FALSE(0 == nRet);
        ASSERT_TRUE(pJV == 0);
    }

}

int main(int argc, char** argv)
{
    INIT_TEST(argc, argv);
    RUN_ALL_TEST();
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
