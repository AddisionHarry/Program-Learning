/**
 * @file CountInputStream.c
 * @brief 在遇到EOF之前，作为字符流读取输入。该程序要报告输入中大写字母和小写字母的个数以及平均每个
 *  单词的字母个数，注意不要把标点符号和空格统计在内
 * @author lh
 * @date 2022-01-29
 */

#include <stdio.h>
#include <ctype.h>

typedef struct
{
    char LastChar;             // 上一次的字符, 用于判断是不是单词结束
    int CapitalLetterNumber;   // 大写字母的数量
    int LowerCaseLetterNumber; // 小写字母的数量
    long WordNumber;           // 单词数量
    long TotalCharacterNumber; // 总字符数
} Stream_Count_Structure;

void CountStreamChar(Stream_Count_Structure *Count_Struct, int NewChar);

int main(int argc, char *argv[])
{
    int ch;
    Stream_Count_Structure Count_Struct = {0, 0, 0, 0, 0};

    printf("Please enter some sentences.\n");
    // 至少在我这里是以 Ctrl+C 退出的
    while ((ch = getchar()) != EOF)
        CountStreamChar(&Count_Struct, ch);
    printf("\nTotally received: %d of capital %s, %d of lower case %s and %d %s, \neach"
           " word has %g letters in average.\n",
           Count_Struct.CapitalLetterNumber, (Count_Struct.CapitalLetterNumber == 1) ? "letter" : "letters",
           Count_Struct.LowerCaseLetterNumber, (Count_Struct.LowerCaseLetterNumber == 1) ? "letter" : "letters",
           Count_Struct.WordNumber, (Count_Struct.WordNumber == 1) ? "word" : "words",
           (Count_Struct.CapitalLetterNumber + Count_Struct.LowerCaseLetterNumber) * 1.0 / Count_Struct.WordNumber);

    return 0;
}

void CountStreamChar(Stream_Count_Structure *Count_Struct, int NewChar)
{
    ++Count_Struct->TotalCharacterNumber;
    // 对字母计数
    if (isalpha(NewChar))
    {
        // 记录大写字母数
        if (isupper(NewChar))
            ++Count_Struct->CapitalLetterNumber;
        else
            ++Count_Struct->LowerCaseLetterNumber;
    }
    // 判断单词结尾
    else if (isalpha(Count_Struct->LastChar) && isspace(NewChar))
        ++Count_Struct->WordNumber;
    Count_Struct->LastChar = NewChar;
}
