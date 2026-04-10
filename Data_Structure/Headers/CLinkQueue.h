#ifndef __CLINKQUEUE_H__
#define __CLINKQUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	ERROR, OK
} Status;

typedef struct CLQueueNode {
	ElemType data;
	struct CLQueueNode * next;
} CLQueueNode;

typedef struct CLinkQueue {
	struct CLQueueNode * tail;
	int size;
}*CLinkQueue;

Status InitQueue(CLinkQueue * CLQ);
bool IsEmpty(CLinkQueue CLQ);
Status EnQueue(CLinkQueue CLQ, ElemType e);
Status DeQueue(CLinkQueue CLQ, ElemType * e);
int QueueLength(CLinkQueue CLQ);
void Print(CLinkQueue CLQ);
Status GetHead(CLinkQueue CLQ, ElemType * e);
Status DestroyQueue(CLinkQueue * CLQ);
Status ClearQueue(CLinkQueue CLQ);

#endif
