#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct Node {
	ElemType data;
	struct Node * next;
} Node, *LinkList;

Status InitList(LinkList * L);
Status ListInsert(LinkList L, int i, ElemType e);
bool IsEmpty(LinkList L);
Status ListDelete(LinkList L, int i, ElemType * e);
int ListLength(LinkList L);
void ListPrint(LinkList  L);
Status ClearList(LinkList L);
Status DestroyList(LinkList * L);

int main() {
	LinkList L;
	ElemType e;

	printf("测试1：初始化\n");
	InitList(&L);
	ListPrint(L);
	printf("长度：%d\n\n", ListLength(L));

	printf("测试2：插入\n");
	ListInsert(L, 1, 10);
	ListInsert(L, 2, 20);
	ListInsert(L, 2, 15);
	ListInsert(L, 4, 25);
	printf("长度：%d\n", ListLength(L));
	ListPrint(L);

	printf("测试3：非法插入\n");
	if (ListInsert(L, 10, 99) == ERROR)
		printf("插入失败\n\n");

	printf("测试4：删除\n");
	ListDelete(L, 1, &e);
	printf("删除：%d\n", e);
	ListDelete(L, 3, &e);
	printf("删除：%d\n", e);
	ListDelete(L, 2, &e);
	printf("删除：%d\n", e);
	printf("长度：%d\n", ListLength(L));
	ListPrint(L);

	printf("测试5：非法删除\n");
	if (ListDelete(L, 2, &e) == ERROR)
		printf("删除失败\n\n");

	printf("测试6：清空\n");
	ListInsert(L, 1, 100);
	ListInsert(L, 2, 200);
	ListPrint(L);
	ClearList(L);
	ListPrint(L);
	printf("长度：%d\n\n", ListLength(L));

	printf("测试7：销毁\n");
	DestroyList(&L);
	if (NULL == L)
		printf("销毁成功\n");

	return 0;
}

//初始化循环单链表
Status InitList(LinkList * L) {
	if (NULL == L)	return ERROR;
	*L = (LinkList)malloc(sizeof(Node));
	if (NULL == *L)	return ERROR;
	(*L)->next = *L;
	return OK;
}

//单链表位序 i 插入 e 值, n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(LinkList L, int i, ElemType e) {
	if (NULL == L)	return ERROR;

	int j = 0;
	Node * cur = L;
	while (j < i - 1 && cur->next != L) {
		cur = cur->next;
		++j;
	}

	if (j > i - 1)	return ERROR;

	Node * NewNode = (Node *)malloc(sizeof(Node));
	if (NULL == NewNode)	return ERROR;
	NewNode->data = e;
	NewNode->next = cur->next;
	cur->next = NewNode;
	return OK;
}

//循环单链表是否为空
bool IsEmpty(LinkList L) {
	if (NULL == L)	return true;
	return L->next == L;
}

//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(LinkList L, int i, ElemType * e) {
	if (NULL == L || IsEmpty(L))	return ERROR;
	int j = 0;
	Node * cur = L;
	while (j < i - 1 && cur->next != L) {
		cur = cur->next;
		++j;
	}
	if (cur->next == L || j > i - 1)	return ERROR;
	Node * tmp = cur->next;
	*e = tmp->data;
	cur->next = tmp->next;
	free(tmp);
	return OK;
}

//返回循环单链表长度
int ListLength(LinkList L) {
	if (NULL == L)	return 0;
	Node * cur = L->next;
	int j = 0;
	while (cur != L) {
		cur = cur->next;
		++j;
	}
	return j;
}

//遍历单链表
void ListPrint(LinkList  L) {
	if (NULL == L) {
		printf("链表未初始化！\n");
		return;
	}

	if (IsEmpty(L)) {
		printf("链表为空！\n");
		return;
	}

	Node * cur = L->next;
	while (cur != L) {
		printf("%d \n", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

//清空循环单链表
Status ClearList(LinkList L) {
	if (NULL == L)	return ERROR;
	Node * cur = L->next, *tmp;
	while (cur != L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	L->next = L;
	return OK;
}

//销毁循环单链表
Status DestroyList(LinkList * L) {
	if (NULL == *L || NULL == L)	return ERROR;
	Node * cur = (*L)->next, *tmp;
	while (cur != *L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(*L);
	*L = NULL;
	return OK;
}
