#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

// 双向循环链表节点结构
typedef struct CDNode {
	ElemType data;
	struct CDNode *prior;
	struct CDNode *next;
} CDNode, *CDLinkList;

// 函数声明
Status InitList(CDLinkList *L);
Status GetElem(CDLinkList L, int i, ElemType *e);
Status ListInsert(CDLinkList L, int i, ElemType e);
Status ListDelete(CDLinkList L, int i, ElemType *e);
int ListLength(CDLinkList L);
bool ListEmpty(CDLinkList L);
void PrintList(CDLinkList L);
Status ClearList(CDLinkList L);
Status DestroyList(CDLinkList *L);
void PrintListReverse(CDLinkList L);
Status Change(CDLinkList L, CDNode * p);

int main()
{
	CDLinkList L;
	printf("1. 初始化双向链表\n");
	InitList(&L);

	printf("2. 插入10个元素(1-10)\n");
	for (int i = 1; i <= 10; ++i) {
		ListInsert(L, i, i);
	}
	printf("链表长度：%d\n", ListLength(L));
	printf("链表内容：");
	PrintList(L);
	PrintListReverse(L);

	printf("\n3. 获取第5个元素\n");
	ElemType e;
	if (GetElem(L, 5, &e) == OK) {
		printf("第5个元素是：%d\n", e);
	}

	printf("\n4. 删除前5个元素\n");
	for (int i = 1; i <= 5; ++i) {
		ElemType deleted;
		if (ListDelete(L, 1, &deleted) == OK) {
			printf("删除的元素：%d，当前链表：", deleted);
			PrintList(L);
		}
	}
	printf("链表长度：%d\n", ListLength(L));

	printf("\n5. 在位置2插入元素100\n");
	ListInsert(L, 2, 100);
	printf("链表内容：");
	PrintList(L);
	PrintListReverse(L);

	printf("\n6. 删除位置3的元素\n");
	ElemType deleted;
	if (ListDelete(L, 3, &deleted) == OK) {
		printf("删除的元素：%d\n", deleted);
	}
	printf("链表内容：");
	PrintList(L);

	printf("\n7. 清空链表\n");
	ClearList(L);
	printf("链表是否为空：%s\n", ListEmpty(L) ? "是" : "否");
	printf("链表内容：");
	PrintList(L);

	printf("\n8. 销毁链表\n");
	DestroyList(&L);
	printf("链表指针：%p\n", (void*)L);
	return 0;
}

Status InitList(CDLinkList * L)
{
	if (NULL == L)  return ERROR;
	*L = (CDNode *)malloc(sizeof(CDNode));
	if (NULL == *L) return ERROR;

	(*L)->next = (*L)->prior = *L;
	return OK;
}

Status GetElem(CDLinkList L, int i, ElemType * e)
{
	if (NULL == L)  return ERROR;
	if (i < 1)      return ERROR;

	int j = 1;
	CDNode *cur = L->next;

	while (j < i && cur != L) {
		cur = cur->next;
		j++;
	}

	if (cur == L) return ERROR;
	*e = cur->data;
	return OK;
}

Status ListInsert(CDLinkList L, int i, ElemType e)
{
	if (NULL == L)  return ERROR;
	if (i < 1)      return ERROR;

	int j = 0;
	CDNode *cur = L;

	// 循环终止条件：回到头节点
	while (j < i - 1 && cur->next != L) {
		cur = cur->next;
		j++;
	}

	CDNode *new_node = (CDNode *)malloc(sizeof(CDNode));
	if (NULL == new_node) return ERROR;
	new_node->data = e;

	new_node->next = cur->next;
	new_node->prior = cur;
	cur->next->prior = new_node;
	cur->next = new_node;

	return OK;
}

Status ListDelete(CDLinkList L, int i, ElemType * e)
{
	if (NULL == L)  return ERROR;
	if (i < 1)      return ERROR;

	int j = 0;
	CDNode *cur = L;

	while (j < i && cur->next != L) {
		cur = cur->next;
		j++;
	}

	if (cur == L) return ERROR;
	*e = cur->data;

	cur->prior->next = cur->next;
	cur->next->prior = cur->prior;
	free(cur);

	return OK;
}

Status ClearList(CDLinkList L)
{
	if (NULL == L)  return ERROR;

	CDNode *cur = L->next;
	CDNode *tmp;

	while (cur != L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	L->next = L;
	L->prior = L;
	return OK;
}

Status DestroyList(CDLinkList * L)
{
	if (NULL == L || NULL == *L) return ERROR;

	CDNode *cur = (*L)->next;
	CDNode *tmp;

	while (cur != *L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	free(*L);
	*L = NULL;
	return OK;
}

void PrintList(CDLinkList L)
{
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (L->next == L) {
		printf("空链表\n");
		return;
	}

	CDNode *cur = L->next;
	while (cur != L) {
		printf("%d -> %p\n", cur->data, cur);
		cur = cur->next;
	}

	putchar('\n');
}

void PrintListReverse(CDLinkList L)
{
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (L->next == L) {
		printf("空链表\n");
		return;
	}

	CDNode *tail = L->prior;
	while (tail != L) {
		printf("%d -> %p\n", tail->data, tail);
		tail = tail->prior;
	}

	putchar('\n');
}

int ListLength(CDLinkList L)
{
	if (NULL == L) return 0;

	int len = 0;
	CDNode *cur = L->next;
	while (cur != L) {
		len++;
		cur = cur->next;
	}
	return len;
}

bool ListEmpty(CDLinkList L)
{
	if (NULL == L) return true;
	return L->next == L;
}

Status Change(CDLinkList L, CDNode * p)
{
	if (NULL == L || L == p || p->prior == L) {
		return ERROR;
	}

	CDNode *q = p->prior;
	q->prior->next = p;
	p->next->prior  = q;

	p->prior = q->prior;
	q->next = p->next;

	p->next = q;
	q->prior = p;

	return OK;
}

