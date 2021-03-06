#include <cstdio>
#include <cstdlib>

// 函数所返回的错误代码
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int *Triplet;   // 指向整型的指针
typedef int  Status;    // 函数返回的状态值

// 初始化三元组
Status InitTriplet (Triplet &T, int v1, int v2, int v3)
{
    T = (int*)malloc(3* sizeof(int));
    if(!T) exit(OVERFLOW);              // 如果存储空间分配失败，返回 OVERFLOW，中断进程
    T[0] = v1, T[1] = v2, T[2] = v3;
    return OK;
}// InitTriplet

// 销毁三元组
Status DestroyTriplet (Triplet &T)
{
    if(T != NULL)
    {
        free(T);
        T = NULL;
        return OK;
    }
    else
    {
        return ERROR;
    }
}// DestroyTriplet

// 获取三元组中第 i 个元素的值
Status GetValue (const Triplet &T, int i, int &ans)
{
    if(!(i >= 1 && i <= 3) || (T == NULL)) return ERROR;
    ans = T[i - 1];
    return OK;
}// GetValue

// 将所给的值 'a' 放入三元组的指定位置 'i' 处
Status PutValue (Triplet &T, int i = 0, int a = 0)
{
    if(!(i >= 1 && i <= 3) || (T == NULL)) return ERROR;
    T[i - 1] = a;
    return OK;
}// PutValue

// 判断三元组的元素是否按照升序排列
Status IsAscending (const Triplet &T)
{
    if(T == NULL)
        return ERROR;
    else if((T[0] <= T[1]) && (T[1] <= T[2]))
        return TRUE;
    else
        return FALSE;
}// IsAscending

// 判断三元组的元素是否按照降序排列
Status IsDecending (const Triplet &T)
{
    if(T == NULL)
        return ERROR;
    else if((T[0] >= T[1]) && (T[1] >= T[2]))
        return TRUE;
    else
        return FALSE;
}// IsDecending

// 获取三元组中数值最大的元素
Status Max (const Triplet &T, int &ans)
{
    if(T == NULL) return ERROR;
    ans = (T[0] >= T[1])?((T[0] >= T[2])?T[0]:T[2]):((T[1] >= T[2])?T[1]:T[2]);
    return OK;
}// Max

// 获取三元组中数值最小的元素
Status Min (const Triplet &T, int &ans)
{
    if(T == NULL) return ERROR;
    ans = (T[0] <= T[1])?((T[0] <= T[2])?T[0]:T[2]):((T[1] <= T[2])?T[1]:T[2]);
    return OK;
}// Min

int main()
{
    Triplet tp = NULL;
    int     ans = 0, min = 0, max = 0;
    InitTriplet(tp, 11, 14, 28);
    printf("The data which used a regular way to access is : %d.\n", *(tp+1));    // 访问第二个元素
    if(GetValue(tp, 3, ans))
        printf("(Using function to access the data) : %d.\n", ans);
    if(Max(tp, max))
        printf("The biggest value in this triplet is : %d.\n", max);
    if(Min(tp, min))
        printf("The smallest value in this triplet is : %d.\n", min);
    if(PutValue(tp, 3, 2001))
        printf("The 3rd element which has been edited is : %d.\n", tp[2]);
    if(IsAscending(tp))
        printf("This triplet is in an ascending order.\n");  
    if(IsDecending(tp))
        printf("This triplet is in a decending order.\n");  
    if(Max(tp, max))
        printf("The biggest value in this triplet is : %d.\n", max);
    if(Min(tp, min))
        printf("The smallest value in this triplet is : %d.\n", min);
    DestroyTriplet(tp);

    return 0;
}