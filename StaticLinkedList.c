#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZES 64
typedef struct SNode {
	ElemType data;
	int cur;
} SNode, StaticLinkList[MAXSIZES];

Status InitList(StaticLinkList space);
int Malloc_SSL(StaticLinkList space);
int ListLength(StaticLinkList space);
Status ListInsert(StaticLinkList space, int i, ElemType e);
void Free_SSL(StaticLinkList space, int i);
Status ListDelete(StaticLinkList space, int i, ElemType * e);
void ListPrint(StaticLinkList space);
Status GetStaticElem(StaticLinkList space, int i, ElemType *e);
int LocateElem(StaticLinkList space, ElemType e);
void ClearList(StaticLinkList L);

int main() {
	StaticLinkList S;
	ElemType e;
	int pos;

	printf("=== 静态链表测试 ===\n\n");

	// 1. 初始化测试
	printf("1. 初始化静态链表测试...\n");
	InitList(S);
	printf("初始化后链表长度: %d\n\n", ListLength(S));

	// 2. 插入测试
	printf("2. 插入测试...\n");
	printf("插入元素1, 2, 3, 4, 5\n");
	ListInsert(S, 1, 1);
	ListInsert(S, 2, 2);
	ListInsert(S, 3, 3);
	ListInsert(S, 4, 4);
	ListInsert(S, 5, 5);
	printf("插入后链表：");
	ListPrint(S);
	printf("当前链表长度: %d\n\n", ListLength(S));

	// 3. 按位插入测试
	printf("3. 按位插入测试...\n");
	printf("在第3个位置插入元素99\n");
	ListInsert(S, 3, 99);
	printf("插入后链表：");
	ListPrint(S);
	printf("当前链表长度: %d\n\n", ListLength(S));

	// 4. 获取元素测试
	printf("4. 获取元素测试...\n");
	if (GetStaticElem(S, 2, &e) == OK) {
		printf("第2个元素: %d\n", e);
	}
	if (GetStaticElem(S, 3, &e) == OK) {
		printf("第3个元素: %d\n", e);
	}
	printf("尝试获取第10个元素: ");
	if (GetStaticElem(S, 10, &e) == ERROR) {
		printf("位置无效！\n");
	}
	printf("\n");

	// 5. 查找测试
	printf("5. 查找测试...\n");
	pos = LocateElem(S, 99);
	printf("元素99的位置: %d\n", pos);
	pos = LocateElem(S, 4);
	printf("元素4的位置: %d\n", pos);
	pos = LocateElem(S, 100);
	printf("元素100的位置: %d (不存在)\n\n", pos);

	// 6. 删除测试
	printf("6. 删除测试...\n");
	printf("删除第3个元素\n");
	if (ListDelete(S, 3, &e) == OK) {
		printf("删除的元素: %d\n", e);
	}
	printf("删除后链表：");
	ListPrint(S);
	printf("当前链表长度: %d\n\n", ListLength(S));

	// 7. 空间状态查看
	printf("7. 空间状态查看...\n");
	ListPrint(S);
	printf("\n");

	// 8. 边界测试
	printf("8. 边界测试...\n");
	printf("尝试在位置0插入元素: ");
	if (ListInsert(S, 0, 100) == ERROR) {
		printf("位置无效！\n");
	}
	printf("尝试在超出长度的位置插入元素: ");
	if (ListInsert(S, ListLength(S) + 2, 100) == ERROR) {
		printf("位置无效！\n");
	}
	printf("尝试删除位置0的元素: ");
	if (ListDelete(S, 0, &e) == ERROR) {
		printf("位置无效！\n");
	}
	printf("尝试删除超出长度的元素: ");
	if (ListDelete(S, ListLength(S) + 1, &e) == ERROR) {
		printf("位置无效！\n");
	}
	printf("\n");

	// 9. 填满空间测试
	printf("9. 填满空间测试...\n");
	int count = ListLength(S);
	printf("当前已有元素: %d\n", count);
	printf("空闲空间: %d\n", MAXSIZES - 2 - count);  // 注意：第一个位置(0)用于空闲链表
	for (int i = 1; i <= MAXSIZES - 2 - count; i++) {
		ListInsert(S, ListLength(S) + 1, i + 100);
	}
	printf("填充后链表：");
	ListPrint(S);
	printf("当前链表长度: %d\n", ListLength(S));
	printf("尝试继续插入元素: ");
	if (ListInsert(S, ListLength(S) + 1, 999) == ERROR) {
		printf("空间已满，插入失败！\n");
	}
	printf("\n");

	// 10. 清空测试
	printf("10. 清空链表测试...\n");
	ClearList(S);
	printf("清空后链表：");
	ListPrint(S);
	printf("清空后链表长度: %d\n", ListLength(S));
	printf("查找元素4的位置: %d\n", LocateElem(S, 4));

	// 11. 清空后插入测试
	printf("\n11. 清空后插入测试...\n");
	ListInsert(S, 1, 999);
	ListInsert(S, 1, 888);
	printf("插入后链表：");
	ListPrint(S);
	printf("当前链表长度: %d\n", ListLength(S));

	printf("\n=== 测试完成 ===\n");
	return 0;
}

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
void Free_SSL(StaticLinkList space, int i) {
	if (i <= 0 || i >= MAXSIZES) return;
	space[i].cur = space[0].cur;
	space[0].cur = i;
}

//静态链表按位序删除结点
Status ListDelete(StaticLinkList space, int i, ElemType * e) {
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
void ListPrint(StaticLinkList space) {
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
Status GetStaticElem(StaticLinkList space, int i, ElemType *e) {
	if (i < 1 || i > ListLength(space))	return ERROR;
	int k = space[MAXSIZES - 1].cur;
	for (int j = 1;  j < i; j++)	k = space[k].cur;
	*e = space[k].data;
	return OK;
}

//查找元素 e 首次出现的位置（返回下标，0 表示不存在）
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

//清空静态链表
void ClearList(StaticLinkList L) {
	int k = L[MAXSIZES - 1].cur;
	while (k != 0) {
		int next = L[k].cur;
		Free_SSL(L, k);
		k = next;
	}

	L[MAXSIZES - 1].cur = 0;
}

