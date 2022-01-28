/**
 * @file Character_ASCII_Converse.c
 * @brief 读取输入，读到#字符为止。程序要打印每个输入的字符以及对应的ASCII码（十进制），
 *          每行打印8个“字符-ASCII码”组合。
 * @author lh
 * @date 2022-01-28
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char ch;
    int linecount = 0;

    printf("Please enter a number of characters(end with '#), the program will");
    printf("show them in \"character-ASCII\" form.\n");

    while ((ch = getchar()) != '#')
    {
        if (ch == '\n')
            printf("\\n%4d \t", ch);
        else if(ch == '\t')
            printf("\\t%4d \t", ch);
        else
            printf("%c%5d \t", ch, ch);

        if (++linecount == 8)
        {
            printf("\n");
            linecount = 0;
        }
    }

    printf("\nProgram Done!\n");

    return 0;
}
