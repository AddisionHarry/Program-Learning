#include <stdio.h>

int romanToInt(char *s)
{
    int index = 0, result = 0;
    while (1)
    {
        switch (s[index])
        {
        case 'I':
            if (s[index + 1] == 'V')
            {
                result += 4;
                ++index;
            }
            else if (s[index + 1] == 'X')
            {
                result += 9;
                ++index;
            }
            else
                result += 1;
            break;
        case 'V':
            result += 5;
            break;
        case 'X':
            if (s[index + 1] == 'L')
            {
                result += 40;
                ++index;
            }
            else if (s[index + 1] == 'C')
            {
                result += 90;
                ++index;
            }
            else
                result += 10;
            break;
        case 'L':
            result += 50;
            break;
        case 'C':
            if (s[index + 1] == 'D')
            {
                result += 400;
                ++index;
            }
            else if (s[index + 1] == 'M')
            {
                result += 900;
                ++index;
            }
            else
                result += 100;
            break;
        case 'D':
            result += 500;
            break;
        case 'M':
            result += 1000;
            break;
        case '\0':
            goto RETURN;
        }
        ++index;
    }
RETURN:
    return result;
}

int main(int argc, char *argv[])
{
    printf("%d", romanToInt("MCMXCIV"));
    getchar();
    return 0;
}
