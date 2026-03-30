#include <stdio.h>

#define ON 0

int main()
{
	int array[] = {-1, 1, 2, 23, 45, 123, 456, 512, 345};

	int size = sizeof(array) / sizeof(array[0]);

	int i, j, k;
	for(i = 0; i < size - 1; i++)
	{
		k = i;
		for(j = i + 1; j < size; j++)
		{
			#if ON == 1
			if(array[j] > array[k])
			{
				k = j;
			}
			#else
			if(array[j] < array[k])
			{
				k = j;
			}
			#endif
		}

		int tmp = array[i];
		array[i] = array[k];
		array[k] = tmp;
	}

	for(i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}

	int start, mid, end;

	start = 0;

	end = size - 1;

	int target;

	scanf("%d", &target);

	while(start <= end)
	{
		mid = (start + end) / 2;

		if(array[mid] == target)
		{
			break;
		}


		if(array[mid] > target)
		{


			#if ON == 1
			start = mid + 1;
			#else
			end = mid - 1;
			#endif
		}

		if(array[mid] < target)
		{
			#if ON == 1
			end = mid - 1;
			#else
			start = mid + 1;
			#endif

		}
	}

	if(start > end)
	{
		printf("没找到\n");
	}
	else
	{
		printf("%d找到了在%d\n", target, mid);
	}
	return 0;
}
