#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

typedef struct LNode {
	ElemType data;
	struct LNode * next;
} LNode, *LinkList;

Status InitList(LinkList * L);
Status ListInsert(LinkList L, int i, ElemType e);
void PrintList(LinkList L);
Status DestoryList(LinkList * L);
Status FindMaxLinkList(LinkList L, ElemType * e);
void FindMaxLinkListR(LinkList L, ElemType * Max);

int main()
{
	int array1[] = {2, -3, 5, -1, 4, 0};
	int len1 = sizeof(array1) / sizeof(*array1);

	LinkList L1;
	InitList(&L1);

	for (int i = 1; i <= len1; ++i)
		ListInsert(L1, i, array1[i - 1]);
	PrintList(L1);
	ElemType e;

	if (FindMaxLinkList(L1, &e) == OK) {
		printf("MAX -> %d\n", e);
	}

	FindMaxLinkListR(L1, &e);

	DestoryList(&L1);
	return 0;
}

void FindMaxLinkListR(LinkList L, ElemType * Max)
{
	if (L == NULL)	return;
	if (L->next == NULL) {
		*Max = L->data;
	}
	FindMaxLinkListR(L->next, Max);
	if (L->data > *Max)
		*Max = L->data;
}

Status InitList(LinkList * L)
{
	if (NULL == L)	return	ERROR;
	*L = (LNode *)malloc(sizeof(LNode));
	if (NULL == *L)	return ERROR;
	(*L)->next = NULL;
	return OK;
}

Status ListInsert(LinkList L, int i, ElemType e)
{
	if (NULL == L)	return ERROR;
	if (i < 1)	return	ERROR;

	int j = 0;
	LNode * cur = L;
	while (j < i - 1 && cur) {
		cur = cur->next;
		j++;
	}

	if (NULL == cur)	return ERROR;
	LNode * NewNode = (LNode *)malloc(sizeof(LNode));
	if (NULL == NewNode)	return ERROR;
	NewNode->data = e;
	NewNode->next = cur->next;
	cur->next = NewNode;

	return OK;
}

void PrintList(LinkList L)
{
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (NULL == L->next) {
		printf("链表为空\n");
		return;
	}

	for (LNode * cur = L->next; cur; cur = cur->next) {
		printf("%d -> %p\n", cur->data, cur);
	}

	putchar('\n');
}

Status DestoryList(LinkList * L)
{
	if (NULL == L || NULL == *L)	return ERROR;

	LNode * cur = (*L)->next, *tmp = NULL;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	free(*L);
	*L = NULL;
	return OK;
}

Status FindMaxLinkList(LinkList L, ElemType * e)
{
	if (NULL == L || NULL == L->next || NULL == e)	return ERROR;

	LNode * p = L->next;
	ElemType Max = p->data;
	while (p) {
		if (p->data > Max) {
			Max = p->data;
		}
		p = p->next;
	}

	*e = Max;
	return OK;
}
