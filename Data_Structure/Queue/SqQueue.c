#include "../Headers/SqQueue.h"
#include <stdio.h>

Status InitQueue(SqQueue * Q, int n)
{
	if (NULL == Q || n <= 0)	return ERROR;
	*Q = (QueueNode *)malloc(sizeof(QueueNode));
	if (NULL == *Q)	return ERROR;
	(*Q)->data = (Elemtype *)malloc(sizeof(Elemtype) * n);
	(*Q)->maxsize = n;
	if (NULL == (*Q)->data) {
		free(*Q);
		*Q = NULL;
		return ERROR;
	}
	(*Q)->front = (*Q)->rear = 0;
	return OK;
}

bool IsEmpty(SqQueue Q)
{
	return Q == NULL || Q->front == Q->rear;
}

bool IsFull(SqQueue Q)
{
	return Q == NULL || Q->rear == Q->maxsize;
}

Status EnQueue(SqQueue Q, Elemtype e)
{
	if (Q == NULL || IsFull(Q))	return ERROR;
	Q->data[Q->rear++] = e;
	return OK;
}

Status DeQueue(SqQueue Q, Elemtype * e)
{
	if (Q == NULL || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front++];
	return OK;
}

int QueueLength(SqQueue Q)
{
	return Q == NULL ? 0 : Q->rear - Q->front;
}

void Print(SqQueue Q)
{
	if (Q == NULL || IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (int i = Q->front; i < Q->rear; i++) {
		printf("%d ", Q->data[i]);
	}

	putchar('\n');
}

Status GetHead(SqQueue Q, Elemtype * e)
{
	if (Q == NULL)	return ERROR;
	*e = Q->data[Q->front];
	return OK;
}

Status DestroyQueue(SqQueue * Q)
{
	if (NULL == Q)	return ERROR;
	if (NULL != (*Q)->data) {
		free((*Q)->data);
	}

	free(*Q);
	*Q = NULL;
	return OK;
}

Status ClearQueue(SqQueue Q)
{
	if (NULL == Q)	return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}

