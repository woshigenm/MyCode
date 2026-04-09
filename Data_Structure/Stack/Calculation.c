#include "../Headers/LinkStack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int Calculate(char oper, int oprand1, int oprand2);
int GetPriority(char oper);
int Calc_Infix(const char * str);
bool MatchParentheses(const char *infix_str);
bool IsRightAssoc(char oper);

#define MAXINPUT 128
int main() {
	char str[MAXINPUT];
	fgets(str, MAXINPUT, stdin);
	str[strcspn(str, "\n")] = '\0';

	printf("%d\n", Calc_Infix(str));

	return 0;
}

int Calc_Infix(const char * str) {
	ElemType oprand1, oprand2, top_oper, now_oper, result, Nothing;

	if (!MatchParentheses(str)) {
		printf("表达式错误：未配对的括号\n");
		exit(EXIT_FAILURE);
	}

	LinkStack Operator, Operand;
	InitStack(&Operator);
	InitStack(&Operand);

	const char * pstr = str;
	while (*pstr) {
		if (*pstr == ' ') {
			pstr++;
			continue;
		}

		if (*pstr == '-' && (pstr == str || *(pstr - 1) == '(' ||
		                     (GetPriority(*(pstr - 1)) > 0 && *(pstr - 1) != ')'))) {
			Push(Operand, 0);
		}

		if (isdigit(*pstr)) {
			int sum = 0;
			while (*pstr && isdigit(*pstr)) {
				sum = sum * 10 + (*pstr - '0');
				pstr++;
			}
			Push(Operand, sum);
			continue;
		}

		switch (*pstr) {
			case '(':
				Push(Operator, *pstr);
				break;
			case ')':
				while (GetTop(Operator, &top_oper) == OK && top_oper != '(') {
					Pop(Operator, &now_oper);
					Pop(Operand, &oprand2);
					Pop(Operand, &oprand1);
					result = Calculate(now_oper, oprand1, oprand2);
					Push(Operand, result);
				}
				Pop(Operator, &Nothing);//抛弃'('
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
				while (!IsEmpty(Operator) && GetTop(Operator, &top_oper) == OK && top_oper != '(') {
					if (GetPriority(*pstr) > GetPriority(top_oper)
					    || IsRightAssoc(*pstr))
						break;

					Pop(Operator, &now_oper);
					Pop(Operand, &oprand2);
					Pop(Operand, &oprand1);
					result = Calculate(now_oper, oprand1, oprand2);
					Push(Operand, result);
				}
				Push(Operator, *pstr);
				break;
			default: {
				DestroyStack(&Operand);
				DestroyStack(&Operator);
				printf("表达式错误：非法字符\n");
				exit(EXIT_FAILURE);
			}

		}
		pstr++;
	}

	while (!IsEmpty(Operator)) {
		Pop(Operator, &now_oper);
		Pop(Operand, &oprand2);
		Pop(Operand, &oprand1);
		result = Calculate(now_oper, oprand1, oprand2);
		Push(Operand, result);
	}

	bool success = Pop(Operand, &result) == OK && IsEmpty(Operator);
	DestroyStack(&Operand);
	DestroyStack(&Operator);

	if (!success) {
		printf("表达式错误：操作数或运算符数量不匹配\n");
		exit(EXIT_FAILURE);
	}

	return result;
}

int GetPriority(char oper) {
	switch (oper) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
		case '(':
			return 0;
	}
	return -1;
}

int Calculate(char oper, int oprand1, int oprand2) {
	switch (oper) {
		case '+':
			return oprand1 + oprand2;
		case '-':
			return oprand1 - oprand2;
		case '*':
			return oprand1 * oprand2;
		case '/':
			if (oprand2 == 0) {
				printf("除数不能为零\n");
				exit(EXIT_FAILURE);
			}
			return oprand1 / oprand2;
		case '%':
			if (oprand2 == 0) {
				printf("模数不能为零\n");
				exit(EXIT_FAILURE);
			}
			return oprand1 % oprand2;
		case '^':
			if (oprand2 < 0) return 0;
			int res = 1;
			for (int i = 0; i < oprand2; i++) {
				res *= oprand1;
			}
			return res;
	}

	return 0;
}

bool MatchParentheses(const char *infix_str) {
	if (NULL == infix_str)	return false;
	ElemType push_elem, top_elem;
	LinkStack Parentheses;
	InitStack(&Parentheses);

	bool flag = true;
	while (*infix_str && flag) {
		switch (*infix_str) {
			case '(': {
				push_elem = *infix_str;
				Push(Parentheses, push_elem);
				break;
			}
			case ')': {
				if (GetTop(Parentheses, &top_elem) == OK && top_elem == '(') {
					Pop(Parentheses, &top_elem);
				} else {
					flag = false;
				}
				break;
			}
		}
		infix_str++;
	}

	bool result = IsEmpty(Parentheses) && flag;
	DestroyStack(&Parentheses);
	return result;
}

// 判断是否为右结合运算符
bool IsRightAssoc(char oper) {
	return oper == '^';
}

