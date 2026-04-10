#include "../Headers/DLinkQueue.h"
#include <stdio.h>

Status InitQueue(DLinkQueue * DLQ)
{
	if (NULL == DLQ)	return ERROR;
	*DLQ = (DLinkQueue)malloc(sizeof(struct DLinkQueue));
	if (NULL == *DLQ)	return ERROR;
	(*DLQ)->front = (*DLQ)->rear = NULL;
	(*DLQ)->length = 0;
	return OK;
}

bool IsEmpty(DLinkQueue DLQ)
{
	return NULL == DLQ ? true : DLQ->front == NULL && DLQ->rear == NULL;
}

Status EnQueue(DLinkQueue DLQ, Which_Ended s, ElemType e)
{
	if (NULL == DLQ)	return ERROR;

	DLinkQueueNode * node = (DLinkQueueNode *)malloc(sizeof(struct DLinkQueueNode));
	if (NULL == node)	return ERROR;
	node->data = e;
	node->next = node->prior = NULL;

	if (NULL == DLQ->front) {
		DLQ->front = DLQ->rear = node;
	} else {
		if (s == FRONT) {
			//node->prior = DLQ->front->prior;
			DLQ->front->prior = node;
			node->next = DLQ->front;
			DLQ->front = node;
		} else if (s == REAR) {
			//node->next = DLQ->rear->next;
			DLQ->rear->next = node;
			node->prior = DLQ->rear;
			DLQ->rear = node;
		} else {
			free(node);
			return ERROR;
		}
	}

	DLQ->length++;
	return OK;
}

Status DeQueue(DLinkQueue DLQ, Which_Ended s, ElemType * e)
{
	if (NULL == DLQ || NULL == e)	return ERROR;
	if (IsEmpty(DLQ))	return ERROR;

	DLinkQueueNode * tmp = NULL;
	if (s == FRONT) {
		tmp = DLQ->front;
		*e = tmp->data;
		DLQ->front = DLQ->front->next;
		if (DLQ->front != NULL)
			DLQ->front->prior = NULL;
		else
			DLQ->rear = NULL;
		free(tmp);
	} else if (s == REAR) {
		tmp = DLQ->rear;
		*e = tmp->data;
		DLQ->rear = DLQ->rear->prior;
		if (DLQ->rear != NULL)
			DLQ->rear->next = NULL;
		else
			DLQ->front = NULL;
		free(tmp);
	} else {
		return ERROR;
	}

	DLQ->length--;
	return OK;
}

int QueueLength(DLinkQueue DLQ)
{
	return NULL == DLQ ? 0 : DLQ->length;
}

void Print(DLinkQueue DLQ, Which_Ended s)
{
	if (NULL == DLQ) {
		printf("双向队列未初始化\n");
		return;
	}

	if (IsEmpty(DLQ)) {
		printf("双向队列为空\n");
		return;
	}

	DLinkQueueNode * cur = s == FRONT ? DLQ->front : DLQ->rear;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = s == FRONT ? cur->next : cur->prior;
	}

	putchar('\n');
}

Status GetHead(DLinkQueue DLQ, Which_Ended s, ElemType * e)
{
	if (NULL == DLQ || NULL == e)	return ERROR;
	if (IsEmpty(DLQ))	return ERROR;

	if (s == FRONT) {
		*e = DLQ->front->data;
	} else if (s == REAR) {
		*e = DLQ->rear->data;
	} else {
		return ERROR;
	}

	return OK;
}

Status DestroyQueue(DLinkQueue * DLQ)
{
	if (NULL == DLQ)	return ERROR;
	if (NULL == *DLQ)	return OK;

	DLinkQueueNode * cur = (*DLQ)->front, *tmp = NULL;
	while (cur) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}

	free(*DLQ);
	*DLQ = NULL;
	return OK;
}

Status ClearQueue(DLinkQueue DLQ)
{
	if (NULL == DLQ)	return ERROR;
	if (IsEmpty(DLQ))	return OK;

	DLinkQueueNode * cur = DLQ->front, *tmp = NULL;
	while (cur) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}

	DLQ->length = 0;
	DLQ->front = DLQ->rear = NULL;

	return OK;
}

