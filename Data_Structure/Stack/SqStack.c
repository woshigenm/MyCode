#include "../Headers/SqStack.h"
#include <stdio.h>

//初始化栈
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

	printf("栈中元素（栈底→栈顶）：");
	for (int i = 0; i <= S->top; i++) {
		printf("%d ", S->data[i]);
	}

	putchar('\n');
}

