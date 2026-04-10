/*
【n若干变化次数】一个正整数n,若其为奇数,则变换成3*n+1;若其为偶数,则变换成n/2.经过若干次变换,能变成1。
如3->10->5->16->8->4->2->1，输入任意一个数n，计算2至少经过多少次变换,才能变成1，输入输出格式如下。
*/
#include <stdio.h>

int main()
{
	int n;

	scanf("%d", &n);

	int counter = 0;

	while (n != 1) {
		printf("%d->", n);
		if (n % 2 != 0) {
			n = 3 * n + 1;
		} else {
			n = n / 2;
		}
		counter++;
	}
	printf("%d\n", n);

	printf("经过%d次变化变为1", counter);

	return 0;
}
