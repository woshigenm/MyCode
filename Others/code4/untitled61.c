#include <stdio.h>
#define SIZE 10

void swap(int * a, int * b);

int main()
{
	int array[SIZE];
	int i, j;

	while(scanf("%d", &array[0]) != EOF)
	{
		for(i = 1; i < 10; i++)
			scanf("%d", &array[i]);

		for(i = 0, j = 0; i < SIZE; i++)
		{
			if(array[i] % 2 != 0)
			{
				swap(&array[i], &array[j++]);
			}
		}

		int fanxiaochao = j;

		int m, c;
		for(i = 1; i < fanxiaochao; i++)
		{
			m = 0;
			for(j = 0; j < fanxiaochao - i; j++)
			{
				if(array[j] < array[j + 1])
				{
					swap(&array[j], &array[j + 1]);
					m = 1;
				}
			}

			c = 0;
			for(j = fanxiaochao; j < SIZE - i; j++)
			{
				if(array[j] > array[j + 1])
				{
					swap(&array[j], &array[j + 1]);
					c = 1;
				}
			}

			if(!c && !m) break;
		}

		for(i = 0; i < SIZE; i++)
		{
			printf("%d ", array[i]);
		}
		putchar('\n');
	}

	return 0;
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
