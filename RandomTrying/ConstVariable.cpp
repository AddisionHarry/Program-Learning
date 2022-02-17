#include <iostream>
using namespace std;

int main()
{
    const volatile int a = 1;
    int *b = (int *)&a;
    *b = 2;

    cout << "a = " << a << endl;
    cout << "*b = " << *b << endl;
    cout << "&a = " << &a << endl;
    cout << "&a = " << b << endl;

    return 0;
}
