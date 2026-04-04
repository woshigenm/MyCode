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
Status MergeList(LinkList L1, LinkList L2);
Status RevertList(LinkList L);
Status DestoryList(LinkList * L);

int main() {
	int array1[] = {1, 3, 5, 7};
	int array2[] = {2, 4, 6, 8};
	int arr1_len = sizeof(array1) / sizeof(*array1);
	int arr2_len = sizeof(array2) / sizeof(*array2);

	LinkList L1, L2;
	InitList(&L1);
	InitList(&L2);

	for (int i = 1; i <= arr1_len; ++i)
		ListInsert(L1, i, array1[i - 1]);

	for (int i = 1; i <= arr2_len; ++i)
		ListInsert(L2, i, array2[i - 1]);

	MergeList(L1, L2);
	RevertList(L1);
	PrintList(L1);

	DestoryList(&L1);
	DestoryList(&L2);
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

Status MergeList(LinkList L1, LinkList L2) {
	if (NULL == L1 || NULL == L2 || NULL == L1->next || NULL == L2->next)	return ERROR;

	LNode * L1_cur = L1, * L2_cur = L2->next, *tmp = NULL;
	while (L1_cur->next && L2_cur) {
		if (L1_cur->next->data < L2_cur->data) {
			L1_cur = L1_cur->next;
		} else if (L1_cur->next->data > L2_cur->data) {
			tmp = L2_cur->next;
			L2_cur->next = L1_cur->next;
			L1_cur->next = L2_cur;
			//L1_cur = L2_cur->next;
			L2_cur = tmp;
		} else {
			tmp = L2_cur->next;
			free(L2_cur);
			L2_cur = tmp;
		}
	}

	if (L2_cur) {
		L1_cur->next = L2_cur;
	}

	L2->next = NULL;
	return OK;
}

Status RevertList(LinkList L) {
	if (NULL == L || NULL == L->next)	return ERROR;

	LNode * prior = NULL, *cur = L->next, *Next = NULL;
	while (cur) {
		Next = cur->next;
		//L->next = cur;
		cur->next = prior;
		prior = cur;
		cur = Next;
	}

	L->next = prior;
	return OK;
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

