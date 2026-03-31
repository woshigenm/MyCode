#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

typedef struct Node {
	ElemType data;
	struct Node * next;
} Node, *LinkList;

Status InitList(LinkList * L);
Status GetElem(LinkList L, int i, ElemType * e);
Status GetElemAd(LinkList L, int i, Node ** e);
Status LocateElem(LinkList L, ElemType e, Node ** ep);
Status ListInsert(LinkList L, int i, ElemType e);
Status ListDelete(LinkList L, int i, ElemType * e);
Status CreateList_H(LinkList * L, int n);
Status CreateList_R(LinkList * L, int n);
int ListLength(LinkList L);
bool ListEmpty(LinkList L);
void ListPrint(LinkList  L);
Status PriorElem(LinkList L, ElemType cur_e, Node ** pre_e);
Status NextElem(LinkList L, ElemType cur_e, Node ** next_e);
Status ClearList(LinkList L);
Status DestroyList(LinkList * L);
Status PriorInsert(LinkList L, int i, ElemType cur_e);
Status NextInsert(LinkList L, int i, ElemType cur_e);
Status ReverseList(LinkList L);
Status MergeList(LinkList L1, LinkList L2);
Status RightRotate(LinkList L, int n);
bool HasCycle(LinkList L);
Node * FindCycle(LinkList L);
Status HandleCycle(LinkList L);

// 辅助函数：打印测试结果
void printTestResult(const char* testName, bool passed) {
	printf("测试 [%s]: %s\n", testName, passed ? "通过" : "失败");
}

// 辅助函数：打印状态测试结果
void printStatusTestResult(const char* testName, Status expected, Status actual) {
	printf("测试 [%s]: %s (预期状态: %s, 实际状态: %s)\n",
	       testName,
	       expected == actual ? "通过" : "失败",
	       expected == OK ? "OK" : "ERROR",
	       actual == OK ? "OK" : "ERROR");
}

// 辅助函数：打印布尔测试结果
void printBoolTestResult(const char* testName, bool expected, bool actual) {
	printf("测试 [%s]: %s (预期: %s, 实际: %s)\n",
	       testName,
	       expected == actual ? "通过" : "失败",
	       expected ? "true" : "false",
	       actual ? "true" : "false");
}

// 辅助函数：打印整数值测试结果
void printIntTestResult(const char* testName, int expected, int actual) {
	printf("测试 [%s]: %s (预期: %d, 实际: %d)\n",
	       testName,
	       expected == actual ? "通过" : "失败",
	       expected, actual);
}

//辅助函数：创建有环链表
Status CreateCycleList(LinkList *L, int n, bool hasCycle) {
	Status status = CreateList_R(L, n);
	if (status != OK) return ERROR;

	if (hasCycle && n > 1) {
		Node *last = (*L)->next;
		Node *middle = NULL;
		int i = 1;

		while (last && last->next) {
			if (i == n / 2) {
				middle = last;
			}
			last = last->next;
			i++;
		}

		if (middle && last) {
			last->next = middle;  // 创建环
		}
	}
	return OK;
}

