#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ITEMS 2000           // 最多的条目数量
#define NAME_MAX_LEN 20          // 名字的最大长度
#define VALID_MEMORY_FLAG (0x20) // 合法内存中的标志位

struct node_t
{
    struct node_t *prev;
    struct node_t *next;
};
typedef struct node_t list_t;

typedef enum
{
    Male,
    Female
} Gender_Enum;

typedef struct
{
    float Chinese;
    float Math;
    float English;
    float TotalScores;
} Scores_Struct;

typedef struct
{
    char *Name;
    int NameSize;
} Name_Struct;

typedef unsigned long long int ID_t;
typedef struct
{
    list_t List;          // 数据存储链表
    Name_Struct Name;     // 姓名
    ID_t ID;              // 独特的序列号, 不可重复
    Gender_Enum Gender;   // 性别
    Scores_Struct Scores; // 考试成绩
    uint8_t Inited;       // 用于标志是否为合法内存
} Information_Struct;

typedef enum
{
    Information_Name = 0,
    Information_Gender,
    Information_ID,
    PerformanceScores_Chinese,
    PerformanceScores_Math,
    PerformanceScores_English,
    PerformanceScores_Total,

    Inquire_All
} Inquire_Condition_Enum; // 查询方式

list_t *Start_Item = NULL;   // 链表的头节点, 但是需要被初始化
bool Program_Inited = false; // 标志位为真代表头节点已经被初始化了

// 初始化一个新的条目
Information_Struct *Information_Data_Init(void)
{
    Information_Struct *NewItem = (Information_Struct *)malloc(sizeof(Information_Struct));
    NewItem->List.next = NewItem->List.prev = &NewItem->List;
    NewItem->Gender = Male;
    NewItem->Scores.Chinese = NewItem->Scores.Math = NewItem->Scores.English = NewItem->Scores.TotalScores = 0.f;
    NewItem->Inited = VALID_MEMORY_FLAG;
    NewItem->Name.Name = NULL;
    return NewItem;
}

// 删除一个新的条目
void Information_Data_DeInit(Information_Struct *Item)
{
    // 不是合法内存, 不需要操作
    if (Item->Inited != VALID_MEMORY_FLAG)
    {
        free(Item);
        return;
    }
    Item->Inited = 0x00;
    // 保持链表连续
    if (Item->List.next != Item->List.prev)
    {
        Item->List.prev->next = Item->List.next;
        Item->List.next->prev = Item->List.prev;
    }
    // 释放内存
    free(Item->Name.Name);
    Item->Name.Name = NULL;
    free(Item);
    Item = NULL;
    return;
}

// 将链表中所有数据全部删除
void Delete_All_The_Lists(void)
{
    // 遍历链表
    Information_Struct *Info = (Information_Struct *)Start_Item;
    do
    {
        Info = (Information_Struct *)Info->List.next;
        Information_Data_DeInit(Info);
    } while (Info != (Information_Struct *)Start_Item);
    Information_Data_DeInit(Info);
}

// 打印信息表头
void Print_Information_Table(FILE *file)
{
    if (file == stdout)
    {
        printf("|\t\tName\t\t| Gender |\tID\t| Chinese |  Math  | English | Total |\n");
        printf("----------------------------------------------------------------------------------------------\n");
    }
    else
        fprintf(file, "Name, Gender, ID, Chinese, Math, English, Total\n");
}

// 将一个节点内的信息打印出来
void Print_Information_Node(FILE *file, Information_Struct *Node)
{
    if (!Node)
        return;
    if (file == stdout)
        printf("|%-31s|%-8s|%-14llu|%9.1f|%8.1f|%9.1f|%7.1f|\n",
               Node->Name.Name, (Node->Gender == Male) ? "Male" : "Female", Node->ID,
               Node->Scores.Chinese, Node->Scores.Math, Node->Scores.English, Node->Scores.TotalScores);
    else
        fprintf(file, "%s, %s, %llu, %.1f, %.1f, %.1f, %.1f\n",
                Node->Name.Name, (Node->Gender == Male) ? "Male" : "Female", Node->ID,
                Node->Scores.Chinese, Node->Scores.Math, Node->Scores.English, Node->Scores.TotalScores);
}

