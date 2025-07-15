#include <stdio.h>

int pedirEntero(void)
 {
  int x;
  printf("Deposite un numero entero : ");
  scanf("%d", &x);

  return x;
 }

  void imprimeEntero(int x)
  {
    printf("El numero es : %d", x );
  }

  int main(void)
  {
    imprimeEntero(pedirEntero());

   return 0;
  }
