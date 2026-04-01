#include <stdio.h>

#define SIZE 32

void fanxiaochao(int test);
void fanxiaochaoSM(int test);
void fanxiaochaoCNM(int test);
void fanxiaochaoMM(int test);
void ChaoShen(int test);

#define TEST (81 * 12)

int count_a(int test);

int main() {
	fanxiaochao(TEST);
	fanxiaochaoCNM(TEST);
	fanxiaochaoMM(TEST);
	fanxiaochaoSM(TEST);
	for (int i = 1; i <= SIZE - count_a(TEST); i++)	putchar('0');
	ChaoShen(TEST);
	return 0;
}

int count_a(int test) {
	int count = 0;
	while (test) {
		test /= 2;
		count++;
	}

	return count;
}

void ChaoShen(int test) {
	char temp = test % 2;

	if (test > 1) {
		ChaoShen(test / 2);
	}

	putchar(temp == 0 ? '0' : '1');
}

void fanxiaochaoCNM(int test) {
	int j = 1, sum = 0;
	int count = 1;
	while (test != 0) {
		sum += (test % 2) * j;
		test /= 2;
		j *= 10;
		count++;
	}

	for (int i = 0; i <= SIZE - count; i++)
		putchar('0');

	printf("%d\n", sum);
}

void fanxiaochaoMM(int test) {
	int j = 1, sum = 0;
	int count = 1;
	while (test != 0) {
		sum += (test % 2) * j;
		test /= 2;
		j *= 10;
		count++;
	}

	for (int i = 0; i <= SIZE - count; i++)
		putchar('0');

	printf("%d\n", sum);
}

void fanxiaochaoSM(int test) {
	int array[SIZE] = {};
	int i, j;
	for (i = 0; test != 0; i++) {
		if (test % 2 == 1)	array[i] = 1;
		test /= 2;
	}

	for (j = SIZE - 1; j >= 0; j--) {
		printf("%d", array[j]);
		//if(j%8==0)	putchar(' ');
	}

	putchar('\n');
}

void fanxiaochao(int test) {
	int array[SIZE];
	int i, j;
	for (i = 0; test != 0; i++) {
		array[i] = test % 2;
		test /= 2;
	}

	for (j = SIZE - 1; j >= 0; j--) {
		if (j > i - 1)	putchar('0');
		else {
			printf("%d", array[j]);
		}

		//if(j % 8 ==0)	putchar(' ');
	}

	putchar('\n');
}
