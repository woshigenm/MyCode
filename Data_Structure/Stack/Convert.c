#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZE 128
typedef struct Stack {
	ElemType data[MAXSIZE];
	int top;
} Stack;

Status InitStack(Stack * S);
Status Push(Stack * S, ElemType e);
Status Pop(Stack * S, ElemType * e);
bool IsEmpty(Stack * S);
int StackLength(Stack * S);
bool IsFull(Stack * S);
Status GetTop(Stack * S, ElemType * e);
void PrintStack(Stack *S);

Status InitStack(Stack * S) {
	if (NULL == S) return ERROR;
	S->top = -1;
	return OK;
}

//判断栈是否为满
bool IsFull(Stack * S) {
	if (NULL == S) return false;
	return S->top + 1 == MAXSIZE;
}

//判断栈是否为空
bool IsEmpty(Stack * S) {
	if (NULL == S)	return true;
	return S->top == -1;
}

//元素入栈
Status Push(Stack * S, ElemType e) {
	if (NULL == S) return ERROR;
	if (IsFull(S))	return ERROR;
	S->data[++S->top] = e;
	return OK;
}

//元素弹栈
Status Pop(Stack * S, ElemType * e) {
	if (NULL == S) return ERROR;
	if (IsEmpty(S))	return ERROR;
	*e = S->data[S->top--];
	return OK;
}

//返回栈长度
int StackLength(Stack * S) {
	if (NULL == S)	return 0;
	return S->top + 1;
}

//返回栈顶元素
Status GetTop(Stack * S, ElemType * e) {
	if (NULL == S) return ERROR;
	if (IsEmpty(S))	return ERROR;
	*e = S->data[S->top];
	return OK;
}

// 打印栈中所有元素（从栈底到栈顶）
void PrintStack(Stack *S) {
	if (NULL == S) {
		printf("栈未初始化!\n");
		return;
	}

	if (IsEmpty(S)) {
		printf("栈为空!\n");
		return;
	}

	for (int i = 0; i <= S->top; i++) {
		printf("%d ", S->data[i]);
	}

	putchar('\n');
}

void Convert(int X, int N);
int main() {
	int X, N;
	scanf("%d%d", &X, &N);
	Convert(X, N);
	return 0;
}

#define SPACE ' '
void Convert(int X, int N) {
	Stack s;
	InitStack(&s);

	char tmp;
	int j = 0;
	while (X) {
		tmp = X % N;
		if (tmp > 9) {
			Push(&s, 'A' - 10 + tmp);
		} else {
			Push(&s, '0' + tmp);
		}

		if (++j % 8 == 0) {
			Push(&s, SPACE);
		}

		X /= N;
	}

	while (!IsEmpty(&s)) {
		Pop(&s, &tmp);
		printf("%c", tmp);
	}
}
