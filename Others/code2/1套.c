#include <stdio.h>

/*
1高考真题第一问
输出样例
101 111 121 131 141 151 161 171 181 191 202 212 222 232 242 252 262 272 282 292 303 313 323 333 343 353 363 373 383 393 404 414 424 434 444 454 464 474 484 494 505 515 525 535 545 555 565 575 585 595 606 616 626 636 646 656 666 676 686 696 707 717 727 737 747 757 767 777 787 797 808 818 828 838 848 858 868 878 888 898 909 919 929 939 949 959 969 979 989 999
*/
void test_1() {
	int i;
	for (i = 100; i <= 999; i++) {
		int t = i;
		int sum = 0;
		while (t) {
			sum = sum * 10 + t % 10;
			t /= 10;
		}

		if (sum == i) {
			printf("%d ", i);
		}
	}
}

/*
1高考真题第二问
输入输出样例
678
9

1
0

114514
-1
*/
void test_2() {
	int array[10] = {1, 7, 9, 20, 21, 67, 89, 145, 345, 678};
	int x;
	scanf("%d", &x);

	int low, mid, high;
	low = 0;
	high = 9;

	while (low <= high) {
		mid = (low + high) / 2;

		if (x > array[mid])
			low = mid + 1;

		if (x == array[mid])
			break;
		
		if (x < array[mid])
			high = mid - 1;
	}
	
	if(low > high)
		printf("-1\n");
	else
		printf("%d\n", mid);
}

int main() {
	test_2();
	return 0;
}
