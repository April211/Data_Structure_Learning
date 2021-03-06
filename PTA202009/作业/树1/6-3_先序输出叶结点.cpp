#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

int CreatBinTree(BinTree *bt);
void PreorderPrintLeaves(BinTree BT);

int main()
{
    BinTree BT;
    CreatBinTree(&BT);
    printf("Leaf nodes are:");
    PreorderPrintLeaves(BT);
    printf("\n");

    return 0;
}

// 按照前序遍历规则创建二叉树（bt: 指向 TNode指针的指针）
// 如果这里的参数不是引用（Cpp才可以用）或者此形式，将会丢失递归时分配的空间（传参拷贝）
int CreatBinTree(BinTree *bt)
{
    char ch;
    scanf("%c", &ch); // 不能以回车结束，字母之间不能有多余空格
    if (ch == ' ')
    {
        *bt = NULL;
    }
    else
    {
        *bt = (TNode *)malloc(sizeof(TNode));
        if (!(*bt))
            exit(-2);
        (*bt)->Data = ch;
        CreatBinTree(&((*bt)->Left)); // 注意：参数是指向指针的指针（指针的地址）
        CreatBinTree(&((*bt)->Right));
    }
    return 0;
}

void PreorderPrintLeaves(BinTree BT)
{
    if (!BT)
        return;
    else
    {
        if(!(BT->Left) && !(BT->Right))
            printf(" %c", BT->Data);
        PreorderPrintLeaves(BT->Left);
        PreorderPrintLeaves(BT->Right);
    }    

}

/* 6-3 先序输出叶结点 (15分)
本题要求按照先序遍历的顺序输出给定二叉树的叶结点。

函数接口定义：
void PreorderPrintLeaves( BinTree BT );
其中BinTree结构定义如下：

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
函数PreorderPrintLeaves应按照先序遍历的顺序输出给定二叉树BT的叶结点，格式为一个空格跟着一个字符。

裁判测试程序样例：
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree();
void PreorderPrintLeaves( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("Leaf nodes are:");
    PreorderPrintLeaves(BT);
    printf("\n");

    return 0;
}

输出样例（对于图中给出的树）：


Leaf nodes are: D E H I */
