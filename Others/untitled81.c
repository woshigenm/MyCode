#include <stdio.h>
#include <string.h>

void reverse(char* s) {
	int len = strlen(s);
	for (int i = 0; i < len / 2; i++) {
		char temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}
}

#define SIZE 64
void Convert(int x, int n) {
	int tmp = x % n;
	if (x >= n) {
		Convert(x / n, n);
	} else if (x == 0)	return;

	if (n == 16) {
		if (tmp >= 10 && tmp <= 15)	putchar('A' - 10 + tmp);
		else	putchar('0' + tmp);
	} else if (n == 2) {
		putchar(tmp ? '1' : '0');
	} else if (n == 8) {
		putchar('0' + tmp);
	}
}

void fanshen(int input, int n) {
	const char str[] = "0123456789ABCDEF";
	char new_str[SIZE];
	int i;
	for (i = 0; input != 0; i++, input /= n) new_str[i] = str[input % n];

	new_str[i] = '\0';
	reverse(new_str);

	if (n == 16) printf("0x%s\n", new_str);
	else if (n == 8) printf("0%s\n", new_str);
	else printf("%s\n", new_str);
}

void fan(int input, int n) {
	char str[SIZE] = {};
	int i = 0;
	while (input) {
		int tmp = input % n;
		if (tmp >= 10 && tmp <= 15) str[i] = 'A' - 10 + tmp;
		else str[i] = '0' + tmp;
		input /= n;
		i++;
	}

	for (int j = i - 1; j >= 0; j--) printf("%c", str[j]);
}

int main() {
	int input, n;
	scanf("%d %d", &input, &n);

	fan(input, n);
	putchar('\n');
	Convert(input, n);
	putchar('\n');
	fanshen(input, n);

	return 0;
}
