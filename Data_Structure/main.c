#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
typedef enum {
	OK, ERROR
} Status;

typedef enum {
	LINK, THREAD
} TAG_TYPE;

typedef struct BTNode {
	ElemType data;
	struct BTNode* lchild, * rchild;
	TAG_TYPE ltag, rtag;
} BTNode, * BTree;

typedef BTNode* ElemType_S;
typedef struct StackNode {
	ElemType_S data;
	struct StackNode* next;
} StackNode, * LinkStack;

Status InitStack(LinkStack* S);
Status Push(LinkStack S, ElemType_S e);
bool IsEmpty(LinkStack S);
Status Pop(LinkStack S, ElemType_S* e);
Status GetTop(LinkStack S, ElemType_S* e);
Status DestroyStack(LinkStack* S);

Status InitBTree(BTree* Root)
{
	if (NULL == Root)	return ERROR;
	*Root = NULL;
	return OK;
}

void PreOrderCreate(BTree* Root)
{
	char input;
	scanf(" %c", &input);
	if (input == '#') {
		*Root = NULL;
	} else {
		*Root = (BTNode*)malloc(sizeof(BTNode));
		if (*Root == NULL)	exit(EXIT_FAILURE);
		(*Root)->data = input;
		(*Root)->ltag = (*Root)->rtag = LINK;
		(*Root)->lchild = (*Root)->rchild = NULL;
		PreOrderCreate(&(*Root)->lchild);
		PreOrderCreate(&(*Root)->rchild);
	}
}

void PreOrderTravel(BTree Root)
{
	if (Root) {
		putchar(Root->data);
		putchar(' ');
		PreOrderTravel(Root->lchild);
		PreOrderTravel(Root->rchild);
	}
}

void InOrderTravel(BTree Root)
{
	if (Root) {
		InOrderTravel(Root->lchild);
		putchar(Root->data);
		putchar(' ');
		InOrderTravel(Root->rchild);
	}
}

void PostOrderTravel(BTree Root)
{
	if (Root) {
		PostOrderTravel(Root->lchild);
		PostOrderTravel(Root->rchild);
		putchar(Root->data);
		putchar(' ');
	}
}

int Depth(BTree Root)
{
	if (Root == NULL)	return 0;
	int left = Depth(Root->lchild);
	int right = Depth(Root->rchild);
	return (left > right ? left : right) + 1;
}

int LeafCount(BTree Root)
{
	if (Root == NULL)
		return 0;
	if (Root->lchild == NULL && Root->rchild == NULL)
		return 1;
	return LeafCount(Root->lchild) + LeafCount(Root->rchild);
}

int NodeCount(BTree Root)
{
	if (Root == NULL)	return 0;
	return	NodeCount(Root->lchild) + NodeCount(Root->rchild) + 1;
}

int DegreeOne(BTree Root)
{
	if (Root == NULL)	return 0;
	if ((Root->lchild == NULL && Root->rchild != NULL) ||
	    (Root->lchild != NULL && Root->rchild == NULL))
		return 1;
	return	DegreeOne(Root->lchild) + DegreeOne(Root->rchild);
}

static void DestroyBTree(BTree* Root)
{
	if (*Root == NULL)	return;
	DestroyBTree(&(*Root)->lchild);
	DestroyBTree(&(*Root)->rchild);
	free(*Root);
	*Root = NULL;
}

Status ClearBTree(BTree* Root)
{
	if (Root == NULL)	return ERROR;
	DestroyBTree(Root);
	return OK;
}

BTNode* pre_ref = NULL;
void InThreading(BTree Root)
{
	if (Root != NULL) {
		InThreading(Root->lchild);

		if (Root->lchild == NULL) {
			Root->lchild = pre_ref;
			Root->ltag = THREAD;
		}

		if (pre_ref != NULL && pre_ref->rchild == NULL) {
			pre_ref->rchild = Root;
			pre_ref->rtag = THREAD;
		}

		pre_ref = Root;
		InThreading(Root->rchild);
	}
}

void CopyTree(BTree* Destination, BTree Source)
{
	if (Source) {
		*Destination = (BTNode*)malloc(sizeof(BTNode));
		if (*Destination == NULL)	exit(EXIT_FAILURE);

		(*Destination)->data = Source->data;
		(*Destination)->ltag = Source->ltag;
		(*Destination)->rtag = Source->rtag;
		(*Destination)->lchild = (*Destination)->rchild = NULL;

		CopyTree(&(*Destination)->lchild, Source->lchild);
		CopyTree(&(*Destination)->rchild, Source->rchild);
	} else {
		*Destination = NULL;
	}
}

