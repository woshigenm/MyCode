#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Status;
enum { ERROR, OK };
typedef struct Node {
	ElemType data;
	struct Node * next;
} Node, *LinkList;

//初始化单链表
Status InitList(LinkList * L) {
	*L = (struct Node*)malloc(sizeof(Node));
	(*L)->next = NULL;
	return OK;
}

//单链表位序 i 插入 e 值， n 个元素 0 <= i <= length, i = length 时为尾插
Status ListInsert(LinkList L, int i, ElemType e) {
	Node * cur = L; //如果 cur=L->next 会导致位序为1的节点插入失败
	int j = 0;
	while (cur && j < i) {
		cur = cur->next;
		++j;
	}
	if (!cur || j > i)	return ERROR; //i值不合法，cur == NULL 时 i 值大于 length, j > i 时，i 为负值
	Node * s = (Node *)malloc(sizeof(Node));
	s->data = e;
	s->next = cur->next;
	cur->next = s;
	return OK;
}

//遍历单链表
void ListPrint(LinkList L) {
	Node * cur = L->next;
	while (cur) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

//销毁链表
Status DestroyList(LinkList * L) {
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

//链表合并
void Merge(LinkList LA, LinkList LB, LinkList * LC) {
	Node * i = LA->next;
	Node * j = LB->next;
	int k = 0;
	while (i && j) {
		if (i->data < j->data) {
			ListInsert(*LC, k++, i->data);
			i = i->next;
		} else if (i->data > j->data) {
			ListInsert(*LC, k++, j->data);
			j = j->next;
		} else {
			ListInsert(*LC, k++, i->data);
			//ListInsert(*LC, k++, j->data);
			j = j->next;
			i = i->next;
		}
	}

	while (i) {
		ListInsert(*LC, k++, i->data);
		i = i->next;
	}

	while (j) {
		ListInsert(*LC, k++, j->data);
		j = j->next;
	}
}

int main() {
	LinkList L1, L2, L3;
	InitList(&L1);
	InitList(&L2);
	InitList(&L3);

	ListInsert(L1, 0, 3);
	ListInsert(L1, 1, 5);
	ListInsert(L1, 2, 8);

	ListInsert(L2, 0, 0);
	ListInsert(L2, 1, 3);
	ListInsert(L2, 2, 7);
	ListInsert(L2, 3, 8);
	ListInsert(L2, 4, 9);
	ListInsert(L2, 5, 12);

	Merge(L1, L2, &L3);
	ListPrint(L3);

	DestroyList(&L1);
	DestroyList(&L2);
	DestroyList(&L3);
	return 0;
}
