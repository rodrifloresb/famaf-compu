// Ejercicio 9

#include <stdio.h>
#include <assert.h>
#define TAM 5


struct comp_t {
 int menores;
 int iguales;
 int mayores;
};

 struct comp_t cuantos(int a[], int tam, int elem){
   struct comp_t cont;
   cont.menores = 0;
   cont.iguales = 0;
   cont.mayores = 0;

 int i = 0;

 while (i<tam)
 {
  if (a[i]<elem)
  {
   cont.menores = cont.menores + 1;
  }
  if (a[i]==elem)
  {
    cont.iguales+=1;
  }
  if (a[i]>elem)
  {
    cont.mayores+=1;
  }
  i=i+1;
 }
return cont;
}


int pedirEntero(void)
 {
  int n;
  printf("Ingrese un entero : " );
  scanf("%d", &n);
  assert(n > 0);

  return n;
 }


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

 int main(void)
 {

 struct comp_t conteo;
 int N;
 printf("Ingrese el tamanho de su arreglo : ");
 scanf("%d", &N );
 assert(N>0);
 int elem = pedirEntero();
 int array[TAM];
 pedirArreglo(array, N);

 conteo = cuantos(array, N, elem);
 printf("\nLos menores al entero son : %d , los iguales : %d  y los mayores : %d \n", conteo.menores, conteo.iguales, conteo.mayores);


  return 0;
 }
