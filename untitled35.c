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
Status ListDelete(LinkList L, int i, ElemType * e);
int ListLength(LinkList L);
bool ListEmpty(LinkList L);
void ListPrint(LinkList  L);
Status DestroyList(LinkList * L);
Node* splitList(Node* L1, int x);

int main() {
	int arr1[] = {1, 4, 3, 2, 5, 2}, x = 5;
	int len_arr1 = sizeof(arr1) / sizeof(*arr1);
	LinkList L1;
	InitList(&L1);

	for (int i = 1; i <= len_arr1; i++) {
		ListInsert(L1, i, arr1[i - 1]);
	}

	ListPrint(L1);
	L1->next = splitList(L1, x);
	ListPrint(L1);
	
	DestroyList(&L1);
	return 0;
}

//将链表L1分割为 小于x 的节点在前，大于等于x 的节点在后
Node* splitList(Node* L1, int x) {
	Node *smallHead = (Node*)malloc(sizeof(Node));
	Node *largeHead = (Node*)malloc(sizeof(Node));
	Node *small = smallHead;
	Node *large = largeHead;

	Node *cur = L1->next;
	while (cur != NULL) {
		if (cur->data < x) {
			small->next = cur;
			small = small->next;
		} else {
			large->next = cur;
			large = large->next;
		}
		cur = cur->next;
	}

	large->next = NULL;
	small->next = largeHead->next;

	Node* res = smallHead->next;
	free(smallHead);
	free(largeHead);

	return res;
}

//初始化单链表
Status InitList(LinkList * L) {
	*L = (struct Node*)malloc(sizeof(Node));
	if (*L == NULL)	return ERROR;
	(*L)->next = NULL;
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
