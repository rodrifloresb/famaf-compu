#include <stdio.h>

int main(void)
{
  int x, y;
  x = 7;
  y = 4;

  if (6%2 != 0 && 7%2 == 0) {
    x = x + 6;
    y = y + x;
  }else{
    x = y + x;

 printf("Estados : %d %d\n", x, y );
  }

  printf("Estado Final! : %d %d\n", x, y );

  return 0;
}
