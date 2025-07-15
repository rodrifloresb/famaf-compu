#include <stdio.h>
#include <assert.h>

 int main(void)
 {
   int i;
   printf("Ingrese un valor para I :\n");
   scanf("%d", &i);
   assert(i >= 0);

   while (i != 0) {
     i = i - 1;

    printf("El valor de i es : %d\n", i );
   }

   return 0;
 }