int main() {
	printf("=======================\n");
	printf("链表功能全面测试\n");
	printf("=======================\n\n");

	LinkList L = NULL;
	ElemType e = 0;
	Node *node = NULL;
	Status status = OK;

	// 1. 测试初始化
	printf("1. 测试初始化功能\n");
	printf("   -----------------\n");
	status = InitList(&L);
	printStatusTestResult("初始化链表", OK, status);
	printBoolTestResult("链表是否为空", true, ListEmpty(L));
	printIntTestResult("链表长度应为0", 0, ListLength(L));
	printf("\n");

	// 2. 测试插入功能
	printf("2. 测试插入功能\n");
	printf("   -------------\n");

	// 测试在空表中插入
	status = ListInsert(L, 1, 10);
	printStatusTestResult("在空表中插入第一个元素", OK, status);
	printIntTestResult("插入后长度", 1, ListLength(L));

	// 测试正常插入
	ListInsert(L, 1, 20);  // 20->10
	ListInsert(L, 2, 30);  // 20->30->10
	ListInsert(L, 4, 40);  // 20->30->10->40
	printf("当前链表内容:\n");
	ListPrint(L);

	// 测试越界插入
	status = ListInsert(L, 6, 50);
	printStatusTestResult("越界插入应该失败", ERROR, status);

	// 测试负索引插入
	status = ListInsert(L, -1, 50);
	printStatusTestResult("负索引插入应该失败", ERROR, status);
	printf("\n");

	// 3. 测试取值和查找功能
	printf("3. 测试取值和查找功能\n");
	printf("   -------------------\n");

	// 测试GetElem
	status = GetElem(L, 2, &e);
	printStatusTestResult("获取第二个元素", OK, status);
	if (status == OK) {
		printIntTestResult("第二个元素值", 30, e);
	}

	status = GetElem(L, 5, &e);
	printStatusTestResult("越界取值应该失败", ERROR, status);

	// 测试LocateElem
	status = LocateElem(L, 10, &node);
	printStatusTestResult("查找值为10的节点", OK, status);
	if (status == OK && node != NULL) {
		printIntTestResult("找到节点的值", 10, node->data);
	}

	status = LocateElem(L, 99, &node);
	printStatusTestResult("查找不存在的值应该失败", ERROR, status);
	printf("\n");

	// 4. 测试删除功能
	printf("4. 测试删除功能\n");
	printf("   -------------\n");

	// 删除中间元素
	ElemType deleted = 0;
	status = ListDelete(L, 2, &deleted);
	printStatusTestResult("删除第二个元素", OK, status);
	if (status == OK) {
		printIntTestResult("被删除的元素值", 30, deleted);
	}

	printf("删除后链表内容:\n");
	ListPrint(L);

	// 删除不存在的元素
	status = ListDelete(L, 5, &deleted);
	printStatusTestResult("越界删除应该失败", ERROR, status);
	printf("\n");

	// 5. 测试前驱和后继
	printf("5. 测试前驱和后继功能\n");
	printf("   -------------------\n");

	// 重建链表为简单结构
	ClearList(L);
	for (int i = 1; i <= 5; i++) {
		ListInsert(L, i, i * 10);
	}
	printf("重建链表为: ");
	ListPrint(L);

	// 测试前驱
	Node *pre = NULL;
	status = PriorElem(L, 30, &pre);
	printStatusTestResult("查找30的前驱", OK, status);
	if (status == OK && pre != NULL) {
		printIntTestResult("前驱节点值", 20, pre->data);
	}

	status = PriorElem(L, 10, &pre);
	printStatusTestResult("查找第一个元素的前驱应该失败", ERROR, status);

	// 测试后继
	Node *next = NULL;
	status = NextElem(L, 30, &next);
	printStatusTestResult("查找30的后继", OK, status);
	if (status == OK && next != NULL) {
		printIntTestResult("后继节点值", 40, next->data);
	}

	status = NextElem(L, 50, &next);
	printStatusTestResult("查找最后一个元素的后继应该失败", ERROR, status);
	printf("\n");

	// 6. 测试前插法和后插法
	printf("6. 测试前插法和后插法\n");
	printf("   --------------------\n");

	LinkList LH = NULL, LR = NULL;

	// 前插法
	status = CreateList_H(&LH, 5);
	printStatusTestResult("前插法创建链表", OK, status);
	printf("前插法结果(应该是逆序): ");
	ListPrint(LH);

	// 后插法
	status = CreateList_R(&LR, 5);
	printStatusTestResult("后插法创建链表", OK, status);
	printf("后插法结果(应该是正序): ");
	ListPrint(LR);

	// 清理测试链表
	DestroyList(&LH);
	DestroyList(&LR);
	printf("\n");

	// 7. 测试反转链表
	printf("7. 测试反转链表\n");
	printf("   -------------\n");

	printf("反转前链表: ");
	ListPrint(L);

	status = ReverseList(L);
	printStatusTestResult("反转链表", OK, status);

	printf("反转后链表: ");
	ListPrint(L);

	// 再次反转恢复
	ReverseList(L);
	printf("\n");

	// 8. 测试合并链表
	printf("8. 测试合并链表\n");
	printf("   -------------\n");

	LinkList L1 = NULL, L2 = NULL;
	InitList(&L1);
	InitList(&L2);

	// 创建两个有序链表
	for (int i = 1; i <= 5; i++) {
		ListInsert(L1, i, i * 2);      // 2, 4, 6, 8, 10
	}
	for (int i = 1; i <= 4; i++) {
		ListInsert(L2, i, i * 3);      // 3, 6, 9, 12
	}

	printf("链表L1: ");
	ListPrint(L1);
	printf("链表L2: ");
	ListPrint(L2);

	status = MergeList(L1, L2);
	printStatusTestResult("合并两个有序链表", OK, status);

	printf("合并后L1: ");
	ListPrint(L1);
	printf("合并后L2应为空: ");
	ListPrint(L2);

	DestroyList(&L1);
	DestroyList(&L2);
	printf("\n");

	// 9. 测试向右旋转
	printf("9. 测试向右旋转\n");
	printf("   -------------\n");

	ClearList(L);
	for (int i = 1; i <= 6; i++) {
		ListInsert(L, i, i);
	}

	printf("旋转前链表: ");
	ListPrint(L);

	status = RightRotate(L, 2);
	printStatusTestResult("向右旋转2位", OK, status);

	printf("旋转后链表: ");
	ListPrint(L);

	printf("\n");

	// 10. 测试环检测
	printf("10. 测试环检测和处理\n");
	printf("    -----------------\n");

	// 创建无环链表
	LinkList L_no_cycle = NULL;
	CreateList_R(&L_no_cycle, 5);
	bool hasCycle = HasCycle(L_no_cycle);
	printBoolTestResult("无环链表检测", false, hasCycle);

	// 创建有环链表
	LinkList L_cycle = NULL;
	Status cycleStatus = CreateCycleList(&L_cycle, 6, true);
	if (cycleStatus == OK) {
		hasCycle = HasCycle(L_cycle);
		printBoolTestResult("有环链表检测", true, hasCycle);

		// 查找环的入口
		Node *cycleEntry = FindCycle(L_cycle);
		printf("环入口节点值: %d\n", cycleEntry ? cycleEntry->data : -1);

		// 处理环
		status = HandleCycle(L_cycle);
		printStatusTestResult("处理链表环", OK, status);

		hasCycle = HasCycle(L_cycle);
		printBoolTestResult("处理环后检测", false, hasCycle);

		printf("处理环后链表: ");
		ListPrint(L_cycle);
	}

	DestroyList(&L_no_cycle);
	if (L_cycle) {
		// 确保链表无环后再销毁
		if (HasCycle(L_cycle)) {
			HandleCycle(L_cycle);
		}
		DestroyList(&L_cycle);
	}
	printf("\n");

	// 11. 测试前插入和后插入
	printf("11. 测试前插入和后插入\n");
	printf("     ------------------\n");

	ClearList(L);
	for (int i = 1; i <= 3; i++) {
		ListInsert(L, i, i * 10);
	}
	printf("原始链表: ");
	ListPrint(L);

	status = PriorInsert(L, 2, 25);
	printStatusTestResult("在第2个节点前插入25", OK, status);
	printf("插入后链表: ");
	ListPrint(L);

	status = NextInsert(L, 3, 35);
	printStatusTestResult("在第3个节点后插入35", OK, status);
	printf("插入后链表: ");
	ListPrint(L);

	printf("\n");

	// 12. 测试边界情况
	printf("12. 测试边界情况\n");
	printf("     -------------\n");

	// 测试空表
	LinkList L_empty = NULL;
	InitList(&L_empty);
	printBoolTestResult("空表判断", true, ListEmpty(L_empty));

	// 测试各种非法操作
	status = GetElem(L_empty, 1, &e);
	printStatusTestResult("从空表获取元素应该失败", ERROR, status);

	status = ListDelete(L_empty, 1, &e);
	printStatusTestResult("从空表删除元素应该失败", ERROR, status);

	status = ReverseList(L_empty);
	printStatusTestResult("反转空表", OK, status);

	// 测试只有一个元素的链表
	LinkList L_single = NULL;
	InitList(&L_single);
	ListInsert(L_single, 1, 100);
	printIntTestResult("单元素链表长度", 1, ListLength(L_single));

	status = ReverseList(L_single);
	printStatusTestResult("反转单元素链表", OK, status);

	DestroyList(&L_single);
	printf("\n");

	// 13. 清理所有链表
	printf("13. 清理和销毁链表\n");
	printf("     ---------------\n");

	// 清空L
	status = ClearList(L);
	printStatusTestResult("清空链表L", OK, status);

	status = DestroyList(&L);
	printStatusTestResult("销毁链表L", OK, status);

	status = DestroyList(&L_empty);
	printStatusTestResult("销毁空链表", OK, status);

	// 测试销毁已销毁的链表
	status = DestroyList(&L);
	printStatusTestResult("重复销毁应该失败", ERROR, status);

	printf("\n14. 额外边界测试\n");
	printf("    ---------------\n");

// 测试单节点链表的各种操作
	LinkList L_single2 = NULL;
	InitList(&L_single2);
	ListInsert(L_single2, 1, 999);
	printf("单节点链表: ");
	ListPrint(L_single2);

// 测试删除单节点
	ElemType val = 0;
	status = ListDelete(L_single2, 1, &val);
	printf("删除单节点: 值=%d, 状态=%s\n", val, status == OK ? "成功" : "失败");
	printf("删除后链表: ");
	ListPrint(L_single2);

// 测试在空表上删除
	status = ListDelete(L_single2, 1, &val);
	printf("在空表上删除: 状态=%s\n", status == OK ? "成功" : "失败");

	DestroyList(&L_single2);

// 测试大数旋转
	LinkList L_large = NULL;
	InitList(&L_large);
	for (int i = 1; i <= 10; i++) {
		ListInsert(L_large, i, i);
	}
	printf("旋转前: ");
	ListPrint(L_large);

// 测试旋转次数大于链表长度
	RightRotate(L_large, 15);
	printf("旋转15次(长度10): ");
	ListPrint(L_large);

	DestroyList(&L_large);

	printf("\n=======================\n");
	printf("测试完成！\n");
	printf("=======================\n");

	return 0;
}

