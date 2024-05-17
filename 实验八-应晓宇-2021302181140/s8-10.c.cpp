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
void CreateAdj(AdjGraph* &G, int A[MAXV][MAXV], int n, int e)
{
    int i, j;
    ArcNode* p;
    G = (AdjGraph*)malloc(sizeof(AdjGraph));
    for (i = 0; i < n; i++)
        G->adjlist[i].firstarc = NULL;
    for (i = 0; i < n; i++)
        for (j = n - 1; j >= 0; j--)
            if (A[i][j] != 0 && A[i][j] != INF) {
                p = (ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = A[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
            }
    G->n = n;
    G->e = e;
}
void DispAdj(AdjGraph* G)
{
    ArcNode* p;
    for (int i = 0; i < G->n; i++) {
        p = G->adjlist[i].firstarc;
        printf("%3d:", i);
        while (p != NULL) {
            printf("%3d[%d]->", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("^\n");
    }
}
void DestroyAdj(AdjGraph* &G)
{
    ArcNode* p, * pre;
    for (int i = 0; i < G->n; i++) {
        pre = G->adjlist[i].firstarc;
        if (pre != NULL) {
            p = pre->nextarc;
            while (p != NULL) {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
            free(pre);
        }
    }
    free(G);
}
int visited[MAXV];
void PallAll1(AdjGraph* G, int u, int v, int path[], int d)
{
    ArcNode* p;
    int j, w;
    d++;
    path[d] = u;
    visited[u] = 1;
    if (u == v && d > 0) {
        for (j = 0; j <= d; j++)
            printf("%3d", path[j]);
        printf("\n");
    }
    p = G->adjlist[u].firstarc;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0)
            PallAll1(G, w, v, path, d);
        p = p->nextarc;
    }
    visited[u] = 0;
}
void PallAll2(AdjGraph* G, int u, int v, int l, int path[], int d)
{
    int w, i;
    ArcNode* p;
    visited[u] = 1;
    d++;
    path[d] = u;
    if (u == v && d == 1) {
        for (i = 0; i <= d; i++)
            printf("%3d", path[i]);
        printf("\n");
    }
    p = G->adjlist[u].firstarc;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0)
            PallAll2(G, w, v, l, path, d);
        p = p->nextarc;
    }
    visited[u] = 0;
}
int ShortPath(AdjGraph* G, int u, int v, int path[])
{
    struct {
        int vno;
        int level;
        int parent;
    }qu[MAXV];
    int front = -1, rear = -1, k, lev, i, j;
    ArcNode* p;
    visited[u] = 1;
    rear++;
    qu[rear].vno = u;
    qu[rear].level = 0;
    qu[rear].parent = -1;
    while (front < rear) {
        front++;
        k = qu[front].vno;
        lev = qu[front].level;
        if (k == v) {
            i = 0;
            j = front;
            while (j != -1) {
                path[lev - i] = qu[j].vno;
                j = qu[j].parent;
                i++;
            }
            return lev;
        }
        p = G->adjlist[k].firstarc;
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                visited[p->adjvex] = 1;
                rear++;
                qu[rear].vno = p->adjvex;
                qu[rear].level = lev + 1;
                qu[rear].parent = front;
            }
            p = p->nextarc;
        }
    }
    return -1;
}
int main()
{
    int i, j;
    int u = 5, v = 2, l = 3;
    int path[MAXV];
    AdjGraph* G;
    int A[MAXV][MAXV] = { {0,1,0,1,0,0},{0,0,1,0,0,0},
                      {1,0,0,0,0,1},{0,0,1,0,0,1},
                      {0,0,0,1,0,0},{1,1,0,1,1,0} };
    int n = 6, e = 10;
    CreateAdj(G, A, n, e);
    printf("图G的邻接图表:\n");
    DispAdj(G);
    printf("(1)从顶点%d到%d的所有路径:\n", u, v);
    for (i = 0; i < n; i++)    visited[i] = 0;
    PallAll1(G, u, v, path, -1);
    printf("(2)从顶点%d到%d的所有长度为%d的路径:\n", u, v, l);
    PallAll2(G, u, v, l, path, -1);
    printf("(3)从顶点%d到%d的最短路径:\n", u, v);
    for (i = 0; i < n; i++) visited[i] = 0;
    j = ShortPath(G, u, v, path);
    for (i = 0; i <=j; i++)
        printf("%3d", path[i]);
    printf("\n");
    DestroyAdj(G);
    system("pause");
    return 1;
}