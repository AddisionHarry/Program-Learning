/**
 * @file FloatOutput.c
 * @brief 读取一个浮点数，首先以小数点计数法打印，然后以指数计数法打印，用下面的格式输出
 *  （系统不同，指数计数法显示的位数可能不同）
 * a. The input is 21.3 or 2.1e+001.
 * b. The input is +21.290 or 2.129E+001.
 * @author lh
 * @date 2022-01-28
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    double a;

    printf("Please enter a number:\n");
    while(!scanf("%lf", &a))
        continue;
    printf("a. The input is %2.1f or %2.1e.\n", a, a);
    printf("c. The input is %+2.3f or %2.3e or %2.3a.\n", a, a, a);
    printf("b. The input is %+2.3f or %2.3E.\n", a, a);

    return 0;
}
