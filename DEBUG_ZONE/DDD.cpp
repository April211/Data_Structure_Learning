#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
#define inf 0x3f3f3f3f

// 二叉树结点
typedef struct TNode
{
    int Data;
    TNode *Left;
    TNode *Right;
} TNode;
typedef TNode *BiTree;

// 按照规则向二叉树中插入一个节点
void InsertNode(BiTree &bt, int value) // 二叉树类型，N 个节点，要插入的结点的值
{
    TNode *pt = bt;
    if ((!(pt->Left)) && ((value) > (pt->Data))) // 如果左子树为空，并且新节点的值比此根节点的值小
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Left = add;
        return;
    }
    else if ((!(pt->Right)) && ((value) < (pt->Data)))
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Right = add;
        return;
    }
    else if ((value) > (pt->Data)) // 左右节点都不为空，需要递归求解
    {
        return InsertNode(pt->Left, value);
    }
    else
    {
        return InsertNode(pt->Right, value);
    }
}

void InitBiTree(BiTree &bt)
{
    int tt;
    scanf("%d", &tt);
    bt = (BiTree)malloc(sizeof(TNode));
    bt->Data = tt;
    bt->Left = NULL;
    bt->Right = NULL;
}

void LevelorderTraversal(const BiTree &bt)
{
    if (!bt)
        return;
    queue<BiTree> lrtree;
    lrtree.push(bt);
    int flag = 0;
    while (!lrtree.empty())
    {
        BiTree tt = lrtree.front();
        if (tt) // 非空执行
        {
            if (flag == 0)
            {
                printf("%d", tt->Data);
                flag++;
            }
            else
            {
                printf(" %d", tt->Data);
            }

            lrtree.push(tt->Left);
            lrtree.push(tt->Right);
            lrtree.pop();
        }
    }
}

/* // 层序遍历（模拟队列实现）
void LevelorderTraversal(const BiTree &BT)
{
    if (!BT)
        return;
    BiTree temp[400]; // 顺序队列（图省事，题目限定编译头，且不让用 C++）
    int in = 0;
    int out = 0;
    int flag = 0;

    temp[in++] = BT; // root

    while (in > out) // 队列为空时，树就遍历完了
    {
        if (temp[out]) // 该指针不是空的，输出它所指向的节点的值，并把他的左右孩子入队列
        {
            if (flag == 0)
            {
                printf("%d", temp[out]->Data);
                flag++;
            }
            else
            {
                printf(" %d", temp[out]->Data);
            }
            temp[in++] = temp[out]->Left;
            temp[in++] = temp[out]->Right;
        }
        out++; // 原节点出队列
    }
} */

// 中序遍历
void InorderTraversal(const BiTree &BT)
{
    static int flag = 0;
    if (!BT)
        return;
    else
    {
        InorderTraversal(BT->Left);
        if (flag == 0)
        {
            printf("%d", BT->Data);
            flag++;
        }
        else
        {
            printf(" %d", BT->Data);
        }
        InorderTraversal(BT->Right);
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    BiTree bt;
    InitBiTree(bt);

    for (int i = 1; i < N; i++)
    {
        int tt;
        scanf("%d", &tt);
        InsertNode(bt, tt); // 构造二叉树（还剩 N-1 个节点未加入）
    }

    LevelorderTraversal(bt);
    //InorderTraversal(bt);

    return 0;
}