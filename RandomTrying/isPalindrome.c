/**
 * @file isPalindrome.c
 * @brief 来自 LeetCode 第九题
 * 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 * 例如，121 是回文，而 123 不是。
 *
 * 输入：x = -121
 * 输出：false
 * 解释：从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 *
 * -2^31 <= x <= 2^31 - 1
 *
 * @author fwlh
 * @version 1.0
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief 用于计算指数, 但是只限于整数域
 * @author fwlh
 * @param  base             底数
 * @param  expen            指数
 * @return int              计算结果
 */
int MyPow(int base, int expen)
{
    if (!expen)
        return 1;
    int result = base;
    while (--expen)
        result *= base;
    return result;
}

/**
 * @brief 计算整数 x 的相反数
 * @author fwlh
 * @param  x                待操作的数字
 * @return int              预想的回文数
 */
int reverse(int x)
{
    long reversex = 0;
    while (x)
    {
        reversex = reversex * 10 + x % 10;
        x /= 10;
    }
    return (int)reversex;
}

bool isPalindrome(int x){
    if (x < 0)
        return false;
    return (x == reverse(x));
}

int main(int argc, char *argv[])
{
    printf("%d\n", isPalindrome(1234567899));
    getchar();
    return 0;
}
