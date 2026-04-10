#include <stdio.h>

int main()
{
	int hour, minute, minus;

	scanf("%d:%d:%d", &hour, &minute, &minus);

	minus++;

	if (minus >= 60) {
		minute++;
		minus = 0;
	}

	if (minute >= 60) {
		hour++;
		minute = 0;
	}

	if (hour >= 24) {
		hour = 0;
	}

	printf("%02d:%02d:%02d", hour, minute, minus);


	return 0;
}
