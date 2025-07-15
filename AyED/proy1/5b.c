#include <stdio.h>
#include <assert.h>

 int main(void)
 {
   int x, y, i;
   printf("Ingrese un valor para x :\n");
   scanf("%d", &x);
   printf("Ingrese un valor para y :\n");
   scanf("%d", &y);

   i = 0;
   while (x >= y) {
     x = x - y;
     i = i + 1;

    printf("El valor de x, y e i son : (x=%d), (y=%d) e (i=%d)\n"
    , x, y , i);
  }

  printf("Estado final : (x=%d), (y=%d) e (i=%d)\n"
  , x, y , i);

   return 0;
 }
