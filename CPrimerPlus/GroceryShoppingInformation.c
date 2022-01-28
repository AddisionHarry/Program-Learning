/**
 * @file GroceryShoppingInformation.c
 * @brief ABC邮购杂货店出售的洋蓟售价为2.05美元/磅（1磅=0.45359237千克），甜菜售价为1.15美元/磅，
 *  胡萝卜售价为1.09美元/磅。在添加运费之前，100美元订单有5%打折优惠。少于或等于5磅的订单收取6.5
 *  美元的运费和包装费，超过20磅的订单在14美元的基础上每续重一磅增加0.5美元。编写一个程序，在循环中
 *  用switch语句实现用户输入不同字母时有不同相应，即输入a的响应是输入洋蓟的磅数，输入b的相应是甜菜
 *  的磅数，c是胡萝卜的磅数，q是退出订购。程序要记录累计的重量。即，如果用户输入4磅的甜菜，然后再输入
 *  5磅的甜菜，程序应该报告9磅的甜菜。然后，该程序要计算货物总价、折扣（如果有的话）、运费和包装费。
 *  随后，程序应显示所有的购买信息，包括物品售价、订购的重量（单位是磅）、订购的蔬菜费用、订单的总费用
 *  折扣（如果有的话）、运费和包装费，以及费用总额
 * @author lh
 * @date 2022-01-28
 */
#include <stdio.h>
#include <math.h>

// 各商品的单价
#define PRICE_OF_ARTICHOKE 2.05
#define PRICE_OF_BEET 1.15
#define PRICE_OF_CARROT 1.09

// 优惠计算宏, 需要的是计算运费之前的价格
#define DISCOUNT(price) ((price > 100) ? 0.05 * price : 0)

typedef struct
{
    double Artichoke;
    double Beet;
    double Carrot;
} Product_Information_Structure;

typedef struct
{
    Product_Information_Structure UnitPrice;
    Product_Information_Structure Weight;
    Product_Information_Structure Price;
    double TotalOrderCost;
    double TotalWeight;
    double Discount;
    double ShippingHandling_Price;
    double TotalCost;
} Shopping_Information_Structure;

// 全局变量及函数声明
Shopping_Information_Structure Calculate_Information;
void Calculate_Init(Shopping_Information_Structure *InitStructure);
char Menu_Interface_Perform(void);
int Select_Information(Shopping_Information_Structure *InitStructure);
void Product_Information_Calculate(Shopping_Information_Structure *InitStructure);
void Print_Product_Information(Shopping_Information_Structure *InitStructure);

int main(int argc, char *argv[])
{
    Calculate_Init(&Calculate_Information);
    printf("Welcome to ABC Mail-order Grocery Store!\n");
    printf("Price List:\n%10s\t$%3.2f per pound\n%10s\t$%3.2f per pound\n%10s\t$%3.2f per pound\n",
        "Artichoke", PRICE_OF_ARTICHOKE, "Beet", PRICE_OF_BEET, "Carrot", PRICE_OF_CARROT);

    while (!Select_Information(&Calculate_Information))
        continue;
    printf("Purchase Done!\n\n");

    Product_Information_Calculate(&Calculate_Information);
    Print_Product_Information(&Calculate_Information);
    printf("Welcome back! Have a nice day! \n---------------by ABC Mail-order Grocery Store\n");
    getchar();
    getchar();

    return 0;
}

/**
 * @brief 用于相关计算结构体的初始化
 * @author lh
 * @param  InitStructure    需要初始化的结构体
 */
void Calculate_Init(Shopping_Information_Structure *InitStructure)
{
    InitStructure->Discount = 0;

    InitStructure->Price.Artichoke = 0;
    InitStructure->Price.Beet = 0;
    InitStructure->Price.Carrot = 0;

    InitStructure->ShippingHandling_Price = 0;
    InitStructure->TotalWeight = 0;
    InitStructure->TotalCost = 0;
    InitStructure->TotalOrderCost = 0;

    InitStructure->UnitPrice.Artichoke = PRICE_OF_ARTICHOKE;
    InitStructure->UnitPrice.Beet = PRICE_OF_BEET;
    InitStructure->UnitPrice.Carrot = PRICE_OF_CARROT;

    InitStructure->Weight.Artichoke = 0;
    InitStructure->Weight.Beet = 0;
    InitStructure->Weight.Carrot = 0;
}

/**
 * @brief 显示初始菜单界面
 * @author fwlh
 * @return char        返回用户输入的小写字母(其实是 getchar 函数的返回值)
 */
char Menu_Interface_Perform(void)
{
    char GetCh, temp;

    printf("Please enter one of the following chioce to purchase the corresponding product:\n");
    printf("a.Artichoke     b.Beet      c.Carrot    q.quit\n");

    while ((GetCh = getchar()) && (GetCh == '\n'))
        continue;
    return GetCh;
}

