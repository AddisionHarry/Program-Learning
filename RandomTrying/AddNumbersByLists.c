/**
 * @file AddNumbersByLists.c
 * @brief 来自 LeetCode 第二题
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * 例如:
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 *
 * 每个链表中的节点数在范围 [1, 100] 内
 * 0 <= Node.val <= 9
 * 题目数据保证列表表示的数字不含前导零
 * @author fwlh
 * @version 1.0
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022  哈尔滨工业大学(威海)HERO战队
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

#define MAX(a, b) ((a > b) ? a : b)

/**
 * @brief 获取链表的长度
 * @author fwlh
 * @param  list             链表头
 * @return int              长度
 */
int GetLen(struct ListNode *list)
{
    int len = 0;
    while (list)
    {
        list = list->next;
        len++;
    }
    return len;
}

/**
 * @brief 将两个链表代表的数字相加返回一个新的链表
 * @author fwlh
 * @param  l1               待计算的链表
 * @param  l2               待计算的链表
 * @return struct ListNode* 计算结束的链表
 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int len = MAX(GetLen(l1), GetLen(l2));
    struct ListNode *startNode = (struct ListNode *)malloc(len * sizeof(struct ListNode));
    struct ListNode *NewNode = startNode;
    /******************** 准备第一轮计算 *********************/
    char num1 = l1->val, num2 = l2->val, overflowflag = 0, addedNumber = 0;
    // 求和
    addedNumber = num1 + num2;
    // 计算是否需要进位
    if (addedNumber >= 10)
        overflowflag = 1;
    else
        overflowflag = 0;
    // 写入数据
    startNode->val = addedNumber % 10;
    // 向下调度
    l1 = l1->next;
    l2 = l2->next;

    /******************** 循环计算 *********************/
    while (l1 || l2)
    {
        // 开辟新的节点
        NewNode->next = NewNode + 1;
        NewNode = NewNode->next;
        // 读新的数据
        if (l1)
            num1 = l1->val;
        else
            num1 = 0;
        if (l2)
            num2 = l2->val;
        else
            num2 = 0;
        // 计算加法
        addedNumber = num1 + num2 + overflowflag;
        if (addedNumber < 10)
            overflowflag = 0;
        else
            overflowflag = 1;
        NewNode->val = addedNumber % 10;
        // 链表递增
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    NewNode->next = NULL;
    // 全部结束, 但是还有一位进位
    if(overflowflag)
    {
        NewNode->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        NewNode->next->next = NULL;
        NewNode->next->val = 1;
    }
    return startNode;
}

/**
 * @brief 将链表中的元素打印出来
 * @author fwlh
 * @param  list             待打印的链表
 */
void Print_Node(struct ListNode *list)
{
    while (list)
    {
        printf("%d\n", list->val);
        list = list->next;
    }
}

/**
 * @brief 根据传入的字符串创建一个链表
 * @author fwlh
 * @param  stringNumber     字符串
 * @return struct ListNode* 创建的链表
 */
struct ListNode *CreateNode(char stringNumber[])
{
    struct ListNode *startNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *newNode = startNode;
    int len = 0;
    while (stringNumber[len] != '\0')
        ++len;
    len -= 1;
    for (; len > 0; --len)
    {
        newNode->val = stringNumber[len] - '0';
        newNode = (newNode->next = (struct ListNode *)malloc(sizeof(struct ListNode)));
    }
    newNode->val = stringNumber[len] - '0';
    newNode->next = NULL;
    return startNode;
}

int main(int argc, char *argv[])
{
    struct ListNode *l1, *l2, *lout;
    printf("List1:\n");
    Print_Node(l1 = CreateNode("9999"));
    printf("len:%d\n", GetLen(l1));
    printf("List2:\n");
    Print_Node(l2 = CreateNode("9999999"));
    printf("len:%d\n", GetLen(l2));
    printf("Output:\n");
    Print_Node(addTwoNumbers(l1, l2));
    getchar();
    return 0;
}
