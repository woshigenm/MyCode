#include <stdio.h>
#include <math.h>

int FANXIAOCHAO_TONGGOUSHU(int fan) {
	int k = 1;
	int temp = fan;
	for(int i = 1; temp != 0; i++) {
		k *= 10;
		temp /= 10;
	}

	if((fan * fan) % k == fan) return 1;

	return 0;
}

int main() {
	int fanxiaochao;
	scanf("%d", &fanxiaochao);

	if(FANXIAOCHAO_TONGGOUSHU(fanxiaochao)) {
		printf("%d 是同构数\n", fanxiaochao);
	} else {
		printf("%d 不是同构数\n", fanxiaochao);
	}
}
