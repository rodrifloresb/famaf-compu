// Ejercicio  3

#include <stdio.h>

int pedirEntero(void){
	int N;
	printf("Ingrese un valor : ");
	scanf("%d", &N);

	return N;
}

int suma_hasta(int N){
int a,b;
a = 1;
b = 0;
while (a <= N) {
  b = b + (a+1);
  a = a + 1;
 }
return b;
}

int main (void){
	int num, res;
	num = pedirEntero();

	if (num < 0){
		printf("Error!. El numero es negativo.\n");
	}
	else {
		res = suma_hasta(num);
		printf("La sumatora desde 1 hasta %d es: %d", num, res);
	}

	return 0;
}
