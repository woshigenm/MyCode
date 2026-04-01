#include "../Headers/SingleLinkList.h"
#include <stdio.h>

Node* splitList(Node* L1, int x);

int main() {
	int arr1[] = {1, 4, 3, 2, 5, 2}, x = 5;
	int len_arr1 = sizeof(arr1) / sizeof(*arr1);
	LinkList L1;
	InitList(&L1);

	for (int i = 1; i <= len_arr1; i++) {
		ListInsert(L1, i, arr1[i - 1]);
	}

	ListPrint(L1);
	L1->next = splitList(L1, x);
	ListPrint(L1);

	DestroyList(&L1);
	return 0;
}

//将链表L1分割为 小于x 的节点在前，大于等于x 的节点在后
Node* splitList(Node* L1, int x) {
	Node *smallHead = (Node*)malloc(sizeof(Node));
	Node *largeHead = (Node*)malloc(sizeof(Node));
	Node *small = smallHead;
	Node *large = largeHead;

	Node *cur = L1->next;
	while (cur != NULL) {
		if (cur->data < x) {
			small->next = cur;
			small = small->next;
		} else {
			large->next = cur;
			large = large->next;
		}
		cur = cur->next;
	}

	large->next = NULL;
	small->next = largeHead->next;

	Node* res = smallHead->next;
	free(smallHead);
	free(largeHead);

	return res;
}

