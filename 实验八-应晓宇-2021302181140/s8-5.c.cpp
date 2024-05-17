#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define INF 32767
#define MAXV 100
typedef char InfoType;
typedef struct
{
    int no;
    InfoType info;
}Vertextype;
typedef struct
{
    int edges[MAXV][MAXV];
    int n, e;
    Vertextype vex[MAXV];
}MatGraph;
typedef struct ANode
{
    int adjvex;
    struct ANode* nextarc;
    int weight;
}ArcNode;
typedef struct Vnode
{
    InfoType info;
    int count;
    ArcNode* firstarc;
}VNode;
typedef struct
{
    VNode adjlist[MAXV];
    int n, e;
}AdjGraph;
void CreateMat(MatGraph &g, int A[MAXV][MAXV], int n, int e)
{
    int i, j;
    g.n = n;
    g.e = e;
    for (i = 0; i < g.n; i++)
        for (j = 0; j < g.n; j++)
            g.edges[i][j] = A[i][j];
}
void DispMat(MatGraph g)
{
    int i, j;
    for (i = 0; i < g.n; i++) {
        for (j = 0; j < g.n; j++)
            if (g.edges[i][j] != INF)
                printf("%4d", g.edges[i][j]);
            else
                printf("%4s", "∞");
        printf("\n");
    }
}
void Prim(MatGraph g, int v)
{
    int lowcost[MAXV], min, n = g.n;
    int closest[MAXV], i, j, k;
    for (i = 0; i < n; i++) {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    }
    for (i = 1; i < n; i++) {
        min = INF;
        for (j = 0; j < n; j++)
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        printf("  边(%d,%d)权为:%d\n", closest[k], k, min);
        lowcost[k] = 0;
        for (j = 0; j < n; j++)
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j]) {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;
            }
    }
}
int main()
{
    int v = 3;
    MatGraph g;
    int A[MAXV][MAXV] = { {0,5,8,7,INF,3},{5,0,4,INF,INF,INF},{8,4,0,5,INF,9},{7,INF,5,0,5,6},{INF,INF,INF,5,0,1},{3,INF,9,6,1,0} };
    int n = 6, e = 10;
    CreateMat(g, A, n, e);
    printf("图G的邻接矩阵:\n");
    DispMat(g);
    printf("普里姆算法求解结果:\n");
    Prim(g, 0);
    system("pause");
    return 1;
}