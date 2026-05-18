#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct CSNode {
	ElemType data;
	struct CSNode* next;
} CSNode;

typedef struct CSLinkList {
	CSNode* rear;
	CSNode* head;
	int size;
} *CSLinkList;

Status InitList(CSLinkList* L);
Status ListInsert(CSLinkList L, int i, ElemType e);
Status DestroyList(CSLinkList* L);

int main()
{
	CSLinkList L;
	InitList(&L);

	int i, m, n;
	printf("输入n 和 m: ");
	scanf("%d%d", &n, &m);

	for (i = 1; i <= n; i++) {
		ListInsert(L, i, i);
	}

	CSNode* prev = L->rear->next, * cur = prev->next, * tmp = NULL;
	while (cur != L->head) {
		for (int step = 1; step < m; ++step) {
			prev = cur;
			cur = cur->next;
			if (cur == L->head) {
				prev = cur;
				cur = cur->next;
			}
		}

		tmp = cur;
		prev->next = cur->next;

		if (cur == L->rear) {
			L->rear = prev;
		}

		cur = cur->next;
		if (cur == L->head) {
			prev = cur;
			cur = cur->next;
		}

		printf("%d\n", tmp->data);
		L->size--;
		free(tmp);
	}

	DestroyList(&L);
	return 0;
}

Status InitList(CSLinkList* L)
{
	if (NULL == L)	return ERROR;

	*L = (CSLinkList)malloc(sizeof(struct CSLinkList));
	if (NULL == *L)	return ERROR;

	(*L)->rear = (CSNode*)malloc(sizeof(struct CSNode));
	if (NULL == (*L)->rear) {
		free(*L);
		*L = NULL;
		return ERROR;
	}

	(*L)->rear->next = (*L)->rear;
	(*L)->head = (*L)->rear;
	(*L)->size = 0;
	return OK;
}

//循环单链表是否为空
bool IsEmpty(CSLinkList L)
{
	if (NULL == L)	return true;
	return L->head->next == L->head;
}

Status ListInsert(CSLinkList L, int i, ElemType e)
{
	if (NULL == L)	return ERROR;
	if (i < 1 || i > L->size + 1) return ERROR;

	int j = 0;
	CSNode* cur = L->head;
	while (j < i - 1) {
		cur = cur->next;
		++j;
	}

	CSNode* NewNode = (CSNode*)malloc(sizeof(CSNode));
	if (NULL == NewNode)	return ERROR;

	NewNode->data = e;
	NewNode->next = cur->next;
	cur->next = NewNode;

	if (i == L->size + 1) {
		L->rear = NewNode;
	}

	L->size++;
	return OK;
}

//销毁循环单链表
Status DestroyList(CSLinkList* L)
{
	if (NULL == *L || NULL == L)	return ERROR;

	CSNode* cur = (*L)->head->next, * tmp;
	while (cur != (*L)->head) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	free((*L)->head);
	free(*L);
	*L = NULL;
	return OK;
}