// 输出链表里面的所有节点的信息
void Export_Stored_All_Nodes(FILE *file)
{
    // 遍历链表
    Information_Struct *Info = (Information_Struct *)Start_Item;
    printf("Informations Stored:\n");
    Print_Information_Table(file);
    do
    {
        Info = (Information_Struct *)Info->List.next;
        Print_Information_Node(file, Info);
    } while (Info != (Information_Struct *)Start_Item);
}

// 打印链表里面的所有节点的信息
void Print_Stored_All_Nodes(void)
{
    Export_Stored_All_Nodes(stdout);
}

// 把当前的所有数据都存储到 CSV 格式的文件中
void Store_AllData_Into_CSVFile(void)
{
    FILE *filepointer; // 文件指针
    filepointer = fopen("AllData.csv", "w+");
    // 输出信息
    Export_Stored_All_Nodes(filepointer);
    // 关闭文件
    fclose(filepointer);
}

typedef struct
{
    struct result
    {
        list_t List;                    // 数据存储链表
        Information_Struct *ResultNode; // 结果正确的节点
    } *Results;                         // 查询结果
    int result_numbers;                 // 查询到结果的个数
} Search_Result;
// 按照固定方式和参数寻找节点, 没找到会返回空指针, 注意函数内部会对 param 参数取址, 所以不要传非指针参数
Search_Result *Search_Lists(Inquire_Condition_Enum inquire_condition, void *param)
{
    if (!Program_Inited || !param)
        return NULL;
    // 找到第一个节点
    Information_Struct *Search_Node = (Information_Struct *)Start_Item;
    int result_num = 0;        // 目前查询到结果的个数
    Search_Result *ret = NULL; // 最终结果的存储位置
    while (true)
    {
        switch (inquire_condition)
        {
        case Information_Name:
            // 先看长度
            if (Search_Node->Name.NameSize != strlen((char *)param))
                break;
            // 找到了, 存放到数组中
            if (strcmp(Search_Node->Name.Name, (char *)param) == 0)
                result_num++;
            else
                break;
        case Information_Gender:
            if (Search_Node->Gender == *(Gender_Enum *)param)
                result_num++;
            break;
        case Information_ID:
            if (Search_Node->ID == *(ID_t *)param)
                result_num++;
            break;
        case PerformanceScores_Chinese:
            if (Search_Node->Scores.Chinese == *(float *)param)
                result_num++;
            break;
        case PerformanceScores_Math:
            if (Search_Node->Scores.Math == *(float *)param)
                result_num++;
            break;
        case PerformanceScores_English:
            if (Search_Node->Scores.English == *(float *)param)
                result_num++;
            break;
        case PerformanceScores_Total:
            if (Search_Node->Scores.TotalScores == *(float *)param)
                result_num++;
            break;
        default:
            return NULL;
        }
        // 已经开始查询到结果了, 就直接开始分配内存并写入最终结果
        if (!ret && result_num)
        {
            ret = (Search_Result *)malloc(sizeof(Search_Result));
            ret->Results = (struct result *)malloc(sizeof(struct result));
            ret->Results->List.next = ret->Results->List.prev = &ret->Results->List;
            ret->result_numbers = result_num;
            ret->Results->ResultNode = Search_Node;
        }
        // 如果产生了新的需要记录的节点, 也要按照需求进行记录
        else if (ret && (ret->result_numbers != result_num))
        {
            struct result *newresult = (struct result *)malloc(sizeof(struct result));
            newresult->List.next = ret->Results->List.next;
            newresult->List.prev = &ret->Results->List;
            ret->Results->List.next->prev = &newresult->List;
            ret->Results->List.next = &newresult->List;
            newresult->ResultNode = Search_Node;
            ret->result_numbers = result_num;
        }
        // 查找完成, 直接退出
        if (Search_Node->List.next == Start_Item)
            break;
        else if (Search_Node->List.next)
            Search_Node = (Information_Struct *)Search_Node->List.next;
        // 发现了空指针, 立马返回
        else
            return NULL;
    }
    // 程序正常退出, 说明已经找到了, 所以直接返回
    return ret;
}

