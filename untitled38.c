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

//初始化单链表
Status InitList(LinkList * L);
//单链表位序取值
Status GetElem(LinkList L, int i, ElemType * e);
//单链表位序 i 插入 e 值， n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(LinkList L, int i, ElemType e);
//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(LinkList L, int i, ElemType * e);
//返回单链表长度
int ListLength(LinkList L);
//返回单链表是否为空表
bool ListEmpty(LinkList L);
//遍历单链表
void ListPrint(LinkList  L);
//销毁线性表
Status DestroyList(LinkList * L);

int main() {
	int arr1[] = {1, 3, 4};
	int arr2[] = {1, 2, 4};
	int len_arr1 = sizeof(arr1) / sizeof(*arr1);
	int len_arr2 = sizeof(arr2) / sizeof(*arr2);
	LinkList L1, L2;
	InitList(&L1);
	InitList(&L2);

	for (int i = 1; i <= len_arr1; i++) {
		ListInsert(L1, i, arr1[i - 1]);
	}

	for (int i = 1; i <= len_arr2; i++) {
		ListInsert(L2, i, arr2[i - 1]);
	}

	ListPrint(L1);
	ListPrint(L2);

	Node * p1 = L1, *p2 = L2->next, *tmp;
	while (p1->next && p2) {
		if (p2->data < p1->next->data) {
			tmp = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p2 = tmp;
		} else if (p1->next->data < p2->data) {
			p1 = p1->next;
		} else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	if (p2) {
		p1->next = p2; // 将 L2 剩余节点接在 L1 最后
	}

	ListPrint(L1);
	L2->next = NULL;

	DestroyList(&L1);
	DestroyList(&L2);

	return 0;
}

//初始化单链表
Status InitList(LinkList * L) {
	*L = (struct Node*)malloc(sizeof(Node));
	if (*L == NULL)	return ERROR;
	(*L)->next = NULL;
	return OK;
}

//单链表位序取值
Status GetElem(LinkList L, int i, ElemType * e) {
	if (!e || !L) return ERROR;
	Node * cur = L->next;
	int j = 1;
	while (cur && j < i) {
		cur = cur->next;
		++j;
	}

	if (!cur || j > i)	return ERROR; //i值不合法，cur == NULL 时i值过大, j > i 时，i 为负值
	*e = cur->data;
	return OK;
}

//单链表位序 i 插入 e 值， n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(LinkList L, int i, ElemType e) {
	if (!L)	return ERROR;
	Node * cur = L; //如果 cur=L->next 会导致位序为1的节点插入失败
	int j = 0;
	while (cur && j < i - 1) {
		cur = cur->next;
		++j;
	}

	if (!cur || j > i - 1)	return ERROR; //i值不合法，cur == NULL 时i值过大, j > i 时，i 为负值

	Node * s = (Node *)malloc(sizeof(Node));
	if (!s)	return ERROR;
	s->data = e;
	s->next = cur->next;
	cur->next = s;
	return OK;
}

//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(LinkList L, int i, ElemType * e) {
	if (!L)	return ERROR;
	Node * cur = L; //如果 cur=L->next 会导致位序为1的节点删除失败
	int j = 0;
	while (cur->next && j < i - 1) {
		cur = cur->next;
		++j;
	}

	if (!cur->next || j > i - 1)	return ERROR;

	Node * q = cur->next;
	*e = q->data;
	cur->next = q->next;
	free(q);
	return OK;
}

//返回单链表长度
int ListLength(LinkList L) {
	if (!L)	return 0;
	Node * cur = L->next;
	int j = 0;
	while (cur) {
		cur = cur->next;
		++j;
	}
	return j;
}

//返回单链表是否为空表
bool ListEmpty(LinkList L) {
	if (L == NULL)	return true;
	return L->next == NULL;
}

//遍历单链表
void ListPrint(LinkList  L) {
	if (!L || ListEmpty(L))	return;
	Node * cur = L->next;
	while (cur) {
		printf("%d -> %p\n", cur->data, cur);
		cur = cur->next;
	}
	putchar('\n');
}

//销毁线性表
Status DestroyList(LinkList * L) {
	if (!L || !(*L))	return ERROR;
	Node * cur = (*L)->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur = p;
	}
	free(*L);
	*L = NULL;
	return OK;
}

