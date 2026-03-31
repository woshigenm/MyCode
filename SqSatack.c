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

Status InitStack(Stack * S);
Status Push(Stack * S, ElemType e);
Status Pop(Stack * S, ElemType * e);
bool IsEmpty(Stack * S);
int StackLength(Stack * S);
bool IsFull(Stack * S);
Status GetTop(Stack * S, ElemType * e);
void PrintStack(Stack *S);

int main() {
	Stack s;
	ElemType e;

	// 1. 初始化栈
	printf("1. 初始化栈测试...\n");
	if (InitStack(&s) == OK) {
		printf("栈初始化成功！\n");
	} else {
		printf("栈初始化失败！\n");
		return 1;
	}
	printf("栈是否为空？%s\n\n", IsEmpty(&s) ? "是" : "否");

	// 2. 入栈操作
	printf("2. 入栈操作测试...\n");
	printf("入栈元素: 1, 2, 3\n");
	Push(&s, 1);
	Push(&s, 2);
	Push(&s, 3);
	printf("入栈后，栈长度：%d\n", StackLength(&s));
	printf("栈是否为空？%s\n", IsEmpty(&s) ? "是" : "否");
	printf("栈是否已满？%s\n", IsFull(&s) ? "是" : "否");
	PrintStack(&s);

	// 3. 获取栈顶元素
	printf("3. 获取栈顶元素测试...\n");
	if (GetTop(&s, &e) == OK) {
		printf("当前栈顶元素：%d\n\n", e);
	} else {
		printf("获取栈顶元素失败！\n\n");
	}

	// 4. 出栈操作
	printf("4. 出栈操作测试...\n");
	if (Pop(&s, &e) == OK) {
		printf("弹出的栈顶元素：%d\n", e);
	} else {
		printf("出栈失败！\n");
	}
	printf("出栈后，栈长度：%d\n", StackLength(&s));
	PrintStack(&s);

	// 5. 获取出栈后的栈顶
	printf("5. 获取出栈后的栈顶...\n");
	if (GetTop(&s, &e) == OK) {
		printf("当前栈顶元素：%d\n\n", e);
	} else {
		printf("获取栈顶元素失败！\n\n");
	}

	// 6. 填满栈测试
	printf("6. 填满栈测试...\n");
	printf("当前栈长度：%d\n", StackLength(&s));
	printf("栈容量：%d\n", MAXSIZE);

	// 先清空栈
	while (!IsEmpty(&s)) {
		Pop(&s, &e);
	}

	printf("清空栈后，栈是否为空？%s\n", IsEmpty(&s) ? "是" : "否");

	// 填充栈到满
	printf("开始填充栈...\n");
	for (int i = 1; i <= MAXSIZE; i++) {
		if (Push(&s, i) == OK) {
			printf("入栈元素: %d, 栈长度: %d\n", i, StackLength(&s));
		} else {
			printf("入栈元素 %d 失败，栈已满！\n", i);
			break;
		}
	}

	printf("填充后栈长度：%d\n", StackLength(&s));
	printf("栈是否已满？%s\n", IsFull(&s) ? "是" : "否");
	if (GetTop(&s, &e) == OK) {
		printf("当前栈顶元素：%d\n\n", e);
	}

	// 7. 栈满时入栈测试
	printf("7. 栈满时入栈测试...\n");
	printf("尝试入栈元素: 9999\n");
	if (Push(&s, 9999) == ERROR) {
		printf("栈已满，无法入栈 9999！\n");
	} else {
		printf("入栈成功！\n");
	}
	printf("栈长度：%d\n", StackLength(&s));
	printf("栈是否已满？%s\n\n", IsFull(&s) ? "是" : "否");

	// 8. 清空栈测试
	printf("8. 清空栈测试...\n");
	printf("清空前栈长度：%d\n", StackLength(&s));
	int count = 0;
	while (!IsEmpty(&s)) {
		if (Pop(&s, &e) == OK) {
			count++;
			if (count <= 5) {
				printf("弹出元素：%d\n", e);
			}
		} else {
			printf("出栈失败！\n");
			break;
		}
	}
	if (count > 5) {
		printf("... 还有 %d 个元素被弹出\n", count - 5);
	}
	printf("清空栈后, 栈长度：%d\n", StackLength(&s));
	printf("栈是否为空？%s\n\n", IsEmpty(&s) ? "是" : "否");

	// 9. 空栈操作测试
	printf("9. 空栈操作测试...\n");
	if (Pop(&s, &e) == ERROR) {
		printf("从空栈弹出失败！\n");
	}
	if (GetTop(&s, &e) == ERROR) {
		printf("获取空栈栈顶失败！\n");
	}

	printf("\n=== 所有测试完成 ===\n");
	return 0;
}

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

