#include <stdio.h>

int main()
{
	int slow, fast;
	int array[] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 6};
	int length = sizeof(array) / sizeof(*array);
	for (slow = fast = 1; fast < length; fast++) {
		if (array[fast] != array[fast - 1]) {
			array[slow++] = array[fast];
		}
	}

	for (int p = 0; p < slow; ++p)
		printf("%d ", array[p]);
	return 0;
}

/*
for (slow = 0, fast = slow + 1; fast < length; fast++) {
if (array[slow] != array[fast]) {
array[++cur] = array[fast];
slow = fast;
}
}
*/
