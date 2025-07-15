#include <stdio.h>
#include <stdbool.h>

 int main(void)
 {
   int x, i;
   int res;
 printf("Ingrese un valor para x :\n");
 scanf("%d", &x );

 i = 2 ;
 res = true ;

 while (i < x && res) {
   res = res && ( (x % i) != 0);
   i = i + 1;

   printf("Estados : %d %d %d\n", x, i, res );
 }

  printf(" %d es primo? %d\n", x, res );

  return 0;
 }
