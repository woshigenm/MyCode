#include <stdio.h>

int main() {
	float score;
	scanf("%f", &score);
	
	switch ((int)score / 10) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		printf("不合格\n");
		break;
	case 7:
		printf("合格\n");
		break;
	case 8:
		printf("良好\n");
		break;
	case 9:
		
	case 10:
		printf("优秀\n");
		break;
	default:
		printf("输入错误\n");
		
	}
	return 0;
}
