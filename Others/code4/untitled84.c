#include <stdio.h>

int FANXIAOCHAO_SHUIXIANHUASHU(int fan) {
	if (fan < 100 || fan > 1000)
		return 0;

	int bai_wei = fan / 100;
	int shi_wei = fan / 10 % 10;
	int ge_wei = fan % 10;
	if (bai_wei * bai_wei * bai_wei + shi_wei * shi_wei * shi_wei + ge_wei * ge_wei * ge_wei == fan) {
		return 1;
	}

	return 0;
}

int main() {
	int fanxiaochao;
	scanf("%d", &fanxiaochao);

	if (FANXIAOCHAO_SHUIXIANHUASHU(fanxiaochao)) {
		printf("%d 是水仙花数\n", fanxiaochao);
	} else {
		printf("%d 不是水仙花数\n", fanxiaochao);
	}
}