// 将查询得到的结果内存释放
void Delete_Inquire_Result(Search_Result *result)
{
    // 输入参数检查
    if (!result)
        return;
    // 向回释放参数直至只有一个节点为止
    while ((result->Results->List.next != result->Results->List.prev) ||
           (result->Results->List.next != &result->Results->List))
    {
        // 释放上一个节点
        result->Results->List.prev->prev->next = result->Results->List.prev->next;
        result->Results->List.prev->next->prev = result->Results->List.prev->prev;
        result->Results->List.prev->next = result->Results->List.prev->prev = NULL;
        free(result->Results->List.prev);
    }
    result->Results->List.prev = result->Results->List.next = NULL;
    free(result->Results);
    result->Results = NULL;
    free(result);
    result = NULL;
}

// 将查询的结果打印出来
void Print_Searched_Result(FILE *file, Search_Result *result)
{
    fprintf(file, "Totally %d results found:\n", result->result_numbers);
    // 还是先打印表头
    Print_Information_Table(file);
    // 遍历查询结果打印
    struct result *node = result->Results;
    for (int i = 0; i < result->result_numbers; ++i)
    {
        Print_Information_Node(file, node->ResultNode);
        node = (struct result *)node->List.next;
    }
}

// 把当前查询到的所有数据都存储到 CSV 格式的文件中
void Store_SearchedData_Into_CSVFile(Search_Result *result)
{
    FILE *filepointer; // 文件指针
    filepointer = fopen("SearchedData.csv", "w+");
    // 输出信息
    Print_Searched_Result(filepointer, result);
    // 关闭文件
    fclose(filepointer);
}

// 从命令行交互获得姓名
void Get_Name_From_CMD(Information_Struct *Item, Inquire_Condition_Enum inquire)
{
    bool Name_Get = false;
    // 清空缓冲区
    fflush(stdin);
    // 开始通过命令行交互输入姓名
    while (!Name_Get)
    {
        printf("Please enter the name and end with an 'Enter':\n");
        char Name[NAME_MAX_LEN + 1]; // 最后一个要存储结束符'\0'
        // 开始从缓冲区中读取姓名
        for (int i = 0; i < NAME_MAX_LEN; ++i)
        {
            Name[i] = getchar();
            // 判断是不是一个真的字符
            if (((Name[i] >= 'a') && (Name[i] <= 'z')) || (Name[i] == '.') ||
                ((Name[i] >= 'A') && (Name[i] <= 'Z')) || (Name[i] == ' '))
            {
                if (i < NAME_MAX_LEN - 1)
                    continue;
                else
                    goto RECORD_NAME;
            }
            // 输入姓名结束了, 判断是不是真的收到东西了
            else if (Name[i] == '\n')
            {
                // 一次合法输入都没有, 直接准备重新输入
                if (!i)
                {
                    printf("Please enter a real name!\n");
                    break;
                }
            RECORD_NAME:
                // 直接开始记录姓名
                Name[i] = 0;
                Item->Name.NameSize = i;
                if (!Item->Name.Name)
                    Item->Name.Name = (char *)malloc((i + 1) * sizeof(char));
                else if (strcmp(Item->Name.Name, Name) != 0)
                {
                    free(Item->Name.Name);
                    Item->Name.Name = NULL;
                    Item->Name.Name = (char *)malloc((i + 1) * sizeof(char));
                }
                else
                    return;
                for (int j = 0; j < i + 1; j++)
                    Item->Name.Name[j] = Name[j];
                printf("Get a name:%s\n", Item->Name.Name);
                Name_Get = true;
                break;
            }
            else
            { // 此次输入不合法, 重新输入
                printf("Please enter a real name!\n");
                break;
            }
        }
    }
}

