#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 32
typedef struct ElemType {
	char name[MAXSIZE];
	char gender; // M 男 F 女
} ElemType;

typedef enum {
	ERROR, OK
} Status;

typedef struct QueueNode {
	ElemType * data;
	int front, rear;
	int maxsize;
} QueueNode, *CSqQueue;

Status InitQueue(CSqQueue * Q, int n);
bool IsEmpty(CSqQueue Q);
bool IsFull(CSqQueue Q);
Status EnQueue(CSqQueue Q, ElemType e);
Status DeQueue(CSqQueue Q, ElemType * e);
int QueueLength(CSqQueue Q);
Status GetHead(CSqQueue Q, ElemType * e);
Status DestroyQueue(CSqQueue * Q);
Status ClearQueue(CSqQueue Q);

#define MAXLENGTH 128
#define MAX_PEOPLE 128
int main()
{
	CSqQueue Male, FeMale;
	InitQueue(&Male, MAX_PEOPLE);
	InitQueue(&FeMale, MAX_PEOPLE);
	ElemType Infomation[MAX_PEOPLE];

	int i = 0;
	printf("请输入姓名和性别(以 # 结束):\n");
	while (i < MAX_PEOPLE) {
		scanf("%31s", Infomation[i].name);
		if (strcmp(Infomation[i].name, "#") == 0) {
			break;
		}
		scanf(" %c", &Infomation[i].gender);
		i++;
	}

	int j = 0;
	while (j < i) {
		if (Infomation[j].gender == 'M') {
			EnQueue(Male, Infomation[j]);
		} else {
			EnQueue(FeMale, Infomation[j]);
		}
		j++;
	}

	ElemType tmp;
	while (!IsEmpty(Male) && !IsEmpty(FeMale)) {
		DeQueue(Male, &tmp);
		printf("%s %c\n", tmp.name, tmp.gender);
		DeQueue(FeMale, &tmp);
		printf("%s %c\n", tmp.name, tmp.gender);
	}

	printf("\n下一个等待匹配的是: \n");
	if (IsEmpty(Male)) {
		GetHead(FeMale, &tmp);
		printf("%s %c", tmp.name, tmp.gender);
	} else {
		GetHead(Male, &tmp);
		printf("%s %c", tmp.name, tmp.gender);
	}

	return 0;
}

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
