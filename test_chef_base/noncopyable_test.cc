#include "_noncopyable.h"
#include <stdio.h>

class A : public chef::noncopyable
{

};

class B : public chef::copyable
{

};

int main()
{
    printf(">noncopyable.\n");
    A a1;
    /// can't compile
//    A a2(a1);
//    A a3;
//    a3 = a1;

    B b1;
    B b2(b1);
    B b3;
    b3 = b1;

    printf("<noncopyable.\n");
    return 0;
}

