// ejercicio4.c
#include <stdio.h>
#include <assert.h>

struct div_t {
int cociente;
int resto;
};

struct div_t division(int x , int y)
{
struct div_t div1;
int q;
q = 0;

while (x >= y)
{
    x = x - y;
    q = q + 1;
}

div1.cociente = q;
div1.resto = x;
return div1;
}


int main (void)
{
    int x;
    int y;
    struct div_t div;

printf (" x = dividendo , y = divisor \n");
printf ("Ingrese un numero para X y otro para Y : ");
scanf ("%d %d" , &x , &y);

assert (x > 0 && y > 0);
div=division (x, y);

division (x,y);

printf ("\nEl cociente es: %d \n", div.cociente);
printf ("El resto es: %d \n", div.resto);
}
