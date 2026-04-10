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
Status InitList(LinkList * L)
{
	*L = (struct Node*)malloc(sizeof(Node));
	(*L)->next = NULL;
	return OK;
}

//单链表位序 i 插入 e 值， n 个元素 0 <= i <= length, i = length 时为尾插
Status ListInsert(LinkList L, int i, ElemType e)
{
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
void ListPrint(LinkList L)
{
	Node * cur = L->next;
	while (cur) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

//销毁链表
Status DestroyList(LinkList * L)
{
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

int main()
{
	LinkList L;
	InitList(&L);
	ListInsert(L, 0, 114);
	ListInsert(L, 1, 514);
	ListInsert(L, 2, 1919);
	ListInsert(L, 3, 810);
	ListInsert(L, 4, 66);
	ListPrint(L);
	DestroyList(&L);

	return 0;
}
