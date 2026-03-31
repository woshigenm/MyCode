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

Status InitQueue(SqQueue * Q);
bool IsEmpty(SqQueue * Q);
bool IsFull(SqQueue * Q);
Status EnQueue(SqQueue * Q, Elemtype e);
Status DeQueue(SqQueue * Q, Elemtype * e);
int QueueLength(SqQueue * Q);
void Print(SqQueue * Q);
Status GetFront(SqQueue * Q, Elemtype * e);

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

//初始化循环队列
Status InitQueue(SqQueue * Q) {
	if (NULL == Q)	return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}

//判断循环队列是否为空
bool IsEmpty(SqQueue * Q) {
	return NULL == Q || Q->front == Q->rear;
}

//判断循环队列是否为满
bool IsFull(SqQueue * Q) {
	return NULL == Q || (Q->rear + 1) % MAXSIZE == Q->front;
}

//循环队列入队
Status EnQueue(SqQueue * Q, Elemtype e) {
	if (NULL == Q || IsFull(Q))	return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//循环队列出队
Status DeQueue(SqQueue * Q, Elemtype * e) {
	if (NULL == Q || IsEmpty(Q))	return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

//返回循环队列长度
int QueueLength(SqQueue * Q) {
	return NULL == Q ? 0 : (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//打印循环队列元素
void Print(SqQueue * Q) {
	if (NULL == Q) {
		printf("队列未初始化\n");
		return;
	}

	if (IsEmpty(Q))	{
		printf("队列为空\n");
		return;
	}

	for (int j = Q->front; j != Q->rear; j = (j + 1) % MAXSIZE) {
		printf("%d ", Q->data[j]);
	}

	putchar('\n');
}

//返回队头元素
Status GetFront(SqQueue * Q, Elemtype * e) {
	if (NULL == Q)	return ERROR;
	*e = Q->data[Q->front];
	return OK;
}

