#include "../Headers/SingleLinkList.h"
#include <stdio.h>

Status RightList(LinkList L, int n);
Status Roate(LinkList L, int j);
void RotateK(Node* head, int k);

int main()
{
	int array1[] = {1, 2, 3, 4};
	int SIZE = sizeof(array1) / sizeof(array1[0]);
	LinkList L1, L2;
	InitList(&L1);
	InitList(&L2);

	for (int i = 0; i < SIZE; ++i) {
		ListInsert(L1, i + 1, array1[i]);
		ListInsert(L2, i + 1, array1[i]);
	}

	Roate(L1, 5);
	ListPrint(L1);
	RightList(L2, 5);
	ListPrint(L2);


	DestroyList(&L1);
	DestroyList(&L2);

	return 0;
}

//向右旋转
Status Roate(LinkList L, int j)
{
	if (L == NULL || L->next == NULL)	return ERROR;
	int n = 1;
	Node * tail = L->next;
	while (tail->next) {
		tail = tail->next;
		n++;
	}

	int movement = j % n;
	if (movement == 0)	return OK;
	movement = n - movement;
	tail->next = L->next;

	while (movement--) {
		tail = tail->next;
	}

	L->next = tail->next;
	tail->next = NULL;
	return OK;
}

//向右旋转
Status RightList(LinkList L, int n)
{
	if (L == NULL || L->next == NULL)	return ERROR;

	Node *fast, *slow;
	fast = L->next;
	slow = L->next;
	int len = n % ListLength(L);
	if (len == 0) return OK;
	for (int i = 0; i < len && fast; ++i) {
		fast = fast->next;
	}

	while (fast->next) {
		fast = fast->next;
		slow = slow->next;
	}

	fast->next = L->next;
	L->next = slow->next;
	slow->next = NULL;
	return OK;
}

//向右旋转
void RotateK(Node* head, int k)
{
	if (head == NULL || head->next == NULL) {
		return;
	}

	Node* slow = head->next;
	Node* fast = head->next;
	int i;
	for (i = 0; i < k && fast; ++i) { //前移k步
		fast = fast->next;
	}

	if (i < k) { //判断k是否已超出链表长度
		return;
	}

	while (fast->next != NULL) {
		slow = slow->next;
		fast = fast->next;
	}

	Node* tmp = slow;
	slow = slow->next;
	tmp->next = NULL;
	fast->next = head->next;
	head->next = slow;
}

