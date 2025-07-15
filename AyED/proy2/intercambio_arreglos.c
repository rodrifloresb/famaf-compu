// Ejercicio 8

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int pedirEntero (void){
	int n;
	printf("Ingrese el numero : ");
	scanf ("%d", &n);
	return n;
}

void pedirArreglo (int a[], int n_max){
	int i = 0;
	int elem;
	while (i < n_max){
	    printf("Ingrese el elemento en la posicion %d :", i);
	    scanf("%d", &elem);
	    a[i] = elem;
	    i = i+1;
	}

}
void imprimeArreglo(int a[], int n_max){
    int i = 0;
	while (i < n_max){
		printf("%d ", a[i]);
		i = i+1;
	}
    printf("\n");
}

void intercambiar(int a[], int tam, int i, int j){
	int z;
	z = a[i];
    a[i]= a[j];
    a[j] = z;
}

int main(void){
	int N, array[1000], lugar1, lugar2;
	printf("Ingrese el tamanho del arreglo : "); scanf("%d",&N);
	assert(N > 0);
	pedirArreglo (array, N);
	printf("Ingrese el lugar que va a cambiar\n");
	scanf("%d", &lugar1);
	scanf("%d", &lugar2);
	assert(0 <= lugar1 && 0 <= lugar2 && lugar1 < N && lugar2 < N);
	intercambiar(array, N, lugar1, lugar2);
	printf("Su arreglo modificado es \n");
	imprimeArreglo(array, N);

	return 0;
}
