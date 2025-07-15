
#include <stdlib.h>
#include <stdio.h>

void swap(int *x, int *y) {
	int p;

	p = *x;
	*x = *y;
	*y = p;
}


int main() {
	int x, y;

	x = 6;
	y = 4;

	printf("%d , %d\n", x, y);

	swap(&x,&y);

	printf("%d , %d\n", x, y);

	return 0;
}