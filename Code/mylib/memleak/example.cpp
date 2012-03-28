#include "monitornew.h"
#include <iostream>

using namespace std;

void Reporter(std::map<std::string, unsigned long>& theMap)
{
    cout << "Reporter:" << endl;
    for(std::map<std::string, unsigned long>::iterator it = theMap.begin();
        it != theMap.end();
        ++it){
        cout << "key: " << it->first << " value: " << it->second << endl;
    }
}

DECL_MNT(A)
{
public:
    A()
    {
    }
};

DECL_INHERIT_MNT(XX, A)
{
public:
    XX(const char*)
    {
    }
};

int main()
{
    MNT_SET_REPORTER(Reporter);
    
    A* a = new A;
    A* b = new A;
    A* c = new A;
    
    XX* x = new XX("abc");
    std::string k;
    unsigned long v;
    MNT_FOREACH(k, v)
    {
        cout << "key: " << k << " value: " << v << endl; 
    }
    cout << "A new unrelease count of A: " << MNT_COUNT("A") << endl;
    delete a;
    delete x;
    MNT_FOREACH(k, v)
    {
        cout << "key: " << k << " value: " << v << endl; 
    }
}
