#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  int x, y, a, b, c;
  printf("Ingrese un valor para x :\n ");
  scanf("%d" , &x);
  printf("Ingrese un valor para y :\n ");
  scanf("%d" , &y);

  a= x*x*x*y >= 0;
  b= (!x == (y+1) || !(x && !y));
  c= !x == (x + 2);

  printf("1) : %d \n", a );
  printf("2) : %d \n", b );
  printf("3) : %d \n", c );
 return 0;
}

 /* 1) x = 0 , y = 1
       x = 1 , y = 0
       x = 2 , y = 2

    2) x = 0 , y = 1
       x = 2 , y = 5
       x = 10 , y = 30

    3) x = -2
 */

 // Me tengo que ir, gracias por el simulacro. 
