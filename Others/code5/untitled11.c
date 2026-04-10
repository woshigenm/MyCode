#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
	ElemType data;
	struct Node *next;
} Node, *LinkList;

void PrintInfo()
{
	printf("链表为空\n");
}

void initList(LinkList L)
{
	L = (LinkList)malloc(sizeof(LinkList));
	if (!L)	return;
	L->next = NULL;
	L->data = 0;
}

Node * get_tail(Node * list)
{
	if (list == NULL) {
		PrintInfo();
		return NULL;
	}

	Node * Cur = list;
	while (Cur->next != NULL) {
		Cur = Cur->next;
	}

	return Cur;
}

Node * InsertTail(Node * list, ElemType e)
{
	if (list == NULL) {
		PrintInfo();
		return NULL;
	}

	Node * Cur_tail = get_tail(list);
	Node * NNode = (Node*)malloc(sizeof(Node));
	NNode->data = e;
	NNode->next = Cur_tail->next;
	Cur_tail->next = NNode;

	return NNode;
}

void Print(Node * list)
{
	if (list == NULL) {
		PrintInfo();
		return;
	}

	Node * Cur = list;
	while (NULL != Cur) {
		printf("%p %d\n", Cur, Cur->data);
		Cur = Cur->next;
	}

	putchar('\n');
}

Node * insertHead(Node * list, ElemType e)
{
	if (list == NULL) {
		PrintInfo();
		return NULL;
	}

	Node * NNode = (Node*)malloc(sizeof(Node));
	NNode->data = e;
	NNode->next = list->next;
	list->next = NNode;

	return NNode;
}


Node * insertNode(Node * list, int pos, ElemType target)
{
	if (list == NULL) {
		PrintInfo();
		return NULL;
	}

	Node * Cur = list;
	for (int i = 1; i <= pos - 1; i++) {
		Cur = Cur->next;
		if (Cur == NULL)
			return NULL;
	}

	Node * NNode = (Node*)malloc(sizeof(Node));
	NNode->data = target;
	NNode->next = Cur->next;
	Cur->next = NNode;

	return NNode;
}

int deleteNode(Node * list, int pos)
{
	if (list == NULL) {
		PrintInfo();
		return 0;
	}

	if (pos < 1) {
		printf("删除位置有误\n");
		return 0;
	}

	Node * Cur = list;
	for (int i = 1; i <= pos - 1; i++) {
		Cur = Cur->next;
		if (Cur == NULL)
			return 0;
	}

	if (Cur->next == NULL) {
		printf("删除位置有误\n");
		return 0;
	}

	Node * temp = Cur->next;
	Cur->next = temp->next;
	free(temp);

	return 1;
}

int lisLength(Node *list)
{
	if (list == NULL) {
		PrintInfo();
		return 0;
	}

	int length = 0;
	Node * Cur = list;
	while (Cur != NULL) {
		length++;
		Cur = Cur->next;
	}

	return length;
}

int destoryList(Node **list)
{
	if (list == NULL) {
		PrintInfo();
		return 0;
	}

	Node * Cur = *list;
	Node * temp;
	while (Cur != NULL) {
		temp = Cur->next;
		free(Cur);
		Cur = temp;
	}

	*list = NULL;

	return 1;
}

void reserveList(Node **list)
{
	//原链表顺序为A→B→C→D，反转后变为D→C→B→A。
//	Node *list = initList();
//	Node *arr[SIZE];
//	arr[0] = list;
//	for (int i = 1; i < SIZE; i++) {
//		arr[i] = InsertTail(list, i);
//	}
//
//	Print(list);
//
//	int i;
//	for (i = SIZE - 1; i >= 1; i--) {
//		arr[i]->next = arr[i - 1];
//	}
//
//	arr[i]->next = NULL;
//	list = arr[SIZE - 1];
}

#define SIZE 100

int main()
{
	LinkList list;
	initList(list);

	for (int i = 1; i <= SIZE; i++)
		InsertTail(list, i);

	Print(list);

	Node * fast = list->next;
	Node * slow = list->next;

	int k = 2;
	for (int i = 1; i <= k; i++)
		fast = fast->next;

	while (fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}

	printf("%d\n", slow->data);
	return 0;
}