// 从命令行交互获得 ID
void Get_ID_From_CMD(Information_Struct *Item, Inquire_Condition_Enum inquire)
{
    while (true)
    {
        printf("Please enter the ID number:\n");
        ID_t ID;
        void *ret;
        scanf("%llu", &ID);
        fflush(stdin);
        if ((ret = Search_Lists(Information_ID, (void *)&ID)) != NULL)
        {
            printf("ID Number repeted!\n");
            Delete_Inquire_Result(ret);
            continue;
        }
        Item->ID = ID;
        break;
    }
}

// 从命令行交互获得性别
void Get_Gender_From_CMD(Information_Struct *Item, Inquire_Condition_Enum inquire)
{
    while (true)
    {
        printf("Please enter the Gender(Give '1' or '2' and end with 'Enter'):\n1. Female\t2.Male\n");
        int gender = 0;
        scanf("%d", &gender);
        fflush(stdin);
        if ((gender != 1) && (gender != 2))
        {
            printf("Enter wrong!\n");
            continue;
        }
        if (gender % 2)
            Item->Gender = Female;
        else
            Item->Gender = Male;
        break;
    }
}

// 从命令行交互获得成绩
void Get_Scores_From_CMD(Information_Struct *Item, Inquire_Condition_Enum inquire)
{
    switch (inquire)
    {
    case PerformanceScores_Chinese:
    CHINESE_RESTART:
        printf("Please enter the Chinese score:\n");
        scanf("%f", &Item->Scores.Chinese);
        fflush(stdin);
        if ((Item->Scores.Chinese < 0.f) || (Item->Scores.Chinese > 200.f))
            goto CHINESE_RESTART;
        break;
    case PerformanceScores_Math:
    MATH_RESTART:
        printf("Please enter the Math score:\n");
        scanf("%f", &Item->Scores.Math);
        fflush(stdin);
        if ((Item->Scores.Math < 0.f) || (Item->Scores.Math > 200.f))
            goto MATH_RESTART;
        break;
    case PerformanceScores_English:
    ENGLISH_RESTART:
        printf("Please enter the English score:\n");
        scanf("%f", &Item->Scores.English);
        fflush(stdin);
        if ((Item->Scores.English < 0.f) || (Item->Scores.English > 200.f))
            goto ENGLISH_RESTART;
        break;
    default:
        Get_Scores_From_CMD(Item, PerformanceScores_Chinese);
        Get_Scores_From_CMD(Item, PerformanceScores_Math);
        Get_Scores_From_CMD(Item, PerformanceScores_English);
        break;
    }
    Item->Scores.TotalScores = Item->Scores.Chinese + Item->Scores.English + Item->Scores.Math;
}

void (*Get_Data_From_CMD[(int)Inquire_All])(Information_Struct *, Inquire_Condition_Enum) = {
    [Information_Name] = Get_Name_From_CMD,
    [Information_Gender] = Get_Gender_From_CMD,
    [Information_ID] = Get_ID_From_CMD,
    [PerformanceScores_Chinese... PerformanceScores_Total] = Get_Scores_From_CMD};

// 通过命令行交互方式添加一条记录
void ScanCMD_Add_Item_ToTheList(void)
{
    Information_Struct *NewItem = Information_Data_Init();
    Get_Name_From_CMD(NewItem, Information_Name);          // 开始通过命令行交互输入姓名
    Get_ID_From_CMD(NewItem, Information_ID);              // 输入 ID 号
    Get_Gender_From_CMD(NewItem, Information_Gender);      // 输入性别
    Get_Scores_From_CMD(NewItem, PerformanceScores_Total); // 输入成绩

    // 最后开始操作链表, 需要判断本次是不是在创建链表头
    if (!Program_Inited)
    {
        Start_Item = &NewItem->List;
        Program_Inited = true;
    }
    else
    {
        NewItem->List.next = Start_Item;
        NewItem->List.prev = Start_Item->prev;
        Start_Item->prev->next = &NewItem->List;
        Start_Item->prev = &NewItem->List;
    }
}

