#include "../Headers/CLinkQueue.h"
#include <stdio.h>

Status InitQueue(CLinkQueue * CLQ)
{
	if (NULL == CLQ)	return ERROR;
	*CLQ = (CLinkQueue)malloc(sizeof(struct CLinkQueue));
	if (NULL == *CLQ)	return ERROR;
	(*CLQ)->tail = NULL;
	(*CLQ)->size = 0;
	return OK;
}

bool IsEmpty(CLinkQueue CLQ)
{
	return NULL == CLQ ? true : NULL == CLQ->tail;
}

Status EnQueue(CLinkQueue CLQ, ElemType e)
{
	if (NULL == CLQ)	return ERROR;
	CLQueueNode * node = (CLQueueNode *)malloc(sizeof(CLQueueNode));
	if (NULL == node)	return ERROR;
	node->data = e;
	node->next = NULL;

	if (NULL == CLQ->tail) {
		CLQ->tail = node;
		CLQ->tail->next = node;
	} else {
		node->next = CLQ->tail->next;
		CLQ->tail->next = node;
		CLQ->tail = node;
	}

	CLQ->size++;
	return OK;
}

Status DeQueue(CLinkQueue CLQ, ElemType * e)
{
	if (NULL == CLQ || NULL == e)	return ERROR;
	if (IsEmpty(CLQ))	return ERROR;

	CLQueueNode * tmp = CLQ->tail->next;
	*e = tmp->data;
	if (CLQ->tail->next == tmp->next) {
		free(tmp);
		CLQ->tail = NULL;
	} else {
		CLQ->tail->next = tmp->next;
		free(tmp);
	}

	CLQ->size--;
	return OK;
}

int QueueLength(CLinkQueue CLQ)
{
	return NULL == CLQ ? 0 : CLQ->size;
}

void Print(CLinkQueue CLQ)
{
	if (NULL == CLQ)	{
		printf("循环链队未初始化\n");
		return;
	}

	if (IsEmpty(CLQ))	{
		printf("循环链队为空\n");
		return;
	}

	CLQueueNode * cur = CLQ->tail->next;
	do {
		printf("%d ", cur->data);
		cur = cur->next;
	} while (cur != CLQ->tail->next);

	putchar('\n');
}

Status GetHead(CLinkQueue CLQ, ElemType * e)
{
	if (NULL == CLQ || NULL == e)	return ERROR;
	if (IsEmpty(CLQ))	return ERROR;

	*e = CLQ->tail->next->data;

	return OK;
}

Status DestroyQueue(CLinkQueue * CLQ)
{
	if (NULL == CLQ)	return ERROR;
	if (NULL == *CLQ)	return OK;

	while (!IsEmpty(*CLQ)) {
		ElemType tmp_e;
		DeQueue(*CLQ, &tmp_e);
	}

	free(*CLQ);
	*CLQ = NULL;
	return OK;
}

Status ClearQueue(CLinkQueue CLQ)
{
	if (NULL == CLQ)	return ERROR;

	while (!IsEmpty(CLQ)) {
		ElemType tmp_e;
		DeQueue(CLQ, &tmp_e);
	}

	CLQ->tail = NULL;
	CLQ->size = 0;
	return OK;
}

