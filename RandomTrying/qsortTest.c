/**
 * @file qsortTest.c
 * @brief 本文件主要是用于测试一下 C 语言自带快速排序的一些行为
 * @author fwlh
 * @version 1.0
 * @date 2022-12-19
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[])
{
    int a[10] = {1, 6, 3, 4, 5, 2, 7, 8, 9, 8};
    printf("Before arrangement:\n");
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
        printf("a[%d] = %d\n", i, a[i]);

    // 可以证明, 该算法是可以正常应对完全相等的情况的
    qsort((void *)a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp);

    printf("\nAfter Arrangement:\n");
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
        printf("a[%d] = %d\n", i, a[i]);
    return 0;
}
