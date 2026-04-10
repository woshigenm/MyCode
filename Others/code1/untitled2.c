#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		int * array = (int *)malloc(sizeof(int) * n);
		memset(array, 0, sizeof(int) * n);

		int i;

		int count = 0;

		int special = 0;

		i = 0;
		while (special != (n - 1)) {
			if (array[i % n] != 1) count++;

			if (count == m) {
				array[i % n] = 1;
				special++;
				count = 0;
			}
			i++;
		}

		for (i = 0; i < n; i++)	if (array[i] != 1) printf("%d是猴王\n", i + 1);
		free(array);
	}
	return 0;
}
