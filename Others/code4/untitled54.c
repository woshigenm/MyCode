#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 51

int test(char * arr);

int main()
{
	int m;
	scanf("%d", &m);

	getchar();

	for (int i = 1; i <= m; i++) {
		char * arr = (char *)malloc(sizeof(char) * SIZE);
		fgets(arr, SIZE, stdin);
		if (test(arr)) {
			printf("YES\n");
		} else printf("NO\n");
	}

	return 0;
}

int test(char * arr)
{
	if (strlen(arr) < 8 || strlen(arr) > 16) {
		return 0;
	}

	int count = 0;

	int flag_alpah_d = 0, flag_num = 0, flag_alpah_x = 0, flag_other = 0;

	for (int i = 0; arr[i] != '\n'; i++) {
		if (!flag_alpah_d && (arr[i] >= 'A' && arr[i] <= 'Z')) {
			count++;
			flag_alpah_d = 1;
		}

		if (!flag_alpah_x && (arr[i] >= 'a' && arr[i] <= 'z')) {
			count++;
			flag_alpah_x = 1;
		}

		if (!flag_num && arr[i] >= '0' && arr[i] <= '9') {
			count++;
			flag_num = 1;
		}

		if (!flag_other && (arr[i] == '~' || arr[i] == '!' || arr[i] == '@' || arr[i] == '#' || arr[i] == '$' || arr[i] == '%' || arr[i] == '^')) {
			count++;
			flag_other = 1;
		}

		if (count == 3) {
			return 1;
		}
	}

	return 0;
}
