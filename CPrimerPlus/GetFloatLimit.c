/**
 * @file GetFloatLimit.c
 * @brief 将一个double类型的变量设置为1.0/3.0，一个float类型的变量设置为1.0/3.0.分别计算两个表达式
 *  各三次：一次显示小数点后面的6位数字；一次显示小数点后面的12位数字；一次显示小数点后面的16位数字。
 *  程序中要包含float.h头文件，并显示FLT_DIG和DBL_DIG的值。1.0/3.0的值和这些值一致吗？
 * @author lh
 * @date 2022-01-28
 */

#include <stdio.h>
#include <float.h>

int main(int argc, char *argv[])
{
    float floatnumber = 1.0/3.0;
    double doublenumber = 1.0/3.0;

    printf("float one third(6) is %.6f\n", floatnumber);
    printf("float one third(12) is %.12f\n", floatnumber);
    printf("float one third(16) is %.16f\n", floatnumber);
    printf("double one third(6) is %.6f\n", doublenumber);
    printf("double one third(12) is %.12f\n", doublenumber);
    printf("double one third(16) is %.16f\n", doublenumber);
    printf("FLT_DIG in float.h is %d\n", FLT_DIG);
    printf("DBL_DIG in float.h is %d\n", DBL_DIG);

    return 0;
}
