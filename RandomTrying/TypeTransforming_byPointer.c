/**
 * @file TypeTransforming_byPointer.c
 * @brief 本文件尝试通过指针操作来实现大类型拆分成小类型
 * @author lh
 * @date 2022-02-07
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char type[4], *p;
    float float_number = 1.2f;
    int int_number = 12;

    printf("float: %f\n", float_number);
    *(float *)(&(type[0])) = *(float *)(&float_number);
    p = (char *)&float_number;

    for (int fori = 0; fori < 4; ++fori)
        printf("float:\n%d\t%d\n", fori, *(p + fori));
    for (int fori = 0; fori < 4; ++fori)
        printf("%d\t%d\n", fori, type[fori]);

    printf("int: %d\n", int_number);
    *(int *)(&(type[0])) = *(int *)(&int_number);
    p = (char *)&int_number;

    for (int fori = 0; fori < 4; ++fori)
        printf("%d\t%d\n", fori, *(p + fori));
    for (int fori = 0; fori < 4; ++fori)
        printf("%d\t%d\n", fori, type[fori]);

    return 0;
}
