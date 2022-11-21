#include <iostream>
#include "funcPointerTest.h"

using namespace std;

void test(void)
{
    cout << "this is a test." << endl;
}

int main(void)
{
    Register_Callback((pCallback)test);
    return 0;
}
