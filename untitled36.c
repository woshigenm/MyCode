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
//右移单链表
Status RightList(LinkList L, int n);
//右移单链表
void RotateK(Node* head, int k);
//右移单链表
Status Roate(LinkList L, int j);

int main() {
	int array1[] = {1, 2, 3, 4};
	int SIZE = sizeof(array1) / sizeof(array1[0]);
	LinkList L1, L2;
	InitList(&L1);
	InitList(&L2);

	for (int i = 0; i < SIZE; ++i) {
		ListInsert(L1, i + 1, array1[i]);
		ListInsert(L2, i + 1, array1[i]);
	}

	Roate(L1, 5);
	ListPrint(L1);
	RightList(L2, 5);
	ListPrint(L2);

	
	DestroyList(&L1);
	DestroyList(&L2);
	return 0;
}

//向右旋转
Status Roate(LinkList L, int j) {
	if (L == NULL || L->next == NULL)	return ERROR;
	int n = 1;
	Node * tail = L->next;
	while (tail->next) {
		tail = tail->next;
		n++;
	}

	int movement = j % n;
	if (movement == 0)	return OK;
	movement = n - movement;
	tail->next = L->next;

	while (movement--) {
		tail = tail->next;
	}

	L->next = tail->next;
	tail->next = NULL;
	return OK;
}

//向右旋转
Status RightList(LinkList L, int n) {
	if (L == NULL || L->next == NULL)	return ERROR;

	Node *fast, *slow;
	fast = L->next;
	slow = L->next;
	int len = n % ListLength(L);
	if (len == 0) return OK;
	for (int i = 0; i < len && fast; ++i) {
		fast = fast->next;
	}

	while (fast->next) {
		fast = fast->next;
		slow = slow->next;
	}

	fast->next = L->next;
	L->next = slow->next;
	slow->next = NULL;
	return OK;
}

//向右旋转
void RotateK(Node* head, int k) {
	if (head == NULL || head->next == NULL) {
		return;
	}

	Node* slow = head->next;
	Node* fast = head->next;
	int i;
	for (i = 0; i < k && fast; ++i) { //前移k步
		fast = fast->next;
	}

	if (i < k) { //判断k是否已超出链表长度
		return;
	}

	while (fast->next != NULL) {
		slow = slow->next;
		fast = fast->next;
	}

	Node* tmp = slow;
	slow = slow->next;
	tmp->next = NULL;
	fast->next = head->next;
	head->next = slow;
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

