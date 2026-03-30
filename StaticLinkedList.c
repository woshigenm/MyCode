#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZES 100
typedef struct SNode {
	ElemType data;
	int cur;
} SNode, StaticLinkList[MAXSIZES];

//初始化静态链表
Status InitList(StaticLinkList space) {
	for (int i = 0; i < MAXSIZES - 1; ++i)
		space[i].cur = i + 1;
	space[MAXSIZES - 1].cur = 0;
	return OK;
}

//静态链表结点申请
int Malloc_SSL(StaticLinkList space) {
	int j = space[0].cur;
	if (j)	space[0].cur = space[j].cur;
	return j;
}

//返回静态链表长度
int ListLength(StaticLinkList space) {
	int j = 0;
	int k = space[MAXSIZES - 1].cur;
	while (k) {
		k = space[k].cur;
		++j;
	}
	return j;
}

//静态链表按位序插入结点
Status ListInsert(StaticLinkList space, int i, ElemType e) {
	int k = MAXSIZES - 1;
	if (i < 1 || i > ListLength(space) + 1)	return ERROR;
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
void Free_SSL(StaticLinkList space, int i) {
	space[i].cur = space[0].cur;
	space[0].cur = i;
}

//静态链表按位序删除结点
Status ListDelete(StaticLinkList space, int i, ElemType * e) {
	int k = MAXSIZES - 1, p;
	if (i < 1 || i > ListLength(space))	return ERROR;
	for (int j = 1; j <= i - 1; ++j)
		k = space[k].cur;

	p = space[k].cur;
	*e = space[p].data;
	space[k].cur = space[p].cur;
	Free_SSL(space, p);
	return OK;
}

//遍历并打印静态链表所有元素
void ListPrint(StaticLinkList space) {
	int k = space[MAXSIZES - 1].cur;
	for (int i = 1; i <= ListLength(space); ++i) {
		printf("%p -> %d\n", &space[k], space[k].data);
		k = space[k].cur;
	}

	putchar('\n');
}

//获取静态链表L的第i个元素
Status GetStaticElem(StaticLinkList space, int i, ElemType *e) {
	if (i < 1 || i > ListLength(space))	return ERROR;
	int k = space[MAXSIZES - 1].cur;
	for (int j = 1;  j < i; j++)	k = space[k].cur;
	*e = space[k].data;
	return OK;
}

// 查找元素 e 首次出现的位置（返回下标，0 表示不存在）
int LocateElem(StaticLinkList space, ElemType e) {
	int k = space[MAXSIZES - 1].cur;
	int j = 1;
	while (k) {
		if (space[k].data == e)	return j;
		k = space[k].cur;
		++j;
	}

	return 0;
}

void ClearList(StaticLinkList L) {
	InitList(L);
}

int main() {
	StaticLinkList S;
	InitList(S);
	ElemType e;

	// 插入测试
	ListInsert(S, 1, 1);
	ListInsert(S, 2, 2);
	ListInsert(S, 3, 3);
	ListInsert(S, 4, 4);
	printf("插入后链表：");
	ListPrint(S);  // 输出：1 2 3 4

	// 删除测试
	ListDelete(S, 1, &e);
	printf("删除第1个元素(%d)后：", e);
	ListPrint(S);  // 输出：2 3 4

	// 查找测试
	int pos = LocateElem(S, 3);
	printf("元素3的位置：%d\n", pos);  // 输出：2

	// 清空测试
	ClearList(S);
	printf("清空后链表：");
	ListPrint(S);  // 无输出
	printf("查找元素4的位置：%d\n", LocateElem(S, 4));  // 输出：0

	return 0;
}
