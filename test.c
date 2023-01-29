#include <stdio.h>

int main(void)
{
    char Uppercase;
    int index;

    printf("Uppercase: ");
    scanf("%c", &Uppercase);
    if (Uppercase != 'y' && Uppercase != 'n')
    {
        printf("You need to enter 'y' or 'n'\n");
        printf("Exiting the program with error code 1\n");
        return 1;
    }
    printf("Index: ");
    scanf("%d", &index);
    if (index < 1 || index > 26)
    {
        printf("You need to enter a number between 1 and 26 inclusive\n");
        printf("Exiting the program with error code 2\n");
        return 2;
    }

    if (Uppercase == 'y')
        printf("The letter is %c\n", 'A' + index - 1);

    if (Uppercase == 'n')
        printf("The letter is %c\n", 'a' + index - 1);

    return 0;
}
