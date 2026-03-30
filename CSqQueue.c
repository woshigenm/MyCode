#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

#define MAXSIZE 1024
typedef struct QueueNode {
	Elemtype data[MAXSIZE];
	int front, rear;
} QueueNode, SqQueue;

Status InitQueue(SqQueue * Q) {
	if (Q == NULL)	return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}

bool IsEmpty(SqQueue * Q) {
	return Q == NULL || Q->front == Q->rear;
}

bool IsFull(SqQueue * Q) {
	return Q == NULL || (Q->rear + 1) % MAXSIZE == Q->front;
}

Status EnQueue(SqQueue * Q, Elemtype e) {
	if (Q == NULL || IsFull(Q))	return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue * Q, Elemtype * e) {
	if (Q == NULL || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

int QueueLength(SqQueue * Q) {
	return Q == NULL ? 0 : (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

void Print(SqQueue * Q) {
	if (Q == NULL || IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (int i = 1, j = Q->front; i <= QueueLength(Q); i++, j = (j + 1) % MAXSIZE) {
		printf("%d ", Q->data[j]);
	}

	putchar('\n');
}

Status GetFront(SqQueue * Q, Elemtype * e) {
	if (Q == NULL)	return ERROR;
	*e = Q->data[Q->front];
	return OK;
}

int main() {
	SqQueue Q;
	Elemtype e;
	InitQueue(&Q);
	for (int i = 1; i <= 50; ++i)
		EnQueue(&Q, i);

	GetFront(&Q, &e);
	printf("队头元素为%d\n", e);
	printf("队列长度为: %d\n", QueueLength(&Q));
	printf("队列元素为:\n");
	Print(&Q);

	for (int i = 1; i <= 10; ++i)
		DeQueue(&Q, &e);

	GetFront(&Q, &e);
	printf("\n队头元素为%d\n", e);
	printf("队列元素为:\n");
	printf("队列长度为: %d\n", QueueLength(&Q));
	Print(&Q);
	return 0;
}

