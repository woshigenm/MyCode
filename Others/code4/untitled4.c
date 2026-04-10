#include <stdio.h>

int main()
{
	//从键盘输入某个分钟数，将其转换成用小时和分钟表示，并将表示结果输出。
	int minute_all;
	scanf("%d", &minute_all);
	printf("%d(m)=%d(h):%02d(m)\n", minute_all, minute_all / 60, minute_all % 60);
	return 0;
}
