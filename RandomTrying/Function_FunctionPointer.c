/**
 * @file Function_FunctionPointer.c
 * @brief 本文件用于学习函数与函数指针之间的模糊界限
 * @author lh
 * @version 1.0
 * @date 2022-03-18
 */
#include <stdio.h>

int Max(int x, int y)
{
    return (x > y) ? x : y;
}

// 将函数指针定义成类型
typedef int (*pfun)(int, int);

// func这个函数参数是(int a, int b, int(*FUN)(int, int))
// 返回值是个指针，这个指针是int (*) (int, int)型函数指针
// int(*func(int a, int b, int(*FUN)(int, int))) (int, int)
pfun func(int a, int b, pfun FUN)
{
    printf("max value=%d\n", FUN(a, b));
    return FUN;
}

int main(int argc, char const *argv[])
{
    int (*p1)(int, int) = Max;
    int (*p2)(int, int) = &Max;
    printf("Max(2, 3) = %d\n(*Max)(2, 3) = %d\n"
           "p1(2, 3) = %d\n(*p1)(2, 3) = %d\n"
           "p2(2, 3) = %d\n(*p2)(2, 3) = %d\n",
           Max(2, 3), (*Max)(2, 3), p1(2, 3), (*p1)(2, 3), p2(2, 3), (*p2)(2, 3));
    p1 = func(1, 2, p1);
    return 0;
}