//初始化单链表
Status InitList(LinkList * L) {
	*L = (struct Node*)malloc(sizeof(Node));
	if (NULL == *L)	return ERROR;
	(*L)->next = NULL;
	return OK;
}

//单链表位序取值
Status GetElem(LinkList L, int i, ElemType * e) {
	if (NULL == e || NULL == L) return ERROR;
	Node * cur = L->next;
	int j = 1;
	while (cur && j < i) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur || j > i)	return ERROR; //i值不合法，cur == NULL 时i值过大, j > i 时，i 为负值
	*e = cur->data;
	return OK;
}

//单链表位序取结点
Status GetElemAd(LinkList L, int i, Node ** e) {
	if (NULL == e || NULL == L) return ERROR;
	Node * cur = L->next;
	int j = 1;
	while (cur && j < i) {
		cur = cur->next;
		++j;
	}

	if (!cur || j > i)	return ERROR; //i值不合法，cur == NULL 时i值过大, j > i 时，i 为负值
	*e = cur;
	return OK;
}

//单链表查找 e 值
Status LocateElem(LinkList L, ElemType e, Node ** ep) {
	if (NULL == L) return ERROR;
	Node * cur = L->next;
	while (cur && cur->data != e) {
		cur = cur->next;
	}

	if (NULL == cur) {
		*ep = NULL;
		return ERROR;  // 未找到
	}

	*ep = cur;
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

//单链表位序 i 删除，返回删除值到e， n 个元素 1 <= i <= n
Status ListDelete(LinkList L, int i, ElemType * e) {
	if (NULL == L)	return ERROR;
	Node * cur = L; //如果 cur=L->next 会导致位序为1的节点删除失败
	int j = 0;
	while (cur->next && j < i - 1) {
		cur = cur->next;
		++j;
	}

	if (NULL == cur->next || j > i - 1)	return ERROR;

	Node * q = cur->next;
	*e = q->data;
	cur->next = q->next;
	free(q);
	return OK;
}

//前插法建立链表
Status CreateList_H(LinkList * L, int n) {
	if (NULL == L)	return ERROR;
	Node * cur;
	*L = (Node*)malloc(sizeof(Node));
	if (NULL == *L)	return ERROR;
	(*L)->next = NULL;
	for (int i = 1; i <= n; ++i) {
		cur = (Node*)malloc(sizeof(Node));
		if (NULL == cur)	{
			cur = (*L)->next;
			while (cur) {
				Node * tmp = cur->next;
				free(cur);
				cur = tmp;
			}
			free(*L);
			*L = NULL;
			return ERROR;
		}
		cur->data = i;
		cur->next = (*L)->next;
		(*L)->next = cur;
	}
	return OK;
}

//后插法建立链表
Status CreateList_R(LinkList * L, int n) {
	if (NULL == L)	return ERROR;
	Node * cur, *p;
	*L = (Node*)malloc(sizeof(Node));
	if (NULL == *L)	return ERROR;
	p = *L;
	for (int i = 1; i <= n; ++i) {
		cur = (Node*)malloc(sizeof(Node));
		if (NULL == cur)	return ERROR;
		cur->data = i;
		p->next = cur;
		p = cur;
	}

	p->next = NULL;
	return OK;
}

//返回单链表长度
int ListLength(LinkList L) {
	if (NULL == L)	return 0;
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
	if (NULL == L)	return true;
	return L->next == NULL;
}

//遍历单链表
void ListPrint(LinkList  L) {
	if (NULL == L) {
		printf("链表未初始化\n");
		return;
	}

	if (ListEmpty(L)) {
		printf("空链表\n");
		return;
	}

	Node * cur = L->next;
	while (cur) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	putchar('\n');
}

//重置线性表为空表
Status ClearList(LinkList  L) {
	if (NULL == L)	return ERROR;
	Node * cur = L->next, *p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur = p;
	}
	L->next = NULL;
	return OK;
}

