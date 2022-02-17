#include <stdio.h>

int main()
{
    const volatile int a = 1;
    int *b = (int *)&a;
    *b = 2;

    printf("a = %d\n", a);
    printf("*b = %d\n", *b);
    printf("&a = 0x%0x\n", &a);
    printf("&a = 0x%0x\n", b);

    return 0;
}
