/**
 * @file CalculatorMenu.c
 * @brief 显示一个提供加法、减法、乘法、除法的菜单。获得用户选择的菜单项后，程序提示用户输入两个数字，
 *  然后执行用户刚才选择的操作。该程序只接受菜单提供的选项。程序使用float类型的变量存储用户输入的数字，
 *  如果用户输入失败，则允许再次输入。在进行除法运算时，如果用户输入0作为第二个数（除数），程序应提示
 *  用户再输入一个新值。该程序的一个运行提示如下。
 *  Enter the operation of your chioce:
 *  a. add          s. subtract
 *  m. multiply     d. divide
 *  q. quit
 *  a
 *  Enter the first number: 22.4
 *  Enter the second number: one
 *  one is not a number.
 *  Please enter a number, such as 2.5, -1, 78E8, or 3: 1
 *  22.4 + 1 = 23.4
 *  Enter the operation of your chioce:
 *  a. add          s. subtract
 *  m. multiply     d. divide
 *  q. quit
 *  d
 *  Enter the first number: 18.4
 *  Enter the second number: 0
 *  Enter a number other than 0: 0.2
 *  18.4 / 0.2 = 92
 *  Enter the operation of your chioce:
 *  a. add          s. subtract
 *  m. multiply     d. divide
 *  q. quit
 *  q
 *  Bye!
 * 
 * @author lh
 * @date 2022-01-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef enum
{
    ErrorOperation = -1,
    AddOperation = 0,
    SubstractOperation,
    MultiplyOperation,
    DivideOperation,
    EndOperation
} Calculator_Operation_Enum;

struct Calculator_Ctrl
{
    Calculator_Operation_Enum Calculator_Operation;
    float FirstNumber;
    float SecondNumber;
    float Result;
    int (*AbnormalCheck)(struct Calculator_Ctrl *this);
    float (*Calculate[0])(float x, float y);
};
typedef struct Calculator_Ctrl Calculator_Ctrl_Structure;

float Add(float a, float b);
float Substract(float a, float b);
float Multiply(float a, float b);
float Divide(float a, float b);
int AbnormalCheck(Calculator_Ctrl_Structure *this);
Calculator_Ctrl_Structure *Calculator_Init(void);
void Calculator_DeInit(Calculator_Ctrl_Structure *Calculator);
void Calculator_Menu_Show(void);
Calculator_Operation_Enum Calculator_ReadOperation(Calculator_Ctrl_Structure *Calculator);
void Calculator_ReadFloat(float *f);
void Calculator_ReadNumber(Calculator_Ctrl_Structure *Calculator);
void Calculator_PrintResult(Calculator_Ctrl_Structure *Calculator);
void Calculator_Work(Calculator_Ctrl_Structure *Calculator);

int main(int argc, char *argv[])
{
    Calculator_Work(Calculator_Init());
    return 0;
}

float Add(float a, float b)
{
    return a + b;
}
float Substract(float a, float b)
{
    return a - b;
}
float Multiply(float a, float b)
{
    return a * b;
}
float Divide(float a, float b)
{
    return a / b;
}
int AbnormalCheck(Calculator_Ctrl_Structure *this)
{
    if (this->Calculator_Operation == DivideOperation && fabs(this->SecondNumber) < 0.06)
    {
        printf("Enter a number other than 0: ");
        return 1;
    }
    return 0;
}

/**
 * @brief 计算器初始化
 * @author lh
 * @return Calculator_Ctrl_Structure* 计算器控制结构体指针
 */
Calculator_Ctrl_Structure *Calculator_Init(void)
{
    Calculator_Ctrl_Structure *Calculator = (Calculator_Ctrl_Structure *)malloc(
        sizeof(Calculator_Ctrl_Structure) + 4 * sizeof(float (*)(float, float)));
    while (Calculator == NULL)
        continue;

    Calculator->AbnormalCheck = AbnormalCheck;

    Calculator->Calculate[0] = Add;
    Calculator->Calculate[1] = Substract;
    Calculator->Calculate[2] = Multiply;
    Calculator->Calculate[3] = Divide;

    Calculator->Calculator_Operation = ErrorOperation;
    Calculator->FirstNumber = Calculator->SecondNumber = Calculator->Result = 0;

    return Calculator;
}

