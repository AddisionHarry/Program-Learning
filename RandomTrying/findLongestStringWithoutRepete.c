/**
 * @file findLongestStringWithoutRepete.c
 * @brief 来自 LeetCode 第三题
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 * 输入: s = "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 * 输入: s = "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 *
 * 0 <= s.length <= 5 * 104
 * s 由英文字母、数字、符号和空格组成
 * @author fwlh
 * @version 1.0
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t Characters[256 / 32]; // 用于按位存储 ASCII 码是否存在

/**
 * @brief 用于判断当前子串是否存在某元素, 若没有则写入该元素
 * @author fwlh
 * @param  s                待判断的元素
 * @return int              返回值为真代表已经存在过该元素
 */
int WriteHaveChar(int s)
{
    int i = 0; // 用于记录当前元素该写入到数组的哪个元素中

    // 判断当前元素是数组的哪个元素的第几位
    while (s >= 32)
    {
        ++i;
        s -= 32;
    }
    while (s < 0)
        s += 32;
    // 判断当前位是否已经有元素
    if (Characters[i] & ((uint32_t)1 << s))
        return 1;
    // 如果没有就写入
    Characters[i] |= ((uint32_t)1 << s);
    return 0;
}

/**
 * @brief 用于清除某个元素
 * @author fwlh
 * @param  s                待清除的元素
 */
void ClearChar(int s)
{
    int i = 0;
    while (s >= 32)
    {
        ++i;
        s -= 32;
    }
    while (s < 0)
        s += 32;
    Characters[i] &= ~((uint32_t)1 << s);
}

/**
 * @brief 删除子串中前面的几个元素直至新的元素被接纳
 * @author fwlh
 * @param  s                待处理的子串
 * @param  len              子串长度
 * @param  NewData          等待被吸收的新元素
 * @return int              新子串长度(含新的元素)
 */
int DeleteUntilNewAccepted(char *s, int len, int NewData)
{
    int pos = 0; // 当前正在尝试删除子串中的第几个元素
    // 只有新元素不存在时才退出
    while ((pos < len) && (WriteHaveChar(NewData)))
    {
        // 删除开头的第一个元素
        ClearChar(s[pos]);
        ++pos;
    }
    WriteHaveChar(NewData);
    return (len + 1 - pos);
}

/**
 * @brief 用于获取数组的最长不重复子串的长度
 * @author fwlh
 * @param  s                待分析的数组
 * @return int              最长不重复子串的长度
 */
int lengthOfLongestSubstring(char *s)
{
    int position = 0;  // 当前读到数组的哪个位置了
    int len = 0;       // 现在正在读的这个子串的当前长度
    int maxLenNow = 0; // 当前读到的最长子串

    // 力扣需要自己手动初始化全局变量
    memset(Characters, 0, sizeof(Characters));

    // 判断是不是到了数组尾
    while (s[position] != '\0')
    {
        // 判断现在的这个元素在子串中是不是存在
        if (WriteHaveChar(s[position]))
        {
            // 说明现在这个子串已经结束了, 先判断是不是产生了新的最长子串
            if (maxLenNow < len)
                maxLenNow = len;
            // 从当前子串的开头挨个删除元素直至当前所在的新元素可以被子串容纳
            len = DeleteUntilNewAccepted(s + position - len, len, s[position]);
        }
        // 子串中没有该元素, 那就把元素添加进去, 然后增长子串长度便可以判断下一个元素
        else
            ++len;
        ++position;
    }
    // 返回两者中较大的一项
    return ((maxLenNow > len) ? maxLenNow : len);
}

int main(int argc, char *argv[])
{
    printf("%d\n", lengthOfLongestSubstring("aab"));
    getchar();
    return 0;
}
