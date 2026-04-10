#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Elemtype;
typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	Elemtype * data;
	int front, rear;
	int maxsize;
} QueueNode, *CSqQueue;

// 函数声明
Status InitQueue(CSqQueue * Q, int n);
bool IsEmpty(CSqQueue Q);
bool IsFull(CSqQueue Q);
Status EnQueue(CSqQueue Q, Elemtype e);
Status DeQueue(CSqQueue Q, Elemtype * e);
Status GetHead(CSqQueue Q, Elemtype * e);
Status DestroyQueue(CSqQueue * Q);

#define SIZE 13
void Shuffle(int deck[], int decksize);
int main()
{
	int deck[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	Shuffle(deck, SIZE);
	return 0;
}

void Shuffle(int deck[], int decksize)
{
	CSqQueue Queue1;
	InitQueue(&Queue1, SIZE + 1);
	for (int i = 0; i < decksize; ++i) {
		EnQueue(Queue1, i);
	}

	int result[SIZE] = {};
	int i = 0;
	Elemtype e;
	while (!IsEmpty(Queue1) && i < decksize) {
		DeQueue(Queue1, &e);
		result[i++] = e;

		int j = 0;
		while (!IsEmpty(Queue1) && j++ < i) {
			DeQueue(Queue1, &e);
			EnQueue(Queue1, e);
		}
	}

	for (int i = 0; i < decksize; i++) {
		printf("第%d 个 -> %d\n", i + 1, result[i]);
	}

	putchar('\n');
}

//初始化循环队列
Status InitQueue(CSqQueue * Q, int n)
{
	if (NULL == Q || n <= 0)	return ERROR;
	*Q = (QueueNode *)malloc(sizeof(struct QueueNode));
	if (NULL == *Q)	return ERROR;
	(*Q)->data = (Elemtype *)malloc(sizeof(Elemtype) * n);
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
Status EnQueue(CSqQueue Q, Elemtype e)
{
	if (NULL == Q || IsFull(Q))	return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % Q->maxsize;
	return OK;
}

//循环队列出队
Status DeQueue(CSqQueue Q, Elemtype * e)
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

//返回队头元素
Status GetHead(CSqQueue Q, Elemtype * e)
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


