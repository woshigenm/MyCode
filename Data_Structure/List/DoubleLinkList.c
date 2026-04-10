#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct DNode {
	ElemType data;
	struct DNode * prior;
	struct DNode * next;
} DNode, *DLinkList;

Status InitList(DLinkList *L);
Status GetElem(DLinkList L, int i, ElemType *e);
Status ListInsert(DLinkList L, int i, ElemType e);
Status ListDelete(DLinkList L, int i, ElemType *e);
int ListLength(DLinkList L);
bool ListEmpty(DLinkList L);
void PrintList(DLinkList L);
Status ClearList(DLinkList L);
Status DestroyList(DLinkList *L);
void PrintListReverse(DLinkList L);

int main()
{
	DLinkList L;
	InitList(&L);

	for (int i = 1; i <= 10; ++i)
		ListInsert(L, i, i);
	printf("链表长度：%d\n", ListLength(L));
	PrintList(L);
	ElemType e;

	for (int i = 1; i <= 5; ++i)
		ListDelete(L, 1, &e);
	printf("链表长度：%d\n", ListLength(L));
	PrintListReverse(L);

	ClearList(L);
	PrintList(L);

	DestroyList(&L);
	PrintList(L);

	return 0;
}

Status InitList(DLinkList * L)
{
	if (NULL == L)	return ERROR;
	*L = (DNode *)malloc(sizeof(DNode));
	if (NULL == *L)	return ERROR;
	(*L)->next = (*L)->prior = NULL;
	return OK;
}

Status GetElem(DLinkList L, int i, ElemType * e)
{
	if (NULL == L)	return ERROR;
	if (i < 1)	return ERROR;

	int j = 1;
	DNode * cur = L->next;
	while (j < i && cur) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur)	return ERROR;
	*e = cur->data;
	return OK;
}

Status ListInsert(DLinkList L, int i, ElemType e)
{
	if (NULL == L)	return ERROR;
	if (i < 1)	return ERROR;

	int j = 0;
	DNode * cur = L;
	while (j < i - 1 && cur) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur)	return ERROR;
	DNode * new_node  = (DNode *)malloc(sizeof(DNode));
	if (NULL == new_node )	return ERROR;
	new_node->data = e;

	new_node->next = cur->next;
	new_node->prior = cur;

	if (cur->next != NULL) {
		cur->next->prior = new_node ;  // 设置后继节点的前驱指针
	}

	cur->next = new_node ;

	return OK;
}

Status ListDelete(DLinkList L, int i, ElemType * e)
{
	if (NULL == L)	return ERROR;
	if (i < 1)	return ERROR;

	int j = 0;
	DNode * cur = L;
	while (j < i && cur) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur)	return ERROR;
	*e = cur->data;

	cur->prior->next = cur->next;
	if (cur->next != NULL) {
		cur->next->prior = cur->prior;
	}

	free(cur);
	return OK;
}

//重置线性表为空表
Status ClearList(DLinkList  L)
{
	if (NULL == L)	return ERROR;
	DNode * cur = L->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	L->next = NULL;
	return OK;
}

Status DestroyList(DLinkList * L)
{
	if (NULL == L || NULL == *L)	return ERROR;
	DNode * cur = (*L)->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(*L);
	*L = NULL;
	return OK;
}

void PrintList(DLinkList L)
{
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (NULL == L->next) {
		printf("空链表\n");
		return;
	}

	DNode * cur = L->next;
	while (cur) {
		printf("%d -> %p\n", cur->data, cur);
		cur = cur->next;
	}

	putchar('\n');
}

//返回单链表长度
int ListLength(DLinkList L)
{
	if (NULL == L)	return 0;
	DNode * cur = L->next;
	int len = 0;
	while (cur) {
		cur = cur->next;
		++len;
	}
	return len;
}

//返回单链表是否为空表
bool ListEmpty(DLinkList L)
{
	if (NULL == L)	return true;
	return L->next == NULL;
}

void PrintListReverse(DLinkList L)
{
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (NULL == L->next) {
		printf("空链表\n");
		return;
	}

	DNode *tail = L->next;
	while (tail->next != NULL) {
		tail = tail->next;
	}

	while (tail != L) {
		printf("%d -> %p\n", tail->data, tail);
		tail = tail->prior;
	}

	putchar('\n');
}

