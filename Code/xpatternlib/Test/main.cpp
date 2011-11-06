#include "Singleton.h"
#include "Prototype.h"
#include <stdio.h>

USE_XPATTERN_NAMESPACE;

class A : public Singleton<A>
{
    DECL_SINGLETON(A)
private:
    A()
    {
        printf("a");
    }
};

class B : public Prototype<B>
{
public:
    B()
    {

    }
    B(const B&b)
    {
        printf("b");
    }
};

int main(int argc, char** argv)
{

    A* p= A::GetInstPtr();
    B b;
    b.Clone();
    return 0;
}