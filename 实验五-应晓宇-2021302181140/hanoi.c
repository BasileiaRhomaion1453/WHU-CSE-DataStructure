#include<stdio.h>
#include<stdlib.h>
void move(char getone, char putone) 
{
    printf("%c->%c\n", getone, putone);
}
void hanoi(int n,char one,char two,char three)
{
if(n==1)
   move(one,three);
   else
{
hanoi(n-1,one,three,two);
move(one,three);
hanoi(n-1,two,one,three);
}   }
int main()
{
    int m;
    printf("输入盘子的数目:");
    scanf("%d",&m);
    printf("移动%3d个盘子的步骤是：\n",m);
    hanoi(m,'A','B','C');
    system("pause");
    return 0;
}