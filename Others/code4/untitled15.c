#include <stdio.h>

int main() {
	int a, n;
	scanf("%d%d", &a, &n);
	int sum = 0;
	
	int i;
	
	//aaa - aa - a
	int an = 0;
	for(i = 1; i < n; i++)
	{
		an = an * 10 + a;
		sum -= an;
	}
	
	sum += an * 10 + a;
	
	printf("%d", sum);
	
	return 0;
}
