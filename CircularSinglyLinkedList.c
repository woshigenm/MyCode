#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct Node {
	ElemType data;
	struct Node * rear;
} Node, *LinkList;

Status InitList(LinkList * L) {
	if (L == NULL)	return ERROR;
	*L = (LinkList)malloc(sizeof(Node));
	if (*L == NULL)	return ERROR;
	(*L)->rear = *L;
	return OK;
}

//单链表位序 i 插入 e 值， n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(LinkList L, int i, ElemType e) {
	if (L == NULL)	return ERROR;

	int j = 0;
	Node * cur = L;
	while (j < i - 1 && cur->rear != L) {
		cur = cur->rear;
		++j;
	}

	if (j > i - 1)	return ERROR;

	Node * NewNode = (Node *)malloc(sizeof(Node));
	if (NULL == NewNode)	return ERROR;
	NewNode->data = e;
	NewNode->rear = cur->rear;
	cur->rear = NewNode;
	return OK;
}

bool IsEmpty(LinkList L) {
	if (L == NULL)	return true;
	return L->rear == L;
}

//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(LinkList L, int i, ElemType * e) {
	if (L == NULL || IsEmpty(L))	return ERROR;
	int j = 0;
	Node * cur = L;
	while (j < i - 1 && cur->rear != L) {
		cur = cur->rear;
		++j;
	}
	if (cur->rear == L || j > i - 1)	return ERROR;
	Node * p = cur->rear;
	*e = p->data;
	cur->rear = p->rear;
	free(p);
	return OK;
}

int ListLength(LinkList L) {
	if (NULL == L)	return 0;
	Node * cur = L->rear;
	int j = 0;
	while (cur != L) {
		cur = cur->rear;
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

	Node * cur = L->rear;
	while (cur != L) {
		printf("%d -> %p\n", cur->data, cur);
		cur = cur->rear;
	}
	putchar('\n');
}

Status DestroyList(LinkList * L) {
	if (*L == NULL || L == NULL)	return ERROR;
	Node * cur = (*L)->rear, *p;
	while (cur->rear != *L) {
		p = cur->rear;
		free(cur);
		cur = p;
	}
	free(*L);
	*L = NULL;
	return OK;
}

int main() {
	LinkList L;
	ElemType e;

	// 1. 初始化链表
	if (InitList(&L) == OK) {
		printf("链表初始化成功！\n");
	}

	// 2. 插入节点（测试头插、中间插、尾插）
	ListInsert(L, 1, 10);  // 第1位插入10（头插）
	ListInsert(L, 2, 20);  // 第2位插入20（尾插）
	ListInsert(L, 2, 15);  // 第2位插入15（中间插）
	printf("插入后链表长度：%d\n", ListLength(L));  // 预期：3
	ListPrint(L);          // 预期：10 -> 15 -> 20

	// 3. 删除节点（测试头删、中间删、尾删）
	ListDelete(L, 1, &e);  // 删除第1位，e=10
	printf("删除的值：%d\n", e);
	ListDelete(L, 2, &e);  // 删除第2位（原20），e=20
	printf("删除的值：%d\n", e);
	printf("删除后链表长度：%d\n", ListLength(L));  // 预期：1
	ListPrint(L);          // 预期：15

	// 4. 测试删除不存在的位置
	if (ListDelete(L, 2, &e) == ERROR) {
		printf("删除失败：位置超出范围\n");
	}

	// 5. 清空后打印
	ListDelete(L, 1, &e);
	ListPrint(L);          // 预期：链表为空
	return 0;
}
