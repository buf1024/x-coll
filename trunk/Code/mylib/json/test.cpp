#include "json.h"
#include <iostream>

using namespace std;
using namespace json;

void testGetErrMsg()
{
    cout << getErrMsg(E_SUCCESS) << endl;
    cout << getErrMsg(E_OUTOF_INDEX) << endl;
}

void testJson()
{
   // Json json;
   // JsonValue jv = true;
   // json["a"] = jv;
   // jv = json;    
   // json["b"]=jv;
   // json["b"]["ab"] = jv;
   // jv = json;
   // json.set("c", jv);
   // jv = (char*)0;
   // json.set("d", jv);
   // jv = json;
   // json.set("0", jv);
   // JsonArray sArr(5);
   // sArr[0] = (char*)0;
   // sArr[1] = true;
   // sArr[2] = "abcdefg";
   // sArr[3] = true;
   // sArr[4] = json;
   // jv = sArr;
   // json.set("e", jv);
   // std::string str;
   // json.dumpFormat(str);
   //cout << str << endl;
   // 
   // /* 
   // {
   //     "a" : true,
   //     "b" : {
   //         "a" : true
   //     }
   // }
   // 
   // 
   // JsonArray ja;
   // ja[0] = 100;
   // ja[1] = 200;
   // ja[2] = 300;
   // jv = ja;
   // json["c"] = jv;*/
   //json.save("e:\\a.json");
   //json.load("e:\\IniConfig.h");

    Json json;
    json.load("e:\\a.json");
    json.save("e:\\b.json");
}

int main(int argc, char** argv)
{
    testGetErrMsg();
    testJson();
    return 0;
}
