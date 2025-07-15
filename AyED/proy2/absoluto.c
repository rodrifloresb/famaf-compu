// Ejercicio 1 c

#include <stdio.h>
#include <assert.h>

int pedirEntero(void){
	int x;
	printf("Ingrese un valor : ");
	scanf("%d", &x);

	return x;
}

int absoluto(int x){
 int abs;
	if (x >= 0) {
    abs = x;
  }
  else{
  abs = -x;
 }
return abs;
}

int main(void){
	int x, abs;
 x = pedirEntero();
 abs = absoluto(x);

 assert (( abs == x || abs == x * (-1)) && abs >= 0);

 printf("El minimo es : %d", abs);

	return 0;
}
