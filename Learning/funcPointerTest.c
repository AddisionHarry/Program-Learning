#include <stdio.h>
#include "funcPointerTest.h"

pCallback callback = NULL;

// void test(void)
// {
//     printf("this is a test.\n");
// }

void Register_Callback(pCallback callback_reg)
{
    printf("Registering callback!\n");
    if (callback_reg)
        callback = callback_reg;
    callback((void *)1);
}

// int main(void)
// {
//     callback = (pCallback)test;
//     if (callback)
//         callback((void *)1);
//     while (1)
//         continue;
//     return 0;
// }
