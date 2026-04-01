#include "../Headers/CSLinkList.h"
#include <stdio.h>

//初始化循环单链表
Status InitList(CSLinkList * L) {
	if (NULL == L)	return ERROR;
	*L = (CSLinkList)malloc(sizeof(CSNode));
	if (NULL == *L)	return ERROR;
	(*L)->next = *L;
	return OK;
}

//单链表位序 i 插入 e 值, n 个元素 1 <= i <= n + 1, i = n + 1 时为尾插
Status ListInsert(CSLinkList L, int i, ElemType e) {
	if (NULL == L)	return ERROR;

	int j = 0;
	CSNode * cur = L;
	while (j < i - 1 && cur->next != L) {
		cur = cur->next;
		++j;
	}

	if (j > i - 1)	return ERROR;

	CSNode * NewNode = (CSNode *)malloc(sizeof(CSNode));
	if (NULL == NewNode)	return ERROR;
	NewNode->data = e;
	NewNode->next = cur->next;
	cur->next = NewNode;
	return OK;
}

//循环单链表是否为空
bool IsEmpty(CSLinkList L) {
	if (NULL == L)	return true;
	return L->next == L;
}

//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(CSLinkList L, int i, ElemType * e) {
	if (NULL == L || IsEmpty(L))	return ERROR;
	int j = 0;
	CSNode * cur = L;
	while (j < i - 1 && cur->next != L) {
		cur = cur->next;
		++j;
	}
	if (cur->next == L || j > i - 1)	return ERROR;
	CSNode * tmp = cur->next;
	*e = tmp->data;
	cur->next = tmp->next;
	free(tmp);
	return OK;
}

//返回循环单链表长度
int ListLength(CSLinkList L) {
	if (NULL == L)	return 0;
	CSNode * cur = L->next;
	int j = 0;
	while (cur != L) {
		cur = cur->next;
		++j;
	}
	return j;
}

//遍历单链表
void ListPrint(CSLinkList  L) {
	if (NULL == L) {
		printf("链表未初始化！\n");
		return;
	}

	if (IsEmpty(L)) {
		printf("链表为空！\n");
		return;
	}

	CSNode * cur = L->next;
	while (cur != L) {
		printf("%d \n", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

//清空循环单链表
Status ClearList(CSLinkList L) {
	if (NULL == L)	return ERROR;
	CSNode * cur = L->next, *tmp;
	while (cur != L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	L->next = L;
	return OK;
}

//销毁循环单链表
Status DestroyList(CSLinkList * L) {
	if (NULL == *L || NULL == L)	return ERROR;
	CSNode * cur = (*L)->next, *tmp;
	while (cur != *L) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(*L);
	*L = NULL;
	return OK;
}
