#include <cstring>
#include <iostream>
#include <string>
using namespace std;

struct TNode
{
    int space;               //记录打印空格数
    int prior;               //标记是文件还是目录，文件优先级0，目录优先级1(优先级大的优先)
    char name[261];          //文件名
    struct TNode *son, *sib; //孩子、兄弟结点指针
};

struct TNode *NewNode(struct TNode *root, char *name, int prior)
{ //新结点
    struct TNode *node;
    node = (struct TNode *)malloc(sizeof(struct TNode));
    strcpy(node->name, name);
    node->sib = node->son = NULL;
    node->prior = prior;
    node->space = root->space + 2;
    return node;
}

struct TNode *Add(struct TNode *root, char *name, int prior)
{ //插入结点
    struct TNode *p = root;
    struct TNode *node = NewNode(root, name, prior);
    if (p->son == NULL)
    {
        p->son = node;
        return p->son;
    }
    else
    {
        if (cmp(node, p->son) == 1)
        { //前插
            node->sib = p->son;
            p->son = node;
            return p->son;
        }
        else if (cmp(node, p->son) == -1)
        { //结点相同，返回结点位置即可
            return p->son;
        }
        else
        { //同一层则往兄弟结点找
            p = p->son;
            while (p->sib)
            {
                if (cmp(node, p->sib) == 1)
                { //前插
                    node->sib = p->sib;
                    p->sib = node;
                    return p->sib;
                }
                else if (cmp(node, p->sib) == -1)
                { //结点相同，返回结点位置即可
                    return p->sib;
                }
                p = p->sib;
            }
            if (!p->sib)
            { //找到末尾插入即可
                p->sib = node;
                return p->sib;
            }
        }
    }
}

int IsChar(char c)
{ //判断是否是英文字母
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int cmp(struct TNode *p, struct TNode *q)
{ //先按优先级比较优先级，优先级相等再按字典序比较
    if (p->prior > q->prior)
        return 1;
    if (p->prior == q->prior)
    {
        if (strcmp(p->name, q->name) < 0)
            return 1;
        if (strcmp(p->name, q->name) == 0)
            return -1;
    }
    return 0;
}

void Out(struct TNode *root)
{ //输出打印
    int i;
    if (root)
    {
        for (i = 0; i < root->space; i++)
        {
            printf(" ");
        }
        printf("%s\n", root->name);
        Out(root->son);
        Out(root->sib);
    }
}


int main()
{
    struct TNode *root = (struct TNode *)malloc(sizeof(struct TNode));
    root->sib = root->son = NULL;
    root->space = 0;
    root->prior = 1;
    strcpy(root->name, "root");
    char input[261];
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%s", input);
        int j, k = 0, prior = 0;
        char name[261];
        struct TNode *p = root;
        for (j = 0; input[j] != '\0'; j++)
        {
            if (IsChar(input[j]))
                name[k++] = input[j];
            else if (input[j] == '\\')
            {
                name[k] = '\0';
                prior = 1;
                p = Add(p, name, prior);
                k = 0;
            }
        }
        if (input[j] == '\0' && IsChar(input[j - 1]))
        {
            name[k] = '\0';
            prior = 0;
            p = Add(p, name, prior);
        }
    }
    Out(root);
    return 0;
}
