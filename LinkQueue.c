#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	Elemtype data;
	struct QueueNode * next;
} QueueNode;

typedef struct LinkQueue {
	struct QueueNode * front;
	struct QueueNode * rear;
	int size;
} LinkQueue;

Status InitLinkQueue(LinkQueue ** Q) {
	if (NULL == Q)	return ERROR;
	*Q = (LinkQueue *)malloc(sizeof(LinkQueue));
	if (NULL == *Q)	return ERROR;
	(*Q)->front = (*Q)->rear = NULL;
	(*Q)->size = 0;
	return OK;
}

bool IsEmpty(LinkQueue * Q) {
	return Q == NULL || Q->front == NULL || Q->rear == NULL;
}

Status EnQueue(LinkQueue * Q, Elemtype e) {
	if (Q == NULL)	return ERROR;
	QueueNode * NewNode = (QueueNode *)malloc(sizeof(QueueNode));
	if (NewNode == NULL)	return ERROR;

	NewNode->data = e;
	NewNode->next = NULL;

	if (IsEmpty(Q)) {
		Q->front = NewNode;
	} else {
		Q->rear->next = NewNode;
	}

	Q->rear	= NewNode;
	Q->size++;
	return OK;
}

Status DeQueue(LinkQueue * Q, Elemtype * e) {
	if (Q == NULL || IsEmpty(Q))	return ERROR;
	QueueNode * p = Q->front;
	*e = p->data;
	Q->front = p->next;
	free(p);
	Q->size--;
	if (Q->front == NULL) {
		Q->rear = NULL;
	}
	return OK;
}

int QueueLength(LinkQueue * Q) {
	return Q == NULL ? 0 : Q->size;
}

void Print(LinkQueue * Q) {
	if (Q == NULL || IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (QueueNode * q = Q->front; q; q = q->next) {
		printf("%d ", q->data);
	}
	putchar('\n');
}

Status GetFront(LinkQueue * Q, Elemtype * e) {
	if (Q == NULL)	return ERROR;
	*e = Q->front->data;
	return OK;
}

int main() {
	Elemtype e;
	LinkQueue * Q;
	InitLinkQueue(&Q);

	for (int i = 1; i <= 50; ++i)
		EnQueue(Q, i);

	GetFront(Q, &e);
	printf("队头元素为%d\n", e);
	printf("队列长度为: %d\n", QueueLength(Q));
	printf("队列元素为:\n");
	Print(Q);

	for (int i = 1; i <= 10; ++i)
		DeQueue(Q, &e);

	GetFront(Q, &e);
	printf("\n队头元素为%d\n", e);
	printf("队列元素为:\n");
	printf("队列长度为: %d\n", QueueLength(Q));
	Print(Q);

	return 0;
}