// 删除一条记录
void Delete_Item_FromTheList(void)
{
START_TO_DELETE:
    printf("Please enter the ID of which item to be deleted:\n");
    ID_t delete_ID;
    scanf("%llu", &delete_ID);
    fflush(stdin);
    Search_Result *ret = Search_Lists(Information_ID, &delete_ID);
RESTART_TO_CONFIRM:
    printf("Find %d item(s):\n", ret->result_numbers);
    Print_Information_Table(stdout);
    Print_Information_Node(stdout, ret->Results->ResultNode);
    printf("Are you sure to delete the item?[Y/n]");
    char confirm;
    scanf("%c", &confirm);
    fflush(stdin);
    if ((confirm == 'N') || (confirm == 'n'))
    {
        // 注意释放返回值
        Delete_Inquire_Result(ret);
        goto START_TO_DELETE;
    }
    else if ((confirm != 'Y') && (confirm != 'y'))
    {
        printf("Input wrong!\n");
        goto RESTART_TO_CONFIRM;
    }
    // 删除节点
    Information_Data_DeInit(ret->Results->ResultNode);
    Delete_Inquire_Result(ret);
}

// 修改一条记录
void Modify_Item_FromTheList(void)
{
START_TO_MODIFY:
    printf("Please enter the ID of which item to modify:\n");
    ID_t modify_ID;
    scanf("%llu", &modify_ID);
    fflush(stdin);
    Search_Result *ret = Search_Lists(Information_ID, (void *)&modify_ID);
    if (!ret)
    {
        printf("Item not found, please check your input number!\n");
        goto START_TO_MODIFY;
    }
RESTART_TO_MODIFY:
    printf("Find %d item(s):\n", ((!ret) ? 0 : ret->result_numbers));
    Print_Information_Table(stdout);
    Print_Information_Node(stdout, ret->Results->ResultNode);
    printf("Are you sure to modify the item?[Y/n]");
    char confirm;
    scanf("%c", &confirm);
    fflush(stdin);
    if ((confirm == 'N') || (confirm == 'n'))
    {
        // 注意释放返回值
        Delete_Inquire_Result(ret);
    RESTART_TO_EXIT:
        printf("Go back to the main menu?[Y/n]\n");
        scanf("%c", &confirm);
        fflush(stdin);
        if ((confirm == 'N') || (confirm == 'n'))
            goto START_TO_MODIFY;
        else if ((confirm != 'Y') && (confirm != 'y'))
        {
            printf("Input wrong!\n");
            goto RESTART_TO_EXIT;
        }
        else
            return;
    }
    else if ((confirm != 'Y') && (confirm != 'y'))
    {
        printf("Input wrong!\n");
        goto RESTART_TO_MODIFY;
    }
    // 修改节点
MODIFY_START:
    printf("Please enter which subject to modify:\n1.Name\t\t2.Gender\t3.ID\t\n4.Chinese score\t"
           "5.Math score\t6.English Score\n");
    char operator= 0;
    scanf("%c", &operator);
    fflush(stdin);
    if ((operator<= '0') || (operator>= '6'))
        goto MODIFY_START;
    Get_Data_From_CMD[(operator- '1')](ret->Results->ResultNode, (Inquire_Condition_Enum)(operator- '1'));
    // 释放查询结果
    Delete_Inquire_Result(ret);
}

