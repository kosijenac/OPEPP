#include <iostream>
#include <string>

using namespace std;

struct A {
    int* br;
    A()
        : br(new int(5))
    {
    }
    ~A() { delete br; }
};

void f(const A a)
{
    cout << *(a.br) << endl;
}

int main()
{
    A a;
    f(a);
    return 0;
}