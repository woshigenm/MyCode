#include <stdio.h>

int main() {
	float x, r;
	scanf("%f", &x);

	switch ((int)x / 500) {
		case 0:
			r = 0.0;
			break;
		case 1:
			r = 0.05;
			break;
		case 2:
		case 3:
			r = 0.08;
			break;
		case 4:
		case 5:
			r = 0.1;
			break;
		default :
			r = 0.15;
	}

	printf("实得奖金%.2f元钱", x - x * r);
}
