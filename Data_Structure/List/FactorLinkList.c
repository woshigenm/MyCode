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
Status FactorLinkList(LinkList L1, LinkList L2, LinkList L3);

int main() {
	int array1[] = {2 , -3 , 5 , -1 , 4 , -6};
	int len1 = sizeof(array1) / sizeof(*array1);

	LinkList L1, L2, L3;
	InitList(&L1);
	InitList(&L2);
	InitList(&L3);

	for (int i = 1; i <= len1; ++i)
		ListInsert(L1, i, array1[i - 1]);
	PrintList(L1);

	FactorLinkList(L1, L2, L3);
	PrintList(L2);
	PrintList(L3);

	DestoryList(&L1);
	DestoryList(&L2);
	DestoryList(&L3);
	return 0;
}

Status InitList(LinkList * L) {
	if (NULL == L)	return	ERROR;
	*L = (LNode *)malloc(sizeof(LNode));
	if (NULL == *L)	return ERROR;
	(*L)->next = NULL;
	return OK;
}

Status ListInsert(LinkList L, int i, ElemType e) {
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

void PrintList(LinkList L) {
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

Status DestoryList(LinkList * L) {
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

Status FactorLinkList(LinkList L1, LinkList L2, LinkList L3) {
	if (NULL == L1 || NULL == L2 || NULL == L3 || NULL == L1->next)	return ERROR;

	LNode * Small = L2;
	LNode * Large = L3;
	LNode * p1 = L1->next;
	while (p1) {
		if (p1->data < 0) {
			Small->next = p1;
			Small = Small->next;
		} else if (p1->data > 0) {
			Large->next = p1;
			Large = Large->next;
		}
		p1 = p1->next;
	}

	Small->next = NULL;
	Large->next = NULL;
	L1->next = NULL;
	return OK;
}

