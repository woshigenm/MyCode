//【某月的天数】输入某年某月，求这一个月有多少天。

#include <stdio.h>

int leap_year(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;

	return 0;
}
int main()
{
	int year, month;
	scanf("%d%d", &year, &month);
	int sum;
	switch (month) {
		case 4:
		case 6:
		case 9:
		case 11:
			sum = 30;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			sum = 31;
			break;
		case 2:
			sum = leap_year(year) ? 29 : 28;
	}

	printf("该月有%d天\n", sum);
	return 0;
}
