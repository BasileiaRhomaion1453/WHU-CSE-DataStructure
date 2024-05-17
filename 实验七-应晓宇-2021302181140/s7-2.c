#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef struct tree
{
    char data;
    struct tree *lchild,*rchild;
}tree,*bittree;
typedef struct
{
    bittree ch[maxsize];
    int front,rare;
}queue,*queuepoint;
bittree create()
{   
    char data;
    bittree t;
    scanf("%c", &data);
    getchar();
    if(data == '0')
    return NULL;
    else
    t=(tree *)malloc(sizeof(struct tree));
    t->data = data;
    printf("请输入%c的左子树：",data);
    t->lchild = create();
    printf("请输入%c的右子树：",data);
    t->rchild = create();
    return t;
}
void preg(bittree t)
{
    if(t==NULL) return;
    printf("%c", t->data);
    preg(t->lchild);
    preg(t->rchild);
}
void midg(bittree t)
{
    if(t==NULL) return;
    midg(t->lchild);
    printf("%c", t->data);
    midg(t->rchild);
}
void lastg(bittree t)
{
    if(t==NULL) return;
    lastg(t->lchild);
    lastg(t->rchild);
    printf("%c",t->data);
}
void pred(bittree t)
{
    if(t==NULL) return;
    bittree stack[maxsize]={0};
    int size=0;
    stack[size++]=t;
    while(size!=0)
    {
        t=stack[--size];
        printf("%c",t->data);
        if(t->rchild)
        stack[size++]=t->rchild;
        if(t->lchild)
        stack[size++]=t->lchild;
    }
}
void midd(bittree t)
{
    bittree stack[maxsize]={0};
    int size=0;
    while(size!=0||t!=NULL)
    {
        if(t!=NULL)
        {
            stack[size++]=t;
            t=t->lchild;
        }
        else
        {
            printf("%c",stack[--size]->data);
            t=stack[size]->rchild;
        }
    }
}
void lastd(bittree t)
{
    if(t==NULL) return;
    bittree stack1[maxsize]={0};
    bittree stack2[maxsize]={0};
    int size1=0;
    int size2=0;
    stack1[size1++]=t;
    while(size1!=0)
    {
        t=stack1[--size1];
        stack2[size2++]=t;
        if(t->lchild!=NULL)
        stack1[size1++]=t->lchild;
        if(t->rchild!=NULL)
        stack1[size1++]=t->rchild;
    }
    while(size2--!=0)
    printf("%c",stack2[size2]->data);
}
queuepoint iniststack()
{
    queuepoint l=(queuepoint)malloc(sizeof(queue));
    l->front=0;
    l->rare=0;
    return l;
}
void enqueue(queuepoint l,bittree t)
{
    if((l->rare+1)%maxsize==l->front)
    {
        printf("队列已满\n");
        exit(-1);
    }
    else
    {
        l->ch[l->rare]=t;
        l->rare=(l->rare+1)%maxsize;
    }
}
int isempty(queuepoint l)
{
    if(l->front==l->rare)
    return 1;
    else
    return 0;
}
bittree outstack(queuepoint l)
{
    bittree fuzhu;
    fuzhu=l->ch[l->front];
    l->front=(l->front+1)%maxsize;
    return fuzhu;
}
void cengci(bittree t)
{
    queuepoint s;
    s=iniststack();
    enqueue(s,t);
    while(!isempty(s))
    {
        bittree fuzhu=outstack(s);
        printf("%c",fuzhu->data);
        if(fuzhu->lchild)
        enqueue(s,fuzhu->lchild);
        if (fuzhu->rchild)
        enqueue(s,fuzhu->rchild);
        
    }
}
int main()
{
    bittree t;
    printf("请输入根结点数据：\n");
    t=create();
    printf("递归先序遍历结果：\n");
    preg(t);
    printf("\n");
    printf("非递归先序遍历结果：\n");
    pred(t);
    printf("\n");
    printf("递归中序遍历结果：\n");
    midg(t);
    printf("\n");
    printf("非递归中序遍历结果：\n");
    midd(t);
    printf("\n");
    printf("递归后序遍历结果：\n");
    lastg(t);
    printf("\n");
    printf("非递归后序遍历结果：\n");
    lastd(t);
    printf("\n");
    printf("层次遍历结果：\n");
    cengci(t);
    printf("\n");
    system("pause");
    return 0;
}