#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SIZE 10

int main()
{
	unsigned array[SIZE] = {0xFFFFFFFF, 0x28C7D4F, 0xFBE21396, 0x6DD89A, 0xC1F00421,
	                        0xB5D780F2, 0xE24A6B13, 0x5CC94A0E, 0x74FE89C1, 0x9B3A0D55
	                       };



	for (int i = 0; i < SIZE; i++)
		; //scanf("%d", &array[i]);

	for (int i = 0; i < SIZE - 1; i++) {
		int index = i;
		for (int j = i + 1; j < SIZE; j++) {
			if (array[index] > array[j]) {
				index = j;
			}
		}

		if (index != i) {
			int t = array[i];
			array[i] = array[index];
			array[index] = t;
		}
	}

	for (int i = 0; i < SIZE; i++)
		printf("%u ", array[i]);
	return 0;
}

