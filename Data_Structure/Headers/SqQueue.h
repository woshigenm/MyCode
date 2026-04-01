#ifndef __SQQUEUE_H__
#define __SQQUEUE_H__

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

#endif
