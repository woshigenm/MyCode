#include "SingleLinkList.h"
#include <stdio.h>

Node * SplitList(LinkList L, int x);

int main() {
	LinkList L;
	int array[] = {1, 4, 3, 2, 5, 2}, x = 3;
	int size = sizeof(array) / sizeof(*array);
	InitList(&L);

	for (int i = 0; i < size; ++i)
		ListInsert(L, i + 1, array[i]);

	ListPrint(L);
	SplitList(L, x);
	ListPrint(L);

	DestroyList(&L);
	return 0;
}

Node * SplitList(LinkList L, int x) {
	if (NULL ==	L || NULL == L->next)	return NULL;
	Node *SmallHead = (Node *)malloc(sizeof(Node));
	Node *LargeHead = (Node *)malloc(sizeof(Node));
	Node *Small = SmallHead, *Large = LargeHead;
	Node * cur = L->next;
	while (cur) {
		if (cur->data < x) {
			Small->next = cur;
			Small = cur;
		} else {
			Large->next = cur;
			Large = cur;
		}
		cur = cur->next;
	}

	Node *tmp = SmallHead;
	Small->next = LargeHead->next;
	Large->next = NULL;

	free(SmallHead);
	free(LargeHead);

	return tmp->next;
}
