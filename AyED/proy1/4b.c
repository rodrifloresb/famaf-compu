#include <stdio.h>

 int main(void){
   int x, y, z, m;
   printf("Ingrese un valor para X :\n");
   scanf("%d", &x);
   printf("Ingrese un valor para Y :\n");
   scanf("%d", &y);
   printf("Ingrese un valor para Z :\n");
   scanf("%d", &z);
   printf("Ingrese un valor para M :\n");
   scanf("%d", &m);

  if (x < y) {
    m = x;
  }else{
    m = y;
  }

  if (m < z) {

  }else{
    m = z;
  }
 printf("El valor de m es : %d\n", m);
   return 0;
 }
