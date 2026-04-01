#include <stdio.h>
#include <string.h>

int qingmi(int x) {
	int sum = 0;

	for (int i = 1; i < x; i++)
		if (x % i == 0)	sum += i;

	return sum;
}

int main() {
	int count = 0;
	for (int i = 1; i <= 3000; i++) {
		int first = qingmi(i);
		int second = qingmi(first);

		if (first < second && i == second) {
			count++;
			printf("(%d,%d) ", first, second);
			if (count % 5 == 0)	putchar('\n');
		}
	}
}