void InTreadingTravel(BTree Root)
{
	BTNode* p = Root;
	while (p != NULL) {
		while (p->ltag == LINK) {
			p = p->lchild;
		}

		putchar(p->data);
		putchar(' ');
		while (p->rtag == THREAD) {
			p = p->rchild;
			putchar(p->data);
			putchar(' ');
		}

		p = p->rchild;
	}
}

void DestroyInTreading(BTree* Root)
{
	BTNode* p = *Root;
	while (p) {
		while (p->ltag == LINK)	p = p->lchild;

		BTNode* temp = p->rchild;
		TAG_TYPE saved_rtag = p->rtag;

		free(p);
		p = temp;

		while (saved_rtag == THREAD) {
			saved_rtag = p->rtag;
			temp = p->rchild;
			free(p);
			p = temp;
		}
	}
	*Root = NULL;
}

void PreOrderTravel_Stack(BTree Root)
{
	if (Root == NULL)	return;
	LinkStack S;
	BTNode* tmp = NULL;
	InitStack(&S);
	Push(S, Root);

	while (!IsEmpty(S)) {
		Pop(S, &tmp);
		printf("%c ", tmp->data);

		if (tmp->rchild != NULL) {
			Push(S, tmp->rchild);
		}

		if (tmp->lchild != NULL) {
			Push(S, tmp->lchild);
		}
	}

	DestroyStack(&S);
}

void InOrderTravel_Stack(BTree Root)
{
	if (Root == NULL)	return;
	LinkStack S;
	InitStack(&S);

	BTNode *Cur_Root = Root;
	while (Cur_Root != NULL || !IsEmpty(S)) {
		if (Cur_Root != NULL) {
			Push(S, Cur_Root);
			Cur_Root = Cur_Root->lchild;
		} else {
			Pop(S, &Cur_Root);
			printf("%c ", Cur_Root->data);
			Cur_Root = Cur_Root->rchild;
		}
	}

	DestroyStack(&S);
}

void PostOrderTravel_TwoStack(BTree Root)
{
	if (Root == NULL)	return;

	LinkStack S1, S2;
	BTNode* tmp = NULL;

	InitStack(&S1);
	InitStack(&S2);

	Push(S1, Root);
	while (!IsEmpty(S1)) {
		Pop(S1, &tmp);
		Push(S2, tmp);

		if (tmp->lchild != NULL) {
			Push(S1, tmp->lchild);
		}
		if (tmp->rchild != NULL) {
			Push(S1, tmp->rchild);
		}
	}

	while (!IsEmpty(S2)) {
		Pop(S2, &tmp);
		printf("%c ", tmp->data);
	}

	DestroyStack(&S1);
	DestroyStack(&S2);
}

void PostOrderTravel_Stack(BTree Root)
{
	if (Root == NULL)	return;
	LinkStack S;
	InitStack(&S);

	BTNode *Cur_Root = Root;
	while (!IsEmpty(S)) {
		
	}

	DestroyStack(&S);
}


//A B D # # E # # C # #
//A # C # D # #
//A B C # # # #
int main()
{
	BTree Root1;
	InitBTree(&Root1);

	PreOrderCreate(&Root1);
	PostOrderTravel(Root1);
	putchar('\n');
	PostOrderTravel_Stack(Root1);

	return 0;
}

Status InitStack(LinkStack* S)
{
	if (S == NULL)	return ERROR;
	*S = (StackNode*)malloc(sizeof(StackNode));
	if (*S == NULL) return ERROR;
	(*S)->next = NULL;
	return OK;
}

//入栈元素
Status Push(LinkStack S, ElemType_S e)
{
	if (S == NULL)	return ERROR;
	StackNode* cur = (StackNode*)malloc(sizeof(StackNode));
	if (NULL == cur)	return ERROR;
	cur->data = e;
	cur->next = S->next;
	S->next = cur;
	return OK;
}

//判断栈是否为空
bool IsEmpty(LinkStack S)
{
	if (NULL == S)	return true;
	return S->next == NULL;
}

//弹出元素
Status Pop(LinkStack S, ElemType_S* e)
{
	if (S == NULL || IsEmpty(S))	return ERROR;
	StackNode* cur = S->next;
	*e = cur->data;
	S->next = cur->next;
	free(cur);
	return OK;
}

//返回栈顶元素
Status GetTop(LinkStack S, ElemType_S* e)
{
	if (S == NULL || IsEmpty(S))	return ERROR;
	*e = S->next->data;
	return OK;
}

//销毁链栈
Status DestroyStack(LinkStack* S)
{
	if (S == NULL || *S == NULL)	return ERROR;
	StackNode* cur = (*S)->next, * p;
	while (cur) {
		p = cur->next;
		free(cur);
		cur = p;
	}
	free(*S);
	*S = NULL;
	return OK;
}

