#include "../Headers/LinkStack.h"
#include <stdio.h>

#define SPACE ' '
void Convert(int X, int N);
int main() {
	int X, N;
	scanf("%d%d", &X, &N);
	Convert(X, N);
	return 0;
}

void Convert(int X, int N) {
	LinkStack s;
	InitStack(&s);

	ElemType tmp;
	int j = 0;
	while (X) {
		tmp = X % N;
		if (tmp > 9) {
			Push(s, 'A' - 10 + tmp);
		} else {
			Push(s, '0' + tmp);
		}

		if (++j % 8 == 0) {
			Push(s, SPACE);
		}

		X /= N;
	}

	while (!IsEmpty(s)) {
		Pop(s, &tmp);
		printf("%c", tmp);
	}
}
