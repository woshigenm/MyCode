#include <stdio.h>

void Binary(int x) {
	int t = x % 2;

	if (x > 1)	Binary(x / 2);

	putchar(t == 1 ? '1' : '0');
}

#define N 32

void convert() {
	char arr[N];
	int x, n;

	scanf("%d%d", &x, &n);
	int t = x;

	int i = 0;
	while (t) {
		int s = t % n;

		if (s > 9 && s < 16)
			arr[i] = 'A' - 10 + s;
		else	arr[i] = '0' + s;

		t /= n;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
		putchar(arr[j]);
}

int main() {
	convert();
	return 0;
}
