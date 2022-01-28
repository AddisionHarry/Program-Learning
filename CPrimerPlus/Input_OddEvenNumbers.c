/**
 * @file Input_OddEvenNumbers.c
 * @brief 读取整数，直到用户输入0。输入结束后，程序应报告用户输入的偶数（不包括0）个数、
 *          这些偶数的平均值、输入奇数的个数和这些奇数的平均值
 * @author lh
 * @date 2022-01-28
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int InputNumber, NumberofInput = 0, NumberofOdd = 0, SumofAll = 0, SumofOdd = 0;

    printf("Please enter a number of integers(end with 0):\n");

    while (scanf("%d", &InputNumber))
    {
        if (!InputNumber)
            break;
        ++NumberofInput;
        SumofAll += InputNumber;

        if (!(InputNumber % 2))
        {
            ++NumberofOdd;
            SumofOdd += InputNumber;
        }
    }

    printf("Inputed: %3d Odd  %s, which have an average of %g\n", NumberofOdd,
           (NumberofOdd == 1) ? "number" : "numbers", SumofOdd * 1.0 / NumberofOdd);
    printf("     and %3d Even %s, which have an average of %g.\n", NumberofOdd,
           (NumberofInput - NumberofOdd == 1) ? "number" : "numbers",
           (SumofAll - SumofOdd) * 1.0 / (NumberofInput - NumberofOdd));
    printf("Done!\n");

    return 0;
}
