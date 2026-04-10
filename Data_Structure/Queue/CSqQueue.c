#include "../Headers/CSqQueue.h"
#include <stdio.h>

//初始化循环队列
Status InitQueue(CSqQueue * Q, int n)
{
	if (NULL == Q || n <= 0)	return ERROR;
	*Q = (QueueNode *)malloc(sizeof(struct QueueNode));
	if (NULL == *Q)	return ERROR;
	(*Q)->data = (ElemType *)malloc(sizeof(ElemType) * n);
	if (NULL == (*Q)->data)	{
		free(*Q);
		*Q = NULL;
		return ERROR;
	}
	(*Q)->maxsize = n;
	(*Q)->front = (*Q)->rear = 0;
	return OK;
}

//判断循环队列是否为空
bool IsEmpty(CSqQueue Q)
{
	return NULL == Q || Q->front == Q->rear;
}

//判断循环队列是否为满
bool IsFull(CSqQueue Q)
{
	return NULL == Q || (Q->rear + 1) % Q->maxsize == Q->front;
}

//循环队列入队
Status EnQueue(CSqQueue Q, ElemType e)
{
	if (NULL == Q || IsFull(Q))	return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % Q->maxsize;
	return OK;
}

//循环队列出队
Status DeQueue(CSqQueue Q, ElemType * e)
{
	if (NULL == Q || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % Q->maxsize;
	return OK;
}

//返回循环队列长度
int QueueLength(CSqQueue Q)
{
	return NULL == Q ? 0 : (Q->rear - Q->front + Q->maxsize) % Q->maxsize;
}

//打印循环队列元素
void Print(CSqQueue Q)
{
	if (NULL == Q) {
		printf("队列未初始化\n");
		return;
	}

	if (IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (int j = Q->front; j != Q->rear; j = (j + 1) % Q->maxsize) {
		printf("%d ", Q->data[j]);
	}

	putchar('\n');
}

//返回队头元素
Status GetHead(CSqQueue Q, ElemType * e)
{
	if (NULL == Q || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front];
	return OK;
}

Status DestroyQueue(CSqQueue * Q)
{
	if (NULL == Q || NULL == *Q)	return ERROR;

	if (NULL != (*Q)->data) {
		free((*Q)->data);
	}

	free(*Q);
	*Q = NULL;

	return OK;
}

Status ClearQueue(CSqQueue Q)
{
	if (NULL == Q)	return ERROR;
	if (IsEmpty(Q))	return OK;

	Q->front = Q->rear = 0;
	return OK;
}