// 获得返回结构以后进行相关结果的处理
static int Dealwith_Search_Result(Information_Struct *TempItem, Inquire_Condition_Enum subject)
{
    // 获得待查询项目
    Get_Data_From_CMD[subject](TempItem, subject);
    // 进行查询
    Search_Result *ret;
    switch (subject)
    {
    case Information_Name:
        ret = Search_Lists(subject, (void *)&TempItem->Name.Name);
        break;
    case Information_Gender:
        ret = Search_Lists(subject, (void *)&TempItem->Gender);
        break;
    case Information_ID:
        ret = Search_Lists(subject, (void *)&TempItem->ID);
        break;
    case PerformanceScores_Chinese:
        ret = Search_Lists(subject, (void *)&TempItem->Scores.Chinese);
        break;
    case PerformanceScores_Math:
        ret = Search_Lists(subject, (void *)&TempItem->Scores.Math);
        break;
    case PerformanceScores_English:
        ret = Search_Lists(subject, (void *)&TempItem->Scores.English);
        break;
    case PerformanceScores_Total:
        ret = Search_Lists(subject, (void *)&TempItem->Scores.TotalScores);
        break;
    }
    if (!ret)
    {
        printf("No satisfying item found!\n");
        return -1;
    }
    Print_Searched_Result(stdout, ret);
    printf("Do you want to save the items?[Y/n]");
    char confirm;
    scanf("%c", &confirm);
    fflush(stdin);
    if ((confirm == 'N') || (confirm == 'n'))
    {
        // 注意释放返回值
        Delete_Inquire_Result(ret);
    RESTART_TO_EXIT:
        printf("Go back to the main menu?[Y/n]\n");
        scanf("%c", &confirm);
        fflush(stdin);
        if ((confirm == 'N') || (confirm == 'n'))
            return -1;
        else if ((confirm != 'Y') && (confirm != 'y'))
        {
            printf("Input wrong!\n");
            goto RESTART_TO_EXIT;
        }
        else
        {
            // 退出
            free(TempItem);
            TempItem = NULL;
            return 0;
        }
    }
    else if ((confirm != 'Y') && (confirm != 'y'))
    {
        printf("Input wrong!\n");
        goto RESTART_TO_EXIT;
    }
    // 保存为 CSV 文件
    Store_SearchedData_Into_CSVFile(ret);
    free(TempItem);
    TempItem = NULL;
    return 0;
}

// 根据指定的数据目标筛选数据
void Search_Item_According_Specific_Subject(void)
{
SEARCH_START:
    printf("Please specify which subject to search:\n1.Name\t\t2.Gender\t3.ID\t\n4.Chinese score\t"
           "5.Math score\t6.English Score\n");
    char operator= 0;
    scanf("%c", &operator);
    fflush(stdin);
    if ((operator<= '0') || (operator>= '6'))
        goto SEARCH_START;
    // 用于查询的临时变量
    Information_Struct *TempItem = (Information_Struct *)malloc(sizeof(Information_Struct));
    // 查询和输出
    if (Dealwith_Search_Result(TempItem, (Inquire_Condition_Enum)(operator- '1')) == -1)
        goto SEARCH_START;
}

typedef enum
{
    Add_Item = 0, // 增加条目
    Delete_Item,  // 删除条目
    Show_Items,   // 展示所有条目
    Modify_Item,  // 修改条目
    Search_Items, // 筛选条目
    Save_All,     // 保存当前所有

    Operations_All
} Operation_Options; // 操作选项
void (*Operations[(int)Operations_All])(void) =
    {[Add_Item] = ScanCMD_Add_Item_ToTheList,
     [Delete_Item] = Delete_Item_FromTheList,
     [Show_Items] = Print_Stored_All_Nodes,
     [Modify_Item] = Modify_Item_FromTheList,
     [Search_Items] = Search_Item_According_Specific_Subject,
     [Save_All] = Store_AllData_Into_CSVFile};

// 主运行菜单
void Print_Start_Menu(void)
{
    printf("\n\nWelcome to the scores management system!\n\n");
    while (true)
    {
        if (!Program_Inited)
        {
            printf("Not yet the system started, please start your first item!\n");
            ScanCMD_Add_Item_ToTheList();
            continue;
        }
        fflush(stdin); // 清空缓冲区
        printf("\nPlease choose your operate options:\n1.Add an item\t\t\t2.Delete an item\n"
               "3.Show all the items here\t4.Change the specific item\n"
               "5.Search from the items\t\t6.Save all to CSV file\n"
               "7.Quit the system\n");
        char operator;
        scanf("%c", &operator);
        fflush(stdin);
        if ((operator> '7') || (operator<'1'))
        {
            printf("Input wrong!\n");
            continue;
        }
        else if (operator== '7')
        {
            printf("Saving the data.\n");
            Store_AllData_Into_CSVFile();
            printf("Ready to quit the system!\n");
            return;
        }
        else
            Operations[operator - '1']();
    }
}

int main(int argc, char *argv[])
{
    Print_Start_Menu();
    Delete_All_The_Lists();
    return 0;
}
