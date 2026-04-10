#include <stdio.h>

int main()
{
	int ji, tu;

	for (ji = 0; ji <= 35; ji++) {
		tu = 35 - ji;
		if (ji * 2 + tu * 4 == 94) {
			printf("共有鸡%d只\n兔%d只\n", ji, tu);
		}
	}
	return 0;
}

