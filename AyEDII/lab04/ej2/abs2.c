#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x >= 0)
    {
        *y = x;
    } else {
        *y = -x;
    }

}

int main(void) {
    int a=0, res=0;  
    int *p;
    p = NULL;

    p = &a;
    *p = -10;

    p = &res;

    absolute(a, p);

    printf("resultado : %d \n", res);
    
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

// el int *y que toma como parametro absolute() es de tipo in/out.
