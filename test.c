#include <stdio.h>

int mySqrt(int x)
{
    if (0 == x)
        return 0;
    if (x < 4)
        return 1;
    if (x < 9)
        return 2;
    if (x < 16)
        return 3;
    if (x < 25)
        return 4;
    if (x < 36)
        return 5;

    int x0 = x / 6, last = 0;
    while (!((x0 - x / x0 <= 0) && (x0 + 1 - x / (x0 + 1) > 0)))
    {
        x0 = (int)(x0 * 0.5f + x * 0.5f / x0);
        if (last == x0)
            break;
        else
            last = x0;
    }
    while (x0 - x / x0 > 0)
        x0 -= 1;
    return x0;
}

int main(int argc, char *argv[])
{
    printf("%d\n", mySqrt(2147395599));
    getchar();
    return 0;
}
