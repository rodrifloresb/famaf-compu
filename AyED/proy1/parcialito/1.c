// a)

#include <stdio.h>

 int main(void)
 {
   int x, y, z;
   printf("Ingrese un valor para x :\n ");
   scanf("%d" , &x);
   printf("Ingrese un valor para y :\n ");
   scanf("%d" , &y);
   printf("Ingrese un valor para z :\n ");
   scanf("%d" , &z);

   while (0 < y) {
     z = x*y;
     y = y-1;
     printf("Estados: x= %d , y= %d , z= %d \n", x, y , z);
   }
   printf(" Estado final! : x= %d , y= %d , z= %d \n", x, y, z);
   return 0;
 }


 /* b)
   El programa le asigna a z el valor que del producto entre
   x e y, a su vez resta un unidad a y hasta que no se cumple
   la condicion (0 < y).

   z := 2
 */

 /* c)
 Estado 1: x= 2 , y= 3 , z= 8
 Estado 2: x= 2 , y= 2 , z= 6
 Estado 3: x= 2 , y= 1 , z= 4
 Estado 4: x= 2 , y= 0 , z= 2
 Estado final : x= 2 , y= 0 , z= 2

*/
