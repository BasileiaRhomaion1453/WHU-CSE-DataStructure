#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	float coe;
	int exp;  
	struct node* next;
}listNode;

listNode* createList(int n);
int printList(listNode* head);
int inverseList(listNode* head);
listNode* multi(listNode* head_a, listNode* head_b);

int main()
{
	printf("------多项式乘法------\n");

	int n;
	printf("请输入A(x)的项数:");
	scanf_s("%d", &n);
	listNode* head_a = createList(n);
	printf("A(x)=");
	printList(head_a);

	printf("请输入B(x)的项数:");
	scanf_s("%d", &n);
	listNode* head_b = createList(n);
	printf("B(x)=");
	printList(head_b);

	listNode* head_c = multi(head_a, head_b);
	printf("C(x) = A(x) * B(x) = ");
	printList(head_c);

	return 0;
}

listNode* createList(int n)
{
	listNode* head = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	listNode* pre = head;
	float coe;
	int exp;
	if (head == NULL)
	{
		printf("头结点开辟失败\n");
		exit(1);
	}
	head->next = NULL;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if ((p = (listNode*)malloc(sizeof(listNode))) == NULL)
		{
			printf("新结点开辟失败\n");
			exit(1);
		}
		printf("请输入第%d个系数和指数:", i + 1);
		scanf_s("%f %d", &coe, &exp);
		p->coe = coe;
		p->exp = exp;
		p->next = NULL;
		pre->next = p;
		pre = p;
	}
	return head;
}

int inverseList(listNode* head)
{
	listNode* p = head->next, * q;
	head->next = NULL;
	while (p)
	{
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}
	return 0;
}

int printList(listNode* head)
{
	listNode* p = head->next;
	while (p->next != NULL)
	{
		printf("%1.1f*X^%d+", p->coe, p->exp);
		p = p->next;
	}
	printf("%1.1f*X^%d\n", p->coe, p->exp);
	return 0;
}

listNode* multi(listNode* head_a, listNode* head_b)
{
	listNode* head_c, * pa = head_a, * pb = head_b, * pc, * newnode;
	int exp_max;
	if (pa->next != NULL && pb->next != NULL)
		exp_max = pa->next->exp + pb->next->exp;
	else
		return NULL;
	head_c = (listNode*)malloc(sizeof(listNode));
	if (head_c == NULL)
	{
		printf("链表c开辟失败\n");
		exit(1);
	}
	head_c->coe = 0.0;
	head_c->exp = 0;
	head_c->next = NULL;
	pc = head_c;
	inverseList(head_b);
	float COE = 0.0;
	int k = 0;
	for (k = exp_max; k >= 0; k--)
	{
		pa = head_a->next;
		while (pa != NULL && pa->exp > k)
			pa = pa->next;

		pb = head_b->next;
		while (pa != NULL && pb != NULL && pa->exp + pb->exp < k)
			pb = pb->next;
		while (pa != NULL && pb != NULL)
		{
			if (pa->exp + pb->exp == k)
			{
				COE += pa->coe * pb->coe;
				pa = pa->next;
				pb = pb->next;
			}
			else
			{
				if (pa->exp + pb->exp < k)
					pb = pb->next;
				else
					pa = pa->next;
			}
		}
		if (COE != 0.0)
		{
			if ((newnode = (listNode*)malloc(sizeof(listNode))) == NULL)
			{
				printf("链表c结点开辟失败");
				exit(1);
			}
			newnode->coe = COE;
			newnode->exp = k;
			newnode->next = NULL;

			pc->next = newnode;
			pc = newnode;
			COE = 0.0;
		}
	}
	inverseList(head_b);
	return head_c;
}