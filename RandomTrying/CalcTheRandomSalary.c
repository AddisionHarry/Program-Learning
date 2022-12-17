/**
 * @file CalcTheRandomSalary.c
 * @brief 来自 Leetcode 第 1491 题
 * 去掉最低工资和最高工资后的工资平均值
 *
 * 给你一个整数数组 salary ，数组里每个数都是 唯一 的，其中 salary[i] 是第 i 个员工的工资。
 * 请你返回去掉最低工资和最高工资以后，剩下员工工资的平均值。
 *
 * 示例 1：
 * 输入：salary = [4000,3000,1000,2000]
 * 输出：2500.00000
 * 解释：最低工资和最高工资分别是 1000 和 4000 。
 * 去掉最低工资和最高工资以后的平均工资是 (2000+3000)/2= 2500
 *
 * 示例 2：
 * 输入：salary = [1000,2000,3000]
 * 输出：2000.00000
 * 解释：最低工资和最高工资分别是 1000 和 3000 。
 * 去掉最低工资和最高工资以后的平均工资是 (2000)/1= 2000
 *
 * 示例 3：
 * 输入：salary = [6000,5000,4000,3000,2000,1000]
 * 输出：3500.00000
 *
 * 示例 4：
 * 输入：salary = [8000,9000,2000,3000,6000,1000]
 * 输出：4750.00000
 *
 * 提示：
 * 3 <= salary.length <= 100
 * 10^3 <= salary[i] <= 10^6
 * salary[i] 是唯一的。
 * 与真实值误差在 10^-5 以内的结果都将视为正确答案。
 * @author fwlh
 * @version 1.0
 * @date 2022-12-17
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>

// 不过这里还是做复杂了, 其实在求和的时候只需要无脑地全部求和就可以, 最终在计算平均值的时候把最大和最小值减掉
#define USE_PRINTF_DEBUG 0
double average(int *salary, int salarySize)
{
    int min = 0, max = 0;
    if (salary[0] < salary[1])
    {
        min = salary[0];
        max = salary[1];
    }
    else
    {
        min = salary[1];
        max = salary[0];
    }
    double sum = 0.0;
    for (int i = 2; i < salarySize; ++i)
    {
#if (USE_PRINTF_DEBUG == 1)
        printf("salary[%d] = %d\n", i, salary[i]);
        printf("max = %d\n", max);
        printf("min = %d\n", min);
#endif
        if (salary[i] < min)
        {
            // 在更新最小值之前要把上一次的最小值累加到最终输出上
            sum += min;
            min = salary[i];
        }
        else if (salary[i] > max)
        {
            sum += max;
            max = salary[i];
        }
        else
            sum += salary[i];
#if (USE_PRINTF_DEBUG == 1)
        printf("max = %d\n", max);
        printf("min = %d\n", min);
        printf("sum = %lf\n", sum);
        printf("***************************************\n");
#endif
    }
    return (sum / (salarySize - 2));
}

// #define CMD_ENTER_ARRAY
int main(int argc, char *argv[])
{
#ifdef CMD_ENTER_ARRAY
    int length = 0;
    while (length <= 0)
    {
        printf("Please enter the length of the salary array:\n");
        scanf("%d", &length);
    }
    int salary[length];
    for (int i = 0; i < length; ++i)
    {
        printf("Please enter the %d member of the salary array:\n", i);
        scanf("%d", &salary[i]);
    }
#else
    int salary[6] = {8000, 9000, 2000, 3000, 6000, 1000};
    int length = sizeof(salary) / sizeof(salary[0]);
#endif
    printf("The result is %lf.\n", average(salary, length));
    return 0;
}
