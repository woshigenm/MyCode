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
void ListPrint(CSLinkList  L);

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

		L->size--;

		if (cur == L->rear) {
			L->rear = prev;
		}

		cur = cur->next;
		if (cur == L->head) {
			prev = cur;
			cur = cur->next;
		}

		printf("%d\n", tmp->data);
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
	if (NULL == (*L)->rear)	return ERROR;
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


void ListPrint(CSLinkList  L)
{
	if (NULL == L) {
		printf("链表未初始化！\n");
		return;
	}

	if (IsEmpty(L)) {
		printf("链表为空！\n");
		return;
	}

	CSNode* cur = L->head->next;
	while (cur != L->head) {
		printf("%d \n", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

Status ListInsert(CSLinkList L, int i, ElemType e)
{
	if (NULL == L)	return ERROR;

	int j = 0;
	CSNode* cur = L->head->next;
	while (j < i - 1 && cur->next != L->head) {
		cur = cur->next;
		++j;
	}

	if (j > i - 1)	return ERROR;

	CSNode* NewNode = (CSNode*)malloc(sizeof(CSNode));
	if (NULL == NewNode)	return ERROR;
	NewNode->data = e;
	NewNode->next = cur->next;
	cur->next = NewNode;

	if (i == L->size + 1 || L->size == 0) {
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
	*L = NULL;
	return OK;
}