/**
 * @brief 获取用户数据并做相应的反应
 * @author fwlh
 * @param  InitStructure    用于收集信息的结构体
 * @return int              用于判断当前所有信息是否获取完毕(返回 1 代表信息获取完毕)
 */
int Select_Information(Shopping_Information_Structure *InitStructure)
{
    double weight;
    char NewChar = Menu_Interface_Perform();

    switch (NewChar)
    {
    case 'A':
    case 'a':
        printf("Please enter the weight you'd like to order:\n");
        scanf("%lf", &weight);
        while (weight < 0)
        {
            printf("Error Number! Please try again! \n");
            scanf("%lf", &weight);
        }
        InitStructure->Weight.Artichoke += weight;
        break;
    case 'B':
    case 'b':
        printf("Please enter the weight you'd like to order:\n");
        scanf("%lf", &weight);
        while (weight < 0)
        {
            printf("Error Number! Please try again! \n");
            scanf("%lf", &weight);
        }
        InitStructure->Weight.Beet += weight;
        break;
    case 'C':
    case 'c':
        printf("Please enter the weight you'd like to order:\n");
        scanf("%lf", &weight);
        while (weight < 0)
        {
            printf("Error Number! Please try again! \n");
            scanf("%lf", &weight);
        }
        InitStructure->Weight.Carrot += weight;
        break;
        break;
    case 'Q':
    case 'q':
        return 1;
    default:
        printf("Error Chioce! Please try again! \n");
        return 0;
    }

    return 0;
}

/**
 * @brief 计算用户输入的相关信息
 * @author fwlh
 * @param  InitStructure    相关购买信息
 */
void Product_Information_Calculate(Shopping_Information_Structure *InitStructure)
{
    InitStructure->Price.Artichoke = InitStructure->UnitPrice.Artichoke * InitStructure->Weight.Artichoke;
    InitStructure->Price.Beet = InitStructure->UnitPrice.Beet * InitStructure->Weight.Beet;
    InitStructure->Price.Carrot = InitStructure->UnitPrice.Carrot * InitStructure->Weight.Carrot;

    InitStructure->TotalOrderCost = InitStructure->Price.Artichoke + InitStructure->Price.Beet + InitStructure->Price.Carrot;

    InitStructure->Discount = DISCOUNT(InitStructure->TotalOrderCost);

    InitStructure->TotalWeight = InitStructure->Weight.Artichoke + InitStructure->Weight.Beet + InitStructure->Weight.Carrot;
    if (InitStructure->TotalWeight < 5)
        InitStructure->ShippingHandling_Price = 6.5;
    else if (InitStructure->TotalWeight > 20)
        InitStructure->ShippingHandling_Price = 0.5 * (ceil(InitStructure->TotalWeight) - 20) + 14;
    else
        InitStructure->ShippingHandling_Price = 14;

    InitStructure->TotalCost = InitStructure->TotalOrderCost - InitStructure->Discount + InitStructure->ShippingHandling_Price;
}

/**
 * @brief 输出用户输入的购买信息
 * @author fwlh
 * @param  InitStructure    相关购买信息
 */
void Print_Product_Information(Shopping_Information_Structure *InitStructure)
{
    printf("\n\nPurchased Products:\n");

    printf("%25s  %9s($/pounds)%8s%7s\n", "ProductName", "UnitPrice", "Weight", "Price");
    printf("%25s       %6.3f         %7.1f %6.1f\n", "Artichoke",
           InitStructure->UnitPrice.Artichoke,
           InitStructure->Weight.Artichoke, InitStructure->Price.Artichoke);
    printf("%25s       %6.3f         %7.1f %6.1f\n", "Beet",
           InitStructure->UnitPrice.Beet,
           InitStructure->Weight.Beet, InitStructure->Price.Beet);
    printf("%25s       %6.3f         %7.1f %6.1f\n", "Carrot",
           InitStructure->UnitPrice.Carrot,
           InitStructure->Weight.Carrot, InitStructure->Price.Carrot);

    printf("%25s  %9s           %8s%  6.1f\n", "TotalOrderCost", " ", " ", InitStructure->TotalOrderCost);
    if (fabs(InitStructure->Discount) > 0.06)
        printf("%25s  %9s           %8s%  6.1f\n", "Discount", " ", " ", -InitStructure->Discount);
    printf("%25s  %9s           %8s%  6.1f\n", "ShippingHandling Price", " ", " ", InitStructure->ShippingHandling_Price);
    printf("---------------------------------------------------------------\n");
    printf("%25s  %9s           %8s%  6.1f\n", "TotalCost", " ", " ", InitStructure->TotalCost);
}
