#include<stdio.h>
#define maxn 20
int maxv,maxw;
int x[maxn];
int W=7,n=4;
int w[]={5,3,2,1};
int v[]={4,4,3,1};
void knap(int i,int tw,int tv,int op[])
{
    int j;
    if(i>=n)
    {
        if(tw<=W&&tv>maxv)
        {
            maxv=tv;
            maxw=tw;
            for(j=1;j<=n;j++)
            x[j]=op[j];
        }
    }
    else
    {
        op[i]=1;
        knap(i+1,tw+w[i],tv+v[i],op);
        op[i]=0;
        knap(i+1,tw,tv,op);
    }
}
void dispasolution(int x[],int n)
{
    int i;
    printf("最佳方案是：\n");
    for(i=1;i<=n;i++)
        if(x[i]==1)
        printf("选取第%d个物品\n",i);
    printf("总重量=%d,总价值=%d\n",maxw,maxv);

}
int main()
{
    int op[maxn];
    knap(0,0,0,op);
    dispasolution(x,n);
    return 1;
}