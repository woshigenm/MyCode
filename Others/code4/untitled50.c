#include <stdio.h>

int main() {
	float money, tax = 0, temp;

	scanf("%f", &money);
	temp = money;

	if (temp > 1000000) {
		tax += (temp - 1000000) * 0.01;
		temp = 1000000;
	}

	if (temp > 600000) {
		tax += (temp - 600000) * 0.015;
		temp = 600000;
	}

	if (temp > 400000) {
		tax += (temp - 400000) * 0.03;
		temp = 400000;
	}

	if (temp > 200000) {
		tax += (temp - 200000) * 0.05;
		temp = 200000;
	}

	if (temp > 100000) {
		tax += (temp - 100000) * 0.075;
		temp = 100000;
	}

	if (temp <= 100000) {
		tax += temp * 0.1;
	}

	printf("%.f\n", tax);

	return 0;
}
