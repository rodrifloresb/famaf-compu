// Ejercicio 7

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool existe_positivo(int a[], int tam){
	bool res = 0;
	int i = 0;
	while (i < tam && !res){
		if (a[i] >= 0){
			res = i;
		}
		i = i + 1;
	}
	return res;
}

bool todos_positivos (int a[], int tam){
	bool res = true;
	int i = 0;
	while (i < tam && res){
		if(a[i] < 0){
			res = false;
		}
		i = i + 1;
	}
	return res;
}

int pedirEntero (void){
	int n;
	printf("Ingrese el numero: ");
	scanf ("%d", &n);
	return n;
}

void pedirArreglo (int a[], int n_max){
	int i = 0;
	int elem;
	while (i < n_max){
	    printf("Ingrese el elemento en la posicion %d : ", i);
	    scanf("%d", &elem);
	    a[i] = elem;
	    i = i+1;
	}

}

int main(){
	int N, array[1000];
	bool existePos, todosPos;
	N = pedirEntero();
	assert(N > 0);
	pedirArreglo(array, N);

	printf("Ingrese 1 si desea ejecutar todos_positivos o otro numero si desea existe_positivo : \n");
	int menu = pedirEntero();
	if (menu == 1){
		todosPos = todos_positivos (array, N);
		printf("todosPos = %d\n", todosPos);
	}else{
		existePos = existe_positivo (array, N);
		printf("existePos = %d\n", existePos);
	}
}
