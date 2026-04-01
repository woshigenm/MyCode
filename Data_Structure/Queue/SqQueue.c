#include "../Headers/SqQueue.h"
#include <stdio.h>

Status InitQueue(SqQueue * Q) {
	if (Q == NULL)	return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}

bool IsEmpty(SqQueue * Q) {
	return Q == NULL || Q->front == Q->rear;
}

bool IsFull(SqQueue * Q) {
	return Q == NULL || Q->rear + 1 == Q->front;
}

Status EnQueue(SqQueue * Q, Elemtype e) {
	if (Q == NULL || IsFull(Q))	return ERROR;
	Q->data[Q->rear++] = e;
	return OK;
}

Status DeQueue(SqQueue * Q, Elemtype * e) {
	if (Q == NULL || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front++];
	return OK;
}

int QueueLength(SqQueue * Q) {
	return Q == NULL ? 0 : Q->rear - Q->front;
}

void Print(SqQueue * Q) {
	if (Q == NULL || IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (int i = Q->front; i < Q->rear; i++) {
		printf("%d ", Q->data[i]);
	}

	putchar('\n');
}

Status GetFront(SqQueue * Q, Elemtype * e) {
	if (Q == NULL)	return ERROR;
	*e = Q->data[Q->front];
	return OK;
}

