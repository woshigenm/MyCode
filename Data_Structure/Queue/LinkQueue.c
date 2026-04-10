#include "../Headers/LinkQueue.h"
#include <stdio.h>

Status InitLinkQueue(LinkQueuePtr * Q)
{
	if (NULL == Q)	return ERROR;
	*Q = (LinkQueuePtr)malloc(sizeof(struct LinkQueue));
	if (NULL == *Q)	return ERROR;
	(*Q)->front = (*Q)->rear = NULL;
	(*Q)->size = 0;
	return OK;
}

bool IsEmpty(LinkQueuePtr Q)
{
	return Q == NULL || Q->front == NULL;
}

Status EnQueue(LinkQueuePtr Q, ElemType e)
{
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

Status DeQueue(LinkQueuePtr Q, ElemType * e)
{
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

int QueueLength(LinkQueuePtr Q)
{
	return Q == NULL ? 0 : Q->size;
}

void Print(LinkQueuePtr Q)
{
	if (Q == NULL || IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (QueueNode * q = Q->front; q; q = q->next) {
		printf("%d ", q->data);
	}
	putchar('\n');
}

Status GetHead(LinkQueuePtr Q, ElemType * e)
{
	if (NULL == Q || NULL == e || IsEmpty(Q))	return ERROR;
	*e = Q->front->data;
	return OK;
}

Status DestroyQueue(LinkQueuePtr * Q)
{
	if (NULL == Q || NULL == *Q)	return ERROR;
	QueueNode * current = (*Q)->front, *tmp = NULL;
	while (current) {
		tmp = current;
		current = current->next;
		free(tmp);
	}

	free(*Q);
	*Q = NULL;

	return OK;
}

Status ClearQueue(LinkQueuePtr Q)
{
	if (NULL == Q )	return ERROR;
	QueueNode * current = Q->front, *tmp = NULL;
	while (current) {
		tmp = current;
		current = current->next;
		free(tmp);
	}

	return OK;
}


