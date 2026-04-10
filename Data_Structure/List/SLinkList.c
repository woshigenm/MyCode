#include "../Headers/SLinkList.h"
#include <stdio.h>

//初始化静态链表
Status InitList(SLinkList space)
{
	for (int i = 0; i < MAXSIZES - 1; ++i)
		space[i].cur = i + 1;
	space[MAXSIZES - 1].cur = 0;
	return OK;
}

//静态链表结点申请
int Malloc_SSL(SLinkList space)
{
	int j = space[0].cur;
	if (j)	space[0].cur = space[j].cur;
	return j;
}

//返回静态链表长度
int ListLength(SLinkList space)
{
	int j = 0;
	int k = space[MAXSIZES - 1].cur;
	while (k) {
		k = space[k].cur;
		++j;
	}
	return j;
}

//静态链表按位序插入结点
Status ListInsert(SLinkList space, int i, ElemType e)
{
	if (i < 1 || i > ListLength(space) + 1)	return ERROR;
	if (space[0].cur == 0)	return ERROR; // 检查是否有空闲空间

	int k = MAXSIZES - 1;
	for (int j = 1; j <= i - 1; ++j)
		k = space[k].cur;

	int p = Malloc_SSL(space);
	if (!p)	return ERROR;
	space[p].data = e;
	space[p].cur = space[k].cur;
	space[k].cur = p;
	return OK;
}

//静态链表结点释放
void Free_SSL(SLinkList space, int i)
{
	if (i <= 0 || i >= MAXSIZES) return;
	space[i].cur = space[0].cur;
	space[0].cur = i;
}

//静态链表按位序删除结点
Status ListDelete(SLinkList space, int i, ElemType * e)
{
	if (i < 1 || i > ListLength(space)) {
		return ERROR;
	}

	int k = MAXSIZES - 1;
	for (int j = 1; j <= i - 1; ++j)
		k = space[k].cur;

	int p = space[k].cur;
	*e = space[p].data;
	space[k].cur = space[p].cur;
	Free_SSL(space, p);
	return OK;
}

//遍历并打印静态链表所有元素
void ListPrint(SLinkList space)
{
	int k = space[MAXSIZES - 1].cur;
	if (k == 0) {
		printf("链表为空\n");
		return;
	}

	while (k) {
		printf("%d ", space[k].data);
		k = space[k].cur;
	}
	putchar('\n');
}

//获取静态链表L的第i个元素
Status GetStaticElem(SLinkList space, int i, ElemType *e)
{
	if (i < 1 || i > ListLength(space))	return ERROR;
	int k = space[MAXSIZES - 1].cur;
	for (int j = 1;  j < i; j++)	k = space[k].cur;
	*e = space[k].data;
	return OK;
}

//查找元素 e 首次出现的位置（返回下标，0 表示不存在）
int LocateElem(SLinkList space, ElemType e)
{
	int k = space[MAXSIZES - 1].cur;

	int j = 1;
	while (k) {
		if (space[k].data == e)	return j;
		k = space[k].cur;
		++j;
	}

	return 0;
}

//清空静态链表
void ClearList(SLinkList L)
{
	int k = L[MAXSIZES - 1].cur;
	while (k != 0) {
		int next = L[k].cur;
		Free_SSL(L, k);
		k = next;
	}

	L[MAXSIZES - 1].cur = 0;
}

