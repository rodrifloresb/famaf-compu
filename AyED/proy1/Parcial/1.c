#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  int x, y, a, b, c, d;
  bool z;
  printf("Ingrese un valor para x : \n ");
  scanf("%d" , &x);
  printf("Ingrese un valor para y : \n ");
  scanf("%d" , &y);
  printf("Ingrese un valor para z : \n ");
  scanf("%d" , &z);

 a= (x == 7 + 6 || y == 7 + 6 || z);
 b= ((7 + 6 + x)%3);
 c= x * 7 + y * 6;
 d= (x != 0) && 0 <= (7 - 6)/x && z;

printf("\n");
  printf("El resultado de la primera ecuacion es :%d\n" , a);
  printf("El resultado de la segunda ecuacion es :%d\n" , b);
  printf("El resultado de la tercera ecuacion es :%d\n" , c);
  printf("El resultado de la cuarta ecuacion es :%d\n" , d);

return 0;
}
