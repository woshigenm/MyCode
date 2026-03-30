#include <stdio.h>

#define SIZE 10

int main() {
	unsigned int array[SIZE] = {0xFFFFFFFF, 0x028C7D4F, 0x0FBE21396, 0x006DD89A, 0x0C1F00421, 0x0B5D780F2, 0x0E24A6B13, 0x05CC94A0E, 0x074FE89C1, 0x09B3A0D55};

	for(int i = 0; i < SIZE; i++)
		;//scanf("%d", &array[i]);

	int t;
	for(int i = 1; i < SIZE; i++) {
		int flag = 0;
		for(int j = 0; j < SIZE - i; j++) {
			if(array[j] < array[j + 1]) {
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
				
				flag = 1;
			}
		}
		if(!flag) break;
	}

//	for(int i = SIZE - 1; i >= 0; i--) {
//		int flag = 0;
//		for(int j = 0; j < SIZE - 1; j++) {
//			if(array[j] > array[j + 1]) {
//				t = array[j];
//				array[j] = array[j + 1];
//				array[j + 1] = t;
//				
//				flag = 1;
//			}
//		}
//		if(!flag) break;
//	}
	
	for(int i = 0; i < SIZE; i++)
		printf("%u ", array[i]);
	return 0;
}