/**
 * @brief 计算器去初始化(销毁相关的指针)
 * @author lh
 * @param  Calculator       计算器控制结构体指针
 */
void Calculator_DeInit(Calculator_Ctrl_Structure *Calculator)
{
    printf("Bye!\n");
    free(Calculator);
    Calculator = NULL;
}

/**
 * @brief 计算器主要菜单面板显示
 * @author lh
 */
void Calculator_Menu_Show(void)
{
    printf("Enter the operation of your chioce:\na. add\t\ts. subtract\nm. multiply"
           "\td. divide\nq. quit\n");
}

/**
 * @brief 读取用户选择的计算操作
 * @author lh
 * @param  Calculator                   计算器控制结构体
 * @return Calculator_Operation_Enum    读取到的操作
 */
Calculator_Operation_Enum Calculator_ReadOperation(Calculator_Ctrl_Structure *Calculator)
{
    int ch = getchar();
    char errorch[40];

    switch (tolower(ch))
    {
    case 'a':
        Calculator->Calculator_Operation = AddOperation;
        break;
    case 's':
        Calculator->Calculator_Operation = SubstractOperation;
        break;
    case 'm':
        Calculator->Calculator_Operation = MultiplyOperation;
        break;
    case 'd':
        Calculator->Calculator_Operation = DivideOperation;
        break;
    case 'q':
        Calculator->Calculator_Operation = EndOperation;
        break;
    default:
        Calculator->Calculator_Operation = ErrorOperation;
        putchar(ch);
        scanf("%s", &errorch);
        printf("%s is not a right operation, please enter an operation.\n", errorch);
        break;
    }

    while ((ch = getchar()) != '\n')
        continue;

    return Calculator->Calculator_Operation;
}

/**
 * @brief 从输入流读取浮点数
 * @author lh
 * @param  f                浮点数存放的位置指针
 */
void Calculator_ReadFloat(float *f)
{
    int ch;

    while (!scanf("%f", f))
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" is not a number.\nPlease enter a number, such as 2.5, -1, 78E8, or 3:");
    }
    while (getchar() != '\n')
        continue;
}

/**
 * @brief 读取用户输入的两个浮点操作数
 * @author lh
 * @param  Calculator       计算器控制结构体
 */
void Calculator_ReadNumber(Calculator_Ctrl_Structure *Calculator)
{
    printf("Enter the first number: ");
    Calculator_ReadFloat(&(Calculator->FirstNumber));
    printf("Enter the second number: ");
    Calculator_ReadFloat(&(Calculator->SecondNumber));
}

/**
 * @brief 打印计算器输出结果
 * @author lh
 * @param  Calculator       计算器控制结构体
 */
void Calculator_PrintResult(Calculator_Ctrl_Structure *Calculator)
{
    switch (Calculator->Calculator_Operation)
    {
    case AddOperation:
        printf("%.2f + %.2f = %.2f\n", Calculator->FirstNumber,
               Calculator->SecondNumber, Calculator->Result);
        break;
    case SubstractOperation:
        printf("%.2f - %.2f = %.2f\n", Calculator->FirstNumber,
               Calculator->SecondNumber, Calculator->Result);
        break;
    case MultiplyOperation:
        printf("%.2f * %.2f = %.2f\n", Calculator->FirstNumber,
               Calculator->SecondNumber, Calculator->Result);
        break;
    case DivideOperation:
        printf("%.2f / %.2f = %.2f\n", Calculator->FirstNumber,
               Calculator->SecondNumber, Calculator->Result);
        break;
    default:
        break;
    }
}

/**
 * @brief 用于计算器的实际功能实现
 * @author lh
 * @param  Calculator       计算器控制结构体
 */
void Calculator_Work(Calculator_Ctrl_Structure *Calculator)
{
    Calculator_Menu_Show();
    while (Calculator_ReadOperation(Calculator) != EndOperation)
    {
        Calculator_ReadNumber(Calculator);
        while ((Calculator->AbnormalCheck(Calculator)))
            Calculator_ReadFloat(&(Calculator->SecondNumber));
        Calculator->Result = Calculator->Calculate[Calculator->Calculator_Operation](
            Calculator->FirstNumber, Calculator->SecondNumber);
        Calculator_PrintResult(Calculator);
        Calculator_Menu_Show();
    }
    Calculator_DeInit(Calculator);
}
