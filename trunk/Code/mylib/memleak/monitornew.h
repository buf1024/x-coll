/*
 * File       : monitornew.h
 * Description: 
 * Version    : 2012-03-28 Created
 * Author     : buf1024@gmail.com
 */
 
#ifndef __MONITOR_NEW_H__
#define __MONITOR_NEW_H__

#ifdef _DEBUG

#include <map>
#include <string>

typedef void (*MemUsageReportFunType)(std::map<std::string, unsigned long>&);

class __THE_MONITOR_WATCH_DOG__
{
public:
    typedef std::map<std::string, unsigned long> TheMap;
    typedef std::map<std::string, unsigned long>::iterator TheMapIterator;
    
public:
    __THE_MONITOR_WATCH_DOG__()
    {
        theFunc = NULL;
    }
    ~__THE_MONITOR_WATCH_DOG__()
    {
        if(theFunc != NULL){
            (*theFunc)(theMap);
        }
    }
    
public:
    static __THE_MONITOR_WATCH_DOG__& GetInstance()
    {
        static __THE_MONITOR_WATCH_DOG__ theInst;
        return theInst;
    }
    TheMapIterator begin()
    {
        theMap.begin();
    }
    TheMapIterator end()
    {
        theMap.end();
    }
    unsigned long GetInstanceCount(std::string name)
    {
        if(theMap.find(name) == theMap.end()){
            return 0L;
        }
        return theMap[name];
    }
    void SetReportHandler(MemUsageReportFunType func)
    {
        theFunc = func;
    }
    
public:
    TheMap theMap;
    MemUsageReportFunType theFunc;
};

#define MNT_SET_REPORTER(TheFunc) \
    __THE_MONITOR_WATCH_DOG__::GetInstance().SetReportHandler(TheFunc)
    
#define MNT_FOREACH(Key, Value) \
    if(__THE_MONITOR_WATCH_DOG__::GetInstance().theMap.size() > 0) \
        for(__THE_MONITOR_WATCH_DOG__::TheMapIterator it = \
            __THE_MONITOR_WATCH_DOG__::GetInstance().begin();\
            it != __THE_MONITOR_WATCH_DOG__::GetInstance().end() && \
            (Key=it->first) != "" && (Value=it->second) >= 0 ; \
            ++it) \
    
#define MNT_COUNT(Key) \
    __THE_MONITOR_WATCH_DOG__::GetInstance().GetInstanceCount(Key)
    
    

#define DECL_MNT(TheClass) \
class __THE_MONITOR_##TheClass##SUPER_CLASS__ \
{ \
public: \
    __THE_MONITOR_##TheClass##SUPER_CLASS__() \
    { \
    } \
    ~__THE_MONITOR_##TheClass##SUPER_CLASS__() \
    { \
    } \
    static void* operator new(size_t size) throw(std::bad_alloc) \
    { \
        if(__THE_MONITOR_WATCH_DOG__::GetInstance().theMap.find(#TheClass) == \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap.end()){ \
                __THE_MONITOR_WATCH_DOG__::GetInstance().theMap.insert( \
                   std::make_pair<std::string, unsigned long>(#TheClass, 0L)); \
        } \
        __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] = \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] + 1; \
        return ::operator new(size);\
    } \
    static void operator delete(void* pointer)\
    { \
        __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] = \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] - 1; \
        return ::operator delete(pointer);\
    } \
}; \
class TheClass : public __THE_MONITOR_##TheClass##SUPER_CLASS__ \

#define DECL_INHERIT_MNT(TheClass, TheSuperClass) \
class __THE_MONITOR_##TheClass##TheSuperClass##SUPER_CLASS__ \
    : public TheSuperClass\
{ \
public: \
    __THE_MONITOR_##TheClass##TheSuperClass##SUPER_CLASS__() \
    { \
    } \
    ~__THE_MONITOR_##TheClass##TheSuperClass##SUPER_CLASS__() \
    { \
    } \
    static void* operator new(size_t size) \
    { \
        if(__THE_MONITOR_WATCH_DOG__::GetInstance().theMap.find(#TheClass) == \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap.end()){ \
                __THE_MONITOR_WATCH_DOG__::GetInstance().theMap.insert( \
                   std::make_pair<std::string, unsigned long>(#TheClass, 0L)); \
        } \
        __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] = \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] + 1; \
        return ::operator new(size);\
    } \
    static void operator delete(void* pointer)\
    { \
        __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] = \
            __THE_MONITOR_WATCH_DOG__::GetInstance().theMap[#TheClass] - 1; \
        return ::operator delete(pointer);\
    } \
}; \
class TheClass : public __THE_MONITOR_##TheClass##TheSuperClass##SUPER_CLASS__ \

#else

#define MNT_SET_REPORTER(TheFunc)
#define MNT_FOREACH(Key, Value) 
#define MNT_COUNT(Key) (0L)
#define DECL_MNT(TheClass) class TheClass
#define DECL_INHERIT_MNT(TheClass, TheSuperClass) \
    class TheClass : public TheSuperClass

#endif /* _DEBUG */

#endif /* __MONITOR_NEW_H__ */

/*example

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

//result:
key: A value: 3
key: XX value: 1
A new unrelease count of A: 3
key: A value: 2
key: XX value: 0

*/


