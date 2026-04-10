#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	Elemtype data;
	struct QueueNode* next;
} QueueNode;

Status Josephus(int n, int m);

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		Josephus(n, m);
	}

	return 0;
}

Status Josephus(int n, int m)
{
	if (n <= 0 || m <= 0) {
		return ERROR;
	}

	QueueNode* tmp = NULL, * head = NULL, * tail = NULL;
	for (int i = 1; i <= n; ++i) {
		QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
		if (NULL == node) {
			while (head) {
				tmp = head;
				head = head->next;
				free(tmp);
			}
			return ERROR;
		}

		node->data = i;
		node->next = NULL;
		if (NULL == head) {
			head = node;
		} else {
			tail->next = node;
		}
		tail = node;
	}

	int* result = (int*)malloc(sizeof(int) * n);
	if (NULL == result) {
		while (head) {
			tmp = head;
			head = head->next;
			free(tmp);
		}
		return ERROR;
	}

	int j = 0;
	while (head != tail) {
		for (int i = 1; i < m; i++) {
			tmp = head->next;
			head->next = tail->next;
			tail->next = head;
			tail = head;
			head = tmp;
		}

		tmp = head;
		result[j++] = head->data;
		head = head->next;
		free(tmp);
	}

	result[j] = head->data;
	free(head);

	for (int i = 0; i < n; ++i)
		printf("%d ", result[i]);

	putchar('\n');
	free(result);

	return OK;
}
