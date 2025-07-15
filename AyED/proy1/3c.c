#include <stdio.h>
#include <stdbool.h>

int main(void){
  int x, y;
 printf("Ingresa un valor para Y :\n");
 scanf("%d", &y);
 printf("Ingresa un valor para X :\n");
 scanf("%d", &x);

 y=y+y;
 printf("Y vale : %d\n", y);
 x=x+y;
 printf("X vale : %d\n", x);
 return 0;
}

 /* Ejercución 1° : Ingreso y = 1, x = 2
                    Produce y = 2, x = 4

   Ejercución 2° : Ingreso y = 3, x = 1
                   Produce y = 6, x = 7

   Ejercución 3° : Ingreso y = 2, x = 5
                   Produce y = 4, x = 9
 */
