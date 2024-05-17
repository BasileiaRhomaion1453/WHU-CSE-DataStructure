#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct qnode
{
    int data;
    struct qnode* next;
}QNODE;
typedef struct
{
    QNODE* front, * rear;
}QUTYPE;
void destroyqueue(QUTYPE *&qu)
{
    QNODE* pre, * p;
    pre = qu->front;
    if (pre != NULL)
    {
        p = pre->next;
        while (p != NULL)
        {
            free(pre);
            pre = p;
            p = p->next;
        }
        free(pre);
    }
    free(qu);
}
bool exist(QUTYPE* qu, int no)
{
    bool find = false;
    QNODE* p = qu->front;
    while (p != NULL && !find)
    {
        if (p->data == no) find = true;
        else p = p->next;
    }
    return find;
}
void seedoctor()
{
    int sel, no;
    bool flag = true;
    QUTYPE* qu;
    QNODE* p;
    qu = (QUTYPE*)malloc(sizeof(QUTYPE));
    qu->front = qu->rear = NULL;
    while (flag)
    {
        printf(">1：排队2：就诊3：查看排队4：不再排队，余下依次就诊5：下班  请选择：");
        scanf_s("%d", &sel);
        switch (sel)
        {
        case 1:
            printf("输入病历号：");
            while (true)
            {
                scanf_s("%d", &no);
                if (exist(qu, no))
                    printf("输入重复,请重新输入:");
                else break;
            };
            p = (QNODE*)malloc(sizeof(QNODE));
            p->data = no;
            p->next = NULL;
            if (qu->rear == NULL)
                qu->front = qu->rear = p;
            else
            {
                qu->rear->next = p;
                qu->rear = p;
            }
            break;
        case 2:if (qu->front == NULL)
            printf("没有排队的病人！\n");
              else
        {
            p = qu->front;
            printf(">>病人%d就诊\n", p->data);
            if (qu->rear == p)
                qu->front = qu->rear = NULL;
            else
                qu->front = p->next;
            free(p);
        }
              break;
        case 3:if (qu->front == NULL)
            printf("没有排队的病人！\n");
              else
        {
            p = qu->front;
            printf(">>排队病人：");
            while (p != NULL)
            {
                printf("%d", p->data);
                p = p->next;
            }
            printf("\n");
        }
              break;
        case 4:if (qu->front == NULL)
            printf("没有排队的病人！\n");
              else
        {
            p = qu->front;
            printf(">>病人按以下顺序就诊:");
            while (p != NULL)
            {
                printf("%d", p->data);
                p = p->next;
            }
            printf("\n");
        }
              destroyqueue(qu);
              flag = false;
              break;
        case 5:
            if (qu->front != NULL)
                printf("请排队的病人明天就医！\n");
            flag = false;
            destroyqueue(qu);
            break;
        }
    }
}
int main()
{
    seedoctor();
    return 1;
}