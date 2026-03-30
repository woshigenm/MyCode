#include <stdio.h>

#define N 13
int main() {
	int array[N] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int year, month, day;

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)	array[1] = 29;

	scanf("%d%d%d", &year, &month, &day);

	array[0] = day;

	for (int i = 1; i < month; i++) {
		array[0] += array[i];
	}

	printf("第%d天\n", array[0]);
	return 0;
}
