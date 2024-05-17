#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct
{
    int key;
    char data;
}rectype;
void swap(rectype& x, rectype& y)
{
    rectype tmp=x;
    x=y;
    y=tmp;
}
void createlist(rectype r[],int keys[],int n)
{
    for(int i=0;i<n;i++)
    r[i].key=keys[i];
}
void displist(rectype r[],int n)
{
    for(int i=0;i<n;i++)
    printf("%d ",r[i].key);
    printf("\n");
}
void bininsertsorted(rectype r[],int n)
{
    int i,j,low,high,mid;
    rectype tmp;
    for(i=1;i<n;i++){
        if((r[i].key)<(r[i-1].key)){
            printf("i=%d,插入%d,插入结果: ",i,r[i].key);
            tmp=r[i];
            low=0;
            high=i-1;
            while(low<=high){
                mid=(low+high)/2;
                if(tmp.key<(r[mid].key))
                    high=mid-1;
                else
                    low=mid+1;
            }
            for(j=i-1;j>=high+1;j--)
                r[j+1]=r[j];
            r[high+1]=tmp;
        }
        displist(r,n);
    }
}
void shellsort(rectype r[],int n)
{
    int i,j,d;
    rectype tmp;
    d=n/2;
    while(d>0){
        for(i=d;i<n;i++){
            tmp=r[i];
            j=i-d;
            while(j>=0&&(tmp.key)<(r[j].key)){
                r[j+d]=r[j];
                j=j-d;
            }
            r[j+d]=tmp;
        }
        printf("d=%d:",d);
        displist(r,n);
        d=d/2;
    }
}
int main()
{
    int n=10;
    rectype r[MAX];
    int a[]={9,8,7,6,5,4,3,2,1,0};
    createlist(r,a,n);
    printf("排序前：");
    displist(r,n);
    bininsertsorted(r,n);
    printf("折半排序后:");
    displist(r,n);
    printf("希尔排序:\n");
    createlist(r,a,n);
    shellsort(r,n);
    printf("希尔排序后:");
    displist(r,n);
    system("pause");
    return 0;
}