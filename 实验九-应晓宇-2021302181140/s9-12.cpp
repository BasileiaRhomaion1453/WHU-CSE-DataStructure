#include<stdio.h>
#include<stdlib.h>
#define maxsize 100
typedef struct node
{
    int key;
    char data;
    struct node *lchild,*rchild;
}bstnode;
bool insertbst(bstnode *&bt,int k)
{
    if(bt==NULL){
        bt=(bstnode *)malloc(sizeof(bstnode));
        bt->key=k;
        bt->lchild=bt->rchild=NULL;
        return true;
    }
    else if(k==bt->key)
    return false;
    else if(k<bt->key)
    return insertbst(bt->lchild,k);
    else
    return insertbst(bt->rchild,k);
}
void dispbst(bstnode *bt)
{
    if(bt!=NULL){
        printf("%d",bt->key);
        if(bt->lchild!=NULL||bt->rchild!=NULL){
            printf("(");
            dispbst(bt->lchild);
            if(bt->rchild!=NULL)
                printf(",");
            dispbst(bt->rchild);
            printf(")");
        }
    }
}
bstnode *createbst(int a[],int n)
{
    bstnode *bt=NULL;
    int i=0;
    while(i<n)
        if(insertbst(bt,a[i])==1){
            printf("    第%d步,插入%d:",i+1,a[i]);
            dispbst(bt);
            printf("\n");
            i++;
        }
    return bt;
}
bstnode *lca(bstnode *bt,int x,int y)
{
    if(bt==NULL)
        return NULL;
    if(x<bt->key&&y<bt->key)
        return lca(bt->lchild,x,y);
    else if(x>bt->key&&y>bt->key)
        return lca(bt->rchild,x,y);
    else
        return bt;
}
void destroybst(bstnode *bt)
{
    if(bt!=NULL){
        destroybst(bt->lchild);
        destroybst(bt->rchild);
        free(bt);
    }
}
int main()
{
    bstnode *bt,*p;
    int x=1,y=4;
    int a[]={5,2,1,6,7,4,8,3,9},n=9;
    printf("(1)构造二叉排序树bt\n");
    bt=createbst(a,n);
    printf("(2)输出bst:");
    dispbst(bt);
    printf("\n");
    printf("(3)查找%d和%d结点的lca\n",x,y);
    p=lca(bt,x,y);
    if(p)
    printf("lca是:%d\n",p->key);
    else 
    printf("指定的关键字不存在\n");
    printf("(4)销毁bt");
    destroybst(bt);
    printf("\n");
    system("pause");
    return 1;
}