#include <stdio.h>

int FANXIAOCHAO_HUIWENSHU(int fan)
{
	int tmp = fan;
	int sum = 0;
	while (tmp) {
		sum = sum * 10 + tmp % 10;
		tmp /= 10;
	}

	if (sum == fan)	return 1;
	return 0;
}

int main()
{
	int fanxiaochao;
	scanf("%d", &fanxiaochao);

	if (FANXIAOCHAO_HUIWENSHU(fanxiaochao)) {
		printf("%d 是回文数\n", fanxiaochao);
	} else {
		printf("%d 不是回文数\n", fanxiaochao);
	}
}
