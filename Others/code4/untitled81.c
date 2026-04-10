#include <stdio.h>
#include <string.h>

#define SIZE 64
void Convert(long long int x, int n)
{
	int tmp = x % n;

	if (x > 1) {
		Convert(x / n, n);
	} else if (x == 0)	return;

	if (n == 16) {
		if (tmp >= 10 && tmp <= 16)	putchar('A' - 10 + tmp);
		else	putchar('0' + tmp);
	} else if (n == 2) {
		putchar(tmp ? '1' : '0');
	} else if (n == 8) {
		putchar('0' + tmp);
	}
}

void fanshen()
{
	const char str[] = "0123456789ABCDEF";
	int input = 32, n = 8;

	char new_str[SIZE];

	int i;
	for (i = 0; input != 0; i++, input /= n)
		new_str[i] = str[input % n];

	new_str[i] = '\0';

	strrev(new_str);

	if (n == 16) {
		printf("0x%s\n", new_str);
	} else if (n == 8) {
		printf("0%s\n", new_str);
	} else {
		printf("%s\n", new_str);
	}

}

void test()
{
	int input, n;
	scanf("%d%d", &input, &n);
	Convert(input, n);
//	int tmp = input;
//	int sum = 0;
//	int j = 1;
//	while(input) {
//	sum = sum + (input % n) * j;
//	j *= 10;
//	input /= n;
//	}
//
//	printf("%d 转 %d 进制为 %d\n", tmp, n, sum);
}



void fan(long long int input, int n)
{
	char str[SIZE] = {};
	int i = 0;
	while (input) {
		int tmp = input % n;
		if (tmp >= 10 && tmp <= 15) {
			str[i] = 'A' - 10 + tmp;
		} else {
			str[i] = '0' + tmp;
		}

		input /= n;
		i++;
	}

	for (int j = i; j >= 0; j--) {
		printf("%c", str[j]);
	}

	putchar('\n');
}

int main()
{
	long long int input, n;
	//scanf("%lld", &input);

	fan(31LL, 16);
	Convert(0XELL, 16);
	return 0;
}
