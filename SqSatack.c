#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef enum {
	OK, ERROR
} Status;

#define MAXSIZE 10
typedef struct Stack {
	ElemType data[MAXSIZE];
	int top;
} Stack;

Status InitStack(Stack * S) {
	if (S == NULL) return ERROR;
	S->top = -1;
	return OK;
}

Status Push(Stack * S, ElemType e) {
	if (S == NULL) return ERROR;
	if (S->top + 1 == MAXSIZE)	return ERROR;
	S->data[++S->top] = e;
	return OK;
}

Status Pop(Stack * S, ElemType * e) {
	if (S == NULL) return ERROR;
	if (S->top == -1)	return ERROR;
	*e = S->data[S->top--];
	return OK;
}

bool IsEmpty(Stack * S) {
	return S->top == -1;
}

int StackLength(Stack * S) {
	return S->top + 1;
}

bool IsFull(Stack * S) {
	if (S == NULL) return ERROR;
	return S->top + 1 == MAXSIZE;
}

Status GetTop(Stack * S, ElemType * e) {
	if (S == NULL) return ERROR;
	if (S->top == -1)	return ERROR;
	*e = S->data[S->top];
	return OK;
}

// 打印栈中所有元素（从栈底到栈顶）
void PrintStack(Stack *S) {
	if (S == NULL || IsEmpty(S)) {
		printf("栈为空！\n");
		return;
	}
	printf("栈中元素（栈底→栈顶）：");
	for (int i = 0; i <= S->top; i++) {
		printf("%d ", S->data[i]);
	}
	printf("\n");
}

int main() {
	Stack s; // 定义栈变量（而非指针）
	ElemType e;

	// 1. 初始化栈
	if (InitStack(&s) == OK) {
		printf("栈初始化成功！\n");
	}

	// 2. 入栈操作
	Push(&s, 1);
	Push(&s, 2);
	Push(&s, 3);
	printf("入栈1、2、3后，栈长度：%d\n", StackLength(&s));
	PrintStack(&s);

	// 3. 获取栈顶元素
	if (GetTop(&s, &e) == OK) {
		printf("当前栈顶元素：%d\n", e);
	}

	// 4. 出栈操作
	if (Pop(&s, &e) == OK) {
		printf("弹出的栈顶元素：%d\n", e);
	}
	printf("出栈后，栈长度：%d\n", StackLength(&s));
	PrintStack(&s);

	// 5. 判空/判满测试
	printf("栈是否为空？%s\n", IsEmpty(&s) ? "是" : "否");
	printf("栈是否已满？%s\n", IsFull(&s) ? "是" : "否");

	// 6. 填满栈测试
	for (int i = 4; i <= 10; i++) {
		Push(&s, i);
	}
	printf("填满栈后，栈长度：%d\n", StackLength(&s));
	PrintStack(&s);

	// 7. 栈满时入栈测试
	Push(&s, 11);

	// 8. 清空栈测试
	while (!IsEmpty(&s)) {
		Pop(&s, &e);
		printf("弹出元素：%d\n", e);
	}
	printf("清空栈后，栈是否为空？%s\n", IsEmpty(&s) ? "是" : "否");
	return 0;
}

