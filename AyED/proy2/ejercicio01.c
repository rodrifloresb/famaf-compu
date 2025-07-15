// Ejercicio 1 a

#include <stdio.h>
#include <assert.h>

int pedirEntero(void)
 {
  int n;
  printf("Ingrese cuantas veces quiere imprimir hola : " );
  scanf("%d", &n);
  assert(n > 0);

  return n;
 }

void holaHasta(int n)
{
while (n != 0)
 {
 printf("Hola \n");
  n = n - 1;
 }
}

 int main(){
 holaHasta(pedirEntero());

 return 0;
 }
