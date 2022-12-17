/**
 * @file GetTheNumberofOddNumbers.c
 * @brief 来自 Leetcode 第 1523 题
 * 在区间范围内统计奇数数目
 *
 * 给你两个非负整数 low 和 high 。请你返回 low 和 high 之间（包括二者）奇数的数目。
 *
 * 示例 1：
 * 输入：low = 3, high = 7
 * 输出：3
 * 解释：3 到 7 之间奇数数字为 [3,5,7] 。
 *
 * 示例 2：
 * 输入：low = 8, high = 10
 * 输出：1
 * 解释：8 到 10 之间奇数数字为 [9] 。
 *
 * 提示：
 * 0 <= low <= high <= 10^9
 * @author fwlh
 * @version 1.0
 * @date 2022-12-17
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>
#include <stdlib.h>

// 呆瓜, 最简单的是 return ((high + 1) / 2 - low / 2);
int countOdds(int low, int high)
{
    // 如果开始的数是奇数
    if (low % 2)
        return (high - low) / 2 + 1;
    else if (low == high)
        return 0;
    else
        return (high - low - 1) / 2 + 1;
}

int main(int argc, char *argv[])
{
    int low, high;
    if (argc == 3)
    {
        low = atol(argv[1]);
        high = atol(argv[2]);
    }
    else
    {
        printf("Error!\n");
        return -1;
    }
    printf("The result is %d.\n", countOdds(low, high));
    return 0;
}
