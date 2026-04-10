#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
	int x;
	int y;
} Point;

Point CreatePoint(int x, int y)
{
	Point TempPoint;
	TempPoint.x = x;
	TempPoint.y = y;

	return TempPoint;
}

int main()
{
	Point p1 = CreatePoint(1, 2);
	Point *pp = (Point *)malloc(sizeof(struct Point));
	pp->x = 1;
	pp->y = 2;

	printf("(%d,%d)\n", pp->x, pp->y);
}
