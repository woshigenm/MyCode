#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef enum {
	OK,
	ERROR
} Status;

typedef struct Node {
	ElemType data;
	struct Node *next;
} Node, *LinkList;

Status InitList(LinkList *L);
Status ListInsert(LinkList L, int i, ElemType e);
void ListPrint(LinkList L);
Status DestroyList(LinkList *L);
Status LinkListDedpu(LinkList L1);

int main() {
	int arr1[] = {1, 1, 1, 2, 2, 3};
	int len_arr1 = sizeof(arr1) / sizeof(*arr1);
	LinkList L1;
	InitList(&L1);

	for (int i = 1; i <= len_arr1; i++) {
		ListInsert(L1, i, arr1[i - 1]);
	}
	ListPrint(L1);

	LinkListDedpu(L1);
	ListPrint(L1);

	DestroyList(&L1);
	return 0;
}

//初始化单链表
Status InitList(LinkList * L) {
	if (NULL == L)	return ERROR;
	*L = (struct Node*)malloc(sizeof(Node));
	if (NULL == *L)	return ERROR;
	(*L)->next = NULL;
	return OK;
}

//单链表位序 i 插入 e 值， n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(LinkList L, int i, ElemType e) {
	if (NULL == L)	return ERROR;
	Node * cur = L; //如果 cur=L->next 会导致位序为1的节点插入失败
	int j = 0;
	while (cur && j < i - 1) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur || j > i - 1)	return ERROR; //i值不合法，cur == NULL 时i值过大, j > i 时，i 为负值

	Node * s = (Node *)malloc(sizeof(Node));
	if (NULL == s)	return ERROR;
	s->data = e;
	s->next = cur->next;
	cur->next = s;
	return OK;
}

//遍历单链表
void ListPrint(LinkList  L) {
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (NULL == L->next) {
		printf("空链表\n");
		return;
	}

	Node * cur = L->next;
	while (cur) {
		printf("%d -> %p\n", cur->data, cur);
		cur = cur->next;
	}
	putchar('\n');
}

//销毁线性表
Status DestroyList(LinkList * L) {
	if (NULL == L || NULL == *L)	return ERROR;
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

Status LinkListDedpu(LinkList L1) {
	if (NULL == L1 || NULL == L1->next)	return ERROR;

	Node * slow = L1, *fast = L1->next,*tmp;
	while (fast->next) {
		if (fast->next->data == fast->data) {
			slow->next = fast->next;
			tmp = fast->next;
			free(fast);
			fast = tmp;
		} else {
			slow = slow->next;
			fast = fast->next;
		}
	}
	
	return OK;
}

