// Ejercicio 5

#include <stdio.h>
#include <assert.h>

void pedirArreglo (int a[], int n_max){
	int i = 0;
	int elem;
	while (i < n_max){
	    printf("Ingrese el elemento en la posicion numero %d : ", i);
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

int main(void){
	int N, array[1000];
	printf("Ingrese el tamanho del arreglo : "); scanf("%d",&N);
	assert(N > 0 && N <= 1000);
	pedirArreglo (array, N);
	printf("Su arreglo es : ");
	imprimeArreglo(array, N);

	return 0;
}
