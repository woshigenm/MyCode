#include <stdio.h>

int main() {
	float money, tax, temp;

	scanf("%f", &money);
	tax = 0.0;
	temp = money;

	if(temp > 85000) {
		tax += (temp - 85000) * 0.45;
		temp = 85000;
	}

	if(temp > 60000) {
		tax += (temp - 60000) * 0.35;
		temp = 60000;
	}

	if(temp > 40000) {
		tax += (temp - 40000) * 0.30;
		temp = 40000;
	}

	if(temp > 30000) {
		tax += (temp - 30000) * 0.25;
		temp = 30000;
	}

	if(temp > 17000) {
		tax += (temp - 17000) * 0.20;
		temp = 17000;
	}

	if(temp > 8000) {
		tax += (temp - 8000) * 0.10;
		temp = 8000;
	}

	if(temp > 5000) {
		tax += (temp - 5000) * 0.03;
		temp = 5000;
	}

	printf("月收入%.2f,个税为:%.2f元\n", money, tax);
}
