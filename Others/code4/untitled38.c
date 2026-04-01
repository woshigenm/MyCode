//【求总天数】输入某年，某月，某日，求这一天是这一年的第几天，输入输出格式如下。
#include <stdio.h>

int leap_year(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;

	return 0;
}
int main() {
	int year, month, day;
	scanf("%d%d%d", &year, &month, &day);

	int sum = day;
	switch (month - 1) {
		case 11:
			sum += 31;
		case 10:
			sum += 30;
		case 9:
			sum += 31;
		case 8:
			sum += 30;
		case 7:
			sum += 31;
		case 6:
			sum += 31;
		case 5:
			sum += 30;
		case 4:
			sum += 31;
		case 3:
			sum += 30;
		case 2:
			sum += 31;
		case 1:
			sum += leap_year(year) ? 29 : 28;
	}

	printf("第%d天\n", sum);
	return 0;
}
