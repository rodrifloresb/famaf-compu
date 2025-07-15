// Ejercicio  2 B

#include <stdio.h>
#include <assert.h>

int main()
{
  int x,y,a,b;

  printf("Ingrese un valor para x : ");
  scanf("%d",&x);
  printf("Ingrese un valor para y : ");
  scanf("%d" , &y);

  a=x;
  b=y;
  x=a+1;
  y=a+y;

  printf("\n Los valores finales son x: %d , y: %d \n", x, y);

  return 0;
}
