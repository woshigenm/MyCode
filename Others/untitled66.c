#include <stdio.h>
#include <stdlib.h>

int main() {
	int m, p;
	scanf("%d%d", &m, &p);

	int an;

	int * array = (int *)malloc(sizeof(int) * m);

	int j = 0;

	int a = 0;

	char Operate;
	for(int i = 1; i <= m; ++i) {
		while(getchar() != '\n');
		scanf("%c %d", &Operate, &an);
		if(Operate == 'A') {
			array[j++] = (an + a) % p;
		}

		if(Operate == 'Q') {
			int max = array[j - 1];
			for(int f = j - 1; ; --f) {
				if(array[f] > max)
					max = array[f];
				an--;
				if(!an)
					break;
			}

			printf("%d\n", max);

			a = max;
		}
	}

	free(array);

	return 0;
}

