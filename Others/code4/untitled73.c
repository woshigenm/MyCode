#include <stdio.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
	ElemType data[MAXSIZE];
	int front;
	int rear;
} Queue;

void InitQueue(Queue * q) {
	q->front = q->rear = 0;
}

int isEmpty(Queue * q) {
	if (q->front == 0 && q->rear == 0) {
		return 0;
	}

	if (q->front == q->rear) {
		return 1;
	}

	return 0;
}

ElemType deQueue(Queue * q) {
	if (isEmpty(q)) {
		printf("The Queue Is NULL\n");
		return 0;
	}

	q->front++;

	return q->data[(q->front) - 1];
}

int getHead(Queue * q, ElemType * e) {
	if (isEmpty(q)) {
		printf("The Queue Is NULL\n");
		return 0;
	}

	*e = q->data[q->front];
	return 1 ;
}

int queueFull(Queue * q) {
	if (q->front > 0) {
		int step = q->front;

		for (int i = q->front; i < q->rear; ++i) {
			q->data[i - step] = q->data[i];
		}

		q->front = 0;
		q->rear = q->rear - step;

		return 0;
	}

	printf("The Queue Is FULL\n");
	return 1;
}

ElemType eqQueue(Queue * q, ElemType e) {
	if (q->rear >= MAXSIZE) {
		if (!queueFull(q)) {
			return 0;
		}
	}

	q->data[q->rear] = e;
	q->rear++;

	return 1;
}

void PrintElem(Queue *q) {
	if (isEmpty(q)) {
		printf("The Queue Is NULL\n");
		return;
	}

	for (int i = q->front; i < q->rear; i++) {
		printf("%d ", q->data[i]);
	}

	putchar('\n');
}

int main() {
	Queue queue;
	Queue *q = &queue;
	InitQueue(q);
	for (int i = 1; i <= MAXSIZE; i++) {
		eqQueue(q, i);
	}
	printf("%d\n", deQueue(q));
	PrintElem(q);

	return 0;
}
