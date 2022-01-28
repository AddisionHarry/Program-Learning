/**
 * @file InputRecognize.c
 * @brief 读取输入，读到#字符时停止，报告ei出现的次数
 * @author lh
 * @date 2022-01-28
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char current, last = 'a';
    int times = 0;

    printf("Please enter a number of words and end with '#':\n");

    while ((current = getchar()) != '#')
    {
        if (current == 'i' && last == 'e')
            ++times;
        last = current;
    }

    printf("There %s %d of \"ei\" in the text.\n", (times == 1) ? "was" : "were", times);

    return 0;
}
