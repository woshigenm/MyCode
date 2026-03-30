//【星期的判定】编程实现：输入今天是星期几（1—7,7代表星期日），求x天后星期几？
#include <stdio.h>

int main() {
	int week, day;
	scanf("%d%d", &week, &day);

//	char arr[] = "日一二三四五六";
//
//	printf("星期%c%c", arr[2 * ((week + day) % 7)], arr[2 * ((week + day) % 7) + 1]);

	switch ((week + day) % 7) {
		case 1:
			printf("星期一\n");
			break;
		case 2:
			printf("星期二\n");
			break;
		case 3:
			printf("星期三\n");
			break;
		case 4:
			printf("星期四\n");
			break;
		case 5:
			printf("星期五\n");
			break;
		case 6:
			printf("星期六\n");
			break;
		case 0:
			printf("星期日\n");
	}
	return 0;
}
