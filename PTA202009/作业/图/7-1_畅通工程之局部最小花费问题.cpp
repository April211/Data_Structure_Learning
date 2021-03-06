#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;


int main()
{
    int N = 0;                          // 村庄数目 N (1≤N≤100)
    scanf("%d", &N);

    int matrix[N+6][N+6];
    int in_u[N+6] = {0,}, weight[N+6] = {0,};    // 初始化为 0
    int n_line = (N%2==0)?((N/2)*(N-1)):(((N-1)/2)*N);  // 输入行数

    // 准备使用 Prim算法，初始化主矩阵为不可到达（边的权值为无穷大）
    for(int i = 1; i<= N; i++)
    {
        for(int j = 1; j<= N; j++)
        {
            matrix[j][i] = inf;
        }
    }

    // 随后的 N(N−1)/2行对应村庄间道路的成本及修建状态：
    // 每行给出4个正整数，分别是两个村庄的编号（从 1 编号到 N），此两村庄间道路的成本，以及修建状态 — 1表示已建，0表示未建
    for(int i = 0; i< n_line; i++)
    {
        int v1, v2, cost, status;
        scanf("%d%d%d%d", &v1, &v2, &cost, &status);
        if(status == 0)     // 如果该路没有建成，把边的权值赋值为修建成本
        {
            matrix[v1][v2] = matrix[v2][v1] = cost;     // 保持无向图矩阵的对称性
        }
        else                // 建成了的话，这条路径就会作为最小生成树的边，不需要成本（一定使用这条边）
        {
            matrix[v1][v2] = matrix[v2][v1] = 0;
        }
    }// 输入完毕

    // 从一号节点开始，将整个节点集分为两大部分：U 和 V-U
    in_u[1] = 1;

    // 辅助数组初始化，即载入其他各节点到集合 U 的新增节点（起始节点） 的代价
    for(int i = 1; i<= N; i++)
    {
        if(i == 1)
        {
            weight[i] = 0;   // 初始结点不贡献代价，后面每增加一个结点才会贡献出一个代价（边），共计 n-1 个代价（边）
        }
        else
        {
            weight[i] = matrix[1][i];   // 可能有 inf，代表暂时无法到达（代价无穷大）
        }
    }

    // 一共需要找 N 遍（前面已经加入了一个点，所以这里是 N-1 遍），每一遍只向集合 U 中添加一个节点
    for(int i = 0; i< N-1; i++)
    {
        int min = inf, node = 0;
        for(int j = 1; j<= N; j++)
        {
            if((!in_u[j]) && (min > weight[j]))
            {
                min = weight[j];
                node = j;
            }
        }// 在集合 V-U 中找到到达 U 的最小代价，并记录节点号
        in_u[node] = 1;      // 将该节点归入集合 U 中，但是不删除它在辅助数组中的代价

        // 更新 weigth 数列（原因是有新的节点加入到了集合 U 中，需要更新 V-U 到 U 的最小代价，看看有没有更小的代价可以更新到该数组中）
        for(int j = 1; j<= N; j++)
        {
            if((!in_u[j]) && (weight[j] > matrix[node][j]))
            {
                weight[j] = matrix[node][j];    // 更新为更小的代价
            }
        }
    }// 此时，weight 数组中存储的就是最小生成树各边的权值

    int sum_cost = 0;   // 新修建的路的总花费
    for(int i = 1; i<= N; i++)
    {
        sum_cost += weight[i];
    }// 对数组中元素求和即可

    printf("%d", sum_cost);

    return 0;
}


/* 7-1 畅通工程之局部最小花费问题 (35分)
某地区经过对城镇交通状况的调查，得到现有城镇间快速道路的统计数据，并提出“畅通工程”的目标：使整个地区任何两个城镇间都可以实现快速交通（但不一定有直接的快速道路相连，只要互相间接通过快速路可达即可）。现得到城镇道路统计表，表中列出了任意两城镇间修建快速路的费用，以及该道路是否已经修通的状态。现请你编写程序，计算出全地区畅通需要的最低成本。

输入格式:
输入的第一行给出村庄数目N (1≤N≤100)；随后的N(N−1)/2行对应村庄间道路的成本及修建状态：每行给出4个正整数，分别是两个村庄的编号（从1编号到N），此两村庄间道路的成本，以及修建状态 — 1表示已建，0表示未建。

输出格式:
输出全省畅通需要的最低成本。

输入样例:
4
1 2 1 1
1 3 4 0
1 4 1 1
2 3 3 0
2 4 2 1
3 4 5 0
输出样例:
3 */