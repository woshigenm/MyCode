#include "../Headers/SingleLinkList.h"
#include <stdio.h>

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
	int len = 0;
	while (cur) {
		cur = cur->next;
		++len;
	}
	return len;
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
	Node * cur = L->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
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
	Node * cur = (*L)->next, *tmp;
	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
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