//查找cur_e 的前驱结点，返回 pre_e
Status PriorElem(LinkList L, ElemType cur_e, Node ** pre_e) {
	if (NULL == L || NULL == pre_e)	return ERROR;
	*pre_e = NULL;
	if (ListEmpty(L) || L->next->data == cur_e) return ERROR;
	Node *pre = L;
	Node *cur = L->next;
	while (cur && cur->data != cur_e) {
		pre = cur;
		cur = cur->next;
	}
	if (NULL == cur)	return ERROR;
	*pre_e = pre;
	return OK;
}

//查找cur_e 的后驱结点，返回 next_e
Status NextElem(LinkList L, ElemType cur_e, Node ** next_e) {
	if (NULL == L || NULL == next_e)	return ERROR;
	*next_e = NULL;
	Node * cur = NULL;
	if (LocateElem(L, cur_e, &cur) == OK)	{
		*next_e = cur->next;
		if (cur->next == NULL)
			return ERROR;
		return OK;
	}

	return ERROR;
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

//在第i个结点之后插入以cur_e为值的结点
Status NextInsert(LinkList L, int i, ElemType cur_e) {
	if (NULL == L)	return ERROR;

	Node * cur = NULL;
	if (GetElemAd(L, i, &cur) != OK)	return ERROR;
	Node * p = (Node *)malloc(sizeof(Node));
	if (NULL == p)	return ERROR;

	p->data = cur_e;
	p->next = cur->next;
	cur->next = p;

	return OK;
}

//在第i个结点之前插入以cur_e为值的结点
Status PriorInsert(LinkList L, int i, ElemType cur_e) {
	if (NULL == L)	return ERROR;
	Node * p = (Node *)malloc(sizeof(Node));
	if (NULL == p)	return ERROR;
	p->data = cur_e;

	if (i == 1) {
		p->next = L->next;
		L->next = p;
	} else {
		Node * cur = NULL;
		if (ERROR == GetElemAd(L, i - 1, &cur))	return ERROR;

		p->next = cur->next;
		cur->next = p;
	}
	return OK;
}

//逆转单链表
Status ReverseList(LinkList L) {
	if (NULL == L)	return ERROR;

	Node *cur = L->next, *pre = NULL, *next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	L->next = pre;
	return OK;
}

//合并两个单链表
Status MergeList(LinkList L1, LinkList L2) {
	if (L1 == NULL || L2 == NULL)	return ERROR;
	Node * p1 = L1, *p2 = L2->next, *tmp = NULL;
	while (p1->next && p2) {
		if (p2->data < p1->next->data) {
			tmp = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p2 = tmp;
		} else if (p1->next->data < p2->data) {
			p1 = p1->next;
		} else {
			tmp = p2;
			p2 = p2->next;
			free(tmp);
		}
	}

	if (p2) {
		p1->next = p2; // 将 L2 剩余节点接在 L1 最后
	}

	L2->next = NULL;// L2 头结点清空，避免野指针
	return OK;
}

//单链表向右旋转 k 个位置
Status RightRotate(LinkList L, int n) {
	if (L == NULL || NULL == L->next)	return ERROR;

	Node *q, *p, *tmp;
	q = L;
	tmp = L;
	p = L->next;

	int len = ListLength(L);
	int k = len - n % len;
	if (k == len)	return OK;

	while (k-- && p) {
		q = q->next;
		p = p->next;
	}

	tmp = p;
	q->next = NULL;

	while (p->next) {
		p = p->next;
	}

	p->next = L->next;
	L->next = tmp;

	return OK;
}

//判断链表是否有环
bool HasCycle(LinkList L) {
	if (NULL == L || NULL == L->next)   return false;
	Node * slow = L->next, *fast = slow->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)    return true;
	}

	return false;
}

//返回环的入点
Node * FindCycle(LinkList L) {
	if (NULL == L || NULL == L->next)   return NULL;
	Node * slow = L->next, *fast = slow->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow) {
			slow = L;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}

			return slow;
		}
	}

	return NULL;
}

//解除环
Status HandleCycle(LinkList L) {
	if (NULL == L || L->next == NULL)	return ERROR;
	Node * slow = L->next, *fast = slow->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow) {
			slow = L;
			while (slow->next != fast->next) {
				slow = slow->next;
				fast = fast->next;
			}

			fast->next = NULL;
			return OK;
		}
	}

	return ERROR;
}

