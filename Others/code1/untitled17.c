#include <stdio.h>

#define SIZE 10

int main()
{
	int array[SIZE];
	
	int i, j, k;
	for(i = 0; i < SIZE; i++)
	{
		scanf("%d", &array[i]);
	}
	
	for(i = 0; i < SIZE - 1; i++)
	{
		k = i;
		for(j = i + 1; j < SIZE; j++)
		{
			if(array[j] > array[k])
			{
				k = j;
			}
		}
		
		int tmp = array[i];
		array[i] = array[k];
		array[k] = tmp;
	}
	
	for(i = 0; i < SIZE; i++)
	{
		printf("%d ", array[i]);
	}
	return 0;
}

