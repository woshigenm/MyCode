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
Status IntersectionList(LinkList L1, LinkList L2);
Status IntersectionList_Other(LinkList L1, LinkList L2);

int main()
{
	int array1[] = {1, 2, 3};
	int array2[] = {3, 4, 5, 6};

	int len1 = sizeof(array1) / sizeof(*array1);
	int len2 = sizeof(array2) / sizeof(*array2);

	LinkList L1, L2;
	InitList(&L1);
	InitList(&L2);

	for (int i = 1; i <= len1; ++i) {
		ListInsert(L1, i, array1[i - 1]);
	}

	for (int i = 1; i <= len2; ++i) {
		ListInsert(L2, i, array2[i - 1]);
	}

	printf("L1:\n");
	PrintList(L1);
	printf("L2:\n");
	PrintList(L2);

	printf("交集:\n");
	IntersectionList(L1, L2);
	PrintList(L1);

	DestoryList(&L1);
	DestoryList(&L2);
	return 0;
}

Status IntersectionList_Other(LinkList L1, LinkList L2)
{
	if (NULL == L1 || NULL == L2 || NULL == L1->next || NULL == L2->next)	return ERROR;

	LNode * p = L1, *p1 = L1->next, *p2 = L2->next, *tmp = NULL;
	while (p1 && p2) {
		if (p1->data == p2->data) {
			p->next = p1;
			p = p->next;

			p1 = p1->next;
			p2 = p2->next;
		} else if (p1->data < p2->data) {
			tmp = p1;
			p1 = p1->next;
			free(tmp);
		} else {
			p2 = p2->next;
		}
	}

	while (p1) {
		tmp = p1->next;
		free(p1);
		p1 = tmp;
	}

	p->next = NULL;

	return OK;
}

Status IntersectionList(LinkList L1, LinkList L2)
{
	if (NULL == L1 || NULL == L2 || NULL == L1->next || NULL == L2->next)	return ERROR;

	LNode * p1 = L1, *p2 = L2->next, *tmp = NULL;
	while (p1->next && p2) {
		if (p2->data < p1->next->data) {
			tmp = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p2 = tmp;
		} else if (p1->next->data <= p2->data) {
			p1 = p1->next;
		}
	}

	if (p2) {
		p1->next = p2;
	}

	L2->next = NULL;
	//合并结束

	LNode * slow = L1, *fast = slow->next;
	tmp = NULL;
	while (fast) {
		if (fast->next && fast->next->data == fast->data) {
			slow->next = fast;
			slow = fast;
			while (fast->next && fast->data == fast->next->data) {
				tmp = fast->next;
				fast->next = tmp->next;
				free(tmp);
			}
			fast = fast->next;
		} else {
			tmp = fast;
			fast = fast->next;
			free(tmp);
		}
	}

	slow->next = NULL;

	return OK;
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

