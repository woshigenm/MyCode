#include <stdio.h>

void move(char pos1, char pos2)
{
	printf("%c->%c ", pos1, pos2);
}

void hanoi(int n, char pos1, char pos2, char pos3)
{
	if (n == 1) {
		move(pos1, pos3);
		return;
	}
	hanoi(n - 1, pos1, pos3, pos2);
	move(pos1, pos3);
	hanoi(n - 1, pos2, pos1, pos3);

}

int main()
{
	hanoi(8, 'A', 'B', 'C');
	return 0;
}
