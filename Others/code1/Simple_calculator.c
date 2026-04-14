#include <stdio.h>

int main()
{
	float n, m;
	char op;
	scanf("%f %c%f", &n, &op, &m);

	float reslut;

	switch (op) {
		case '+':
			reslut = n + m;
			break;
		case '-':
			reslut = n - m;
			break;
		case '*':
			reslut = n * m;
			break;
		case '/':
			reslut = n / m;
			break;
	}

	printf("%.2f\n", reslut);

	return 0;
}
