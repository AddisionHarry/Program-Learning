/**
 * @file CalcCharacters.c
 * @brief 读取输入，读到 # 字符停止，然后报告读取到的空格数、换行符数和所有其它字符的数量
 * @author lh
 * @date 2022-01-28
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    char ch;
    int NumberofSpace = 0, NumberofLinebreak = 0, NumberofOtherCharacters = 0;

    printf("Please enter a number of characters, end with '#' :\n");
    while ((ch = getchar()) != '#')
    {
        if (ch == '\n')
            ++NumberofLinebreak;
        else if (ch == ' ')
            ++NumberofSpace;
        else
            ++NumberofOtherCharacters;
    }
    printf("Totally get %d of %s, %d of %s and %d of %s.\n", 
        NumberofSpace, (NumberofSpace == 1)?"space":"spaces", 
        NumberofLinebreak, (NumberofLinebreak == 1)?"Line Break":"Line Breaks",
        NumberofOtherCharacters, (NumberofOtherCharacters == 1)?"Other Character":"Other Characters");

    return 0;
}
