// Ejercicio 1 b

#include <stdio.h>
#include <assert.h>

int pedirEntero(void){
	int x;
	printf("Ingrese un valor : ");
	scanf("%d", &x);

	return x;
}

int minimoEntero(int x, int y){
	int minimo;
	if (x <= y)
		minimo = x;
	else
		minimo = y;

	return minimo;
}

int main(void){
	int x, y, minimo;
	x = pedirEntero();
	y = pedirEntero();

	minimo = minimoEntero(x, y);

	assert(minimo <= x && minimo <= y && ( minimo == x || minimo == y));
	printf("El minimo es : %d", minimo);

	return 0;
}
