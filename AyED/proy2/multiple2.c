// Ejercicio  2 B

#include <stdio.h>
#include <assert.h>

int main()
{
  int x,y,z,a,b,c;

  printf("Ingrese un valor para x : ");
  scanf("%d",&x);
  printf("Ingrese un valor para y : ");
  scanf("%d" , &y);
  printf("Ingrese un valor para z : ");
  scanf("%d" , &z);

  a=x;
  b=y;
  c=z;
  x=b;
  y=b+a+c;
  z=b+a;

  printf("\n Los valores finales son x: %d , y: %d , z: %d \n", x, y,z);

  return 0;
}
