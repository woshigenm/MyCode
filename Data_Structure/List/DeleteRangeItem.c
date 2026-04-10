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
Status DeleteRangeItem(LinkList L, ElemType mink, ElemType maxk);

int main()
{
	int array1[] = {3, 0, -1, 1, 1, 1, 1, 4, 4};
	int len1 = sizeof(array1) / sizeof(*array1);

	LinkList L1;
	InitList(&L1);

	for (int i = 1; i <= len1; ++i)
		ListInsert(L1, i, array1[i - 1]);
	PrintList(L1);

	DeleteRangeItem(L1, -2, 5);
	PrintList(L1);

	DestoryList(&L1);
	return 0;
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

Status DeleteRangeItem(LinkList L, ElemType mink, ElemType maxk)
{
	if (NULL == L || NULL == L->next) return ERROR;

	LNode *slow = L, *fast = slow->next, *tmp = NULL;
	while (fast) {
		if (fast->data > mink && fast->data < maxk) {
			tmp = fast;
			fast = fast->next;
			free(tmp);
		} else {
			slow->next = fast;
			slow = slow->next;
			fast = fast->next;
		}
	}

	slow->next = NULL;
	return OK;
}


