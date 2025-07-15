#include <stdio.h>

 int main(void){
  int x, y;
  printf("Ingrese un valor para x :\n");
  scanf("%d", &x);
  printf("Ingrese un valor para y :\n");
  scanf("%d", &y);

  if (x >= y) {
    x=0;
 }
  else{
    x=2;
  }

  printf("El valor de x es : %d\n", x);
  return 0;
 }

 /* El ejercicio 1.e) toma los valores:
    x:=3 , y:=1. Por lo tanto el resultado es
    x = 0.

    En el 1.f) los valores que se toman son:
    x:= -100 , y:=1. Por lo tanto el resultado es
    x = 2.
 */
