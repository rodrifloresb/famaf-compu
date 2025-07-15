
// ejercicio 1 d
#include <stdio.h>
#include <assert.h>
int main()
{
  int x,y,z,a,b;

  printf("Ingrese x : ");
  scanf("%d",&x);
  printf("Ingrese y : ");
  scanf("%d" , &y);

  a=x;
  b=y;
  z=x;
  x=y;
  y=z;

  assert (x==b && y==a);
  printf("\n Los valores finales son x: %d , y: %d \n", x, y);

  return 0;
}
