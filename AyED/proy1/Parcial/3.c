#include <stdio.h>

int pedirEntero(void)
 {
  int x;
  printf("Deposite un numero entero : ");
  scanf("%d", &x);

  return x;
 }

 int main(void)
 {
   int x, y, i;
   int res;
   printf("Ingrese un valor para x \n");
   x=pedirEntero();
   printf("Ingrese un valor para y \n");
   y=pedirEntero();
   printf("Ingrese un valor para i \n");
   i=pedirEntero();
   printf("Ingrese un valor para res \n");
   res=pedirEntero();

  while (i != x + 1) {
    i = i + 1;
    y = y + i;
    if (i%2 == 0) {
      y = y - 1;
    }else{
    }
    printf("Estados : %d %d %d\n", x, y, i, res);
  }
  res = y * 2 + x%2;

  printf("Estado Final! : %d %d %d %d\n", x, y, i, res );

  return 0;
 }
