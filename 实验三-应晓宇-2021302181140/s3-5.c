#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define maxsize 100
#define M 4
#define N 4
int mg[M+2][N+2]={
    {1,1,1,1,1,1},
    {1,0,0,0,1,1},
    {1,0,1,0,0,1},
    {1,0,0,0,1,1},
    {1,1,0,0,0,1},
    {1,1,1,1,1,1}
};
struct 
{
    int i;
    int j;
    int di;
}St[maxsize],path[maxsize];
int top=-1;
int count=1;
int minlen=maxsize;

void dispapath()
{
    int k;
    printf("%5d: ",count++);
    for(k=0;k<=top;k++)
    printf("(%d,%d)",St[k].i,St[k].j);
    printf("\n");
    if(top+1<minlen)
    {
        for(k=0;k<=top;k++)
        path[k]=St[k];
        minlen=top+1;
    }
}

void disminpath()
{
    printf("最短路径如下：\n");
    printf("长度：%d\n",minlen);
    printf("路径:");
    for(int k=0;k<minlen;k++)
    printf("(%d,%d)",path[k].i,path[k].j);
    printf("\n");
}

void mgpath(int xi,int yi,int xe,int ye)
{
    int i,j,di,il,jl;
    bool find;
    top++;
    St[top].i=xi;
    St[top].j=yi;
    St[top].di=-1;

    mg[xi][yi]=-1;
    while(top>-1)
    {
        
        i=St[top].i;
        j=St[top].j;
        di=St[top].di;
        if(i==xe&&j==ye)
        {
            dispapath();
            mg[i][j]=0;
            top--;
            i=St[top].i;
            j=St[top].j;
            di=St[top].di;
        }
    

        find=false;
        while(di<4 && !find)
        {
            di++;
            switch(di)
            {
                case 0:il=i-1;jl=j;break;
                case 1:il=i;jl=j+1;break;
                case 2:il=i+1;jl=j;break;
                case 3:il=i;jl=j-1;break;
            }
            if(mg[il][jl]==0)   find=true;
        }
        if(find)
        {
            St[top].di=di;
            top++;
            St[top].i=il;
            St[top].j=jl;
            St[top].di=-1;
            mg[il][jl]=-1;
        }
        else
        {
            mg[i][j]=0;
            top--;
        }
    }
    disminpath();
}
int main()
{
    printf("迷宫所有路径如下：\n");
    mgpath(1,1,M,N);
    system("pause");
    return 1;
}