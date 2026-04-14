#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int look_substr(const char str1[], const char str2[])
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	int i, j;
	for (i = 0; i <= len1 - len2; i++) {
		for (j = 0; j < len2; j++) {
			if (str2[j] != str1[i + j])
				break;
		}

		if (j == len2)	return i;
	}

	return -1;
}

int look_substrs(const char str1[], const char str2[])
{
	return strlen(str1) < strlen(str2) ? -1 : strpbrk(str1, str2) - str1;
}

int special_look_substrs(const char str1[], const char str2[])
{
	return strlen(str1) < strlen(str2) ? -1 : strstr(str1, str2) - str1;
}

int main()
{
	const char str1[] = "113";
	const char str2[] = "13";

	printf("index %d %d %d\n", look_substr(str1, str2), look_substrs(str1, str2), special_look_substrs(str1, str2));
}
