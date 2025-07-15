
#include <stdbool.h>
#include <stdio.h>

#include "string.h"

int main() {
    string var = string_create("Hola");
    string var2 = string_create("Como estas?");

    printf("largo de la palabra %u \n", string_length(var));

    if (string_less(var, var2))
    {
        printf("var es 'menor' que var2 \n");
    } else {
        printf("var es 'mayor' que var2 \n");
    }

    if (string_eq(var, var2)) {
        printf("var es igual a var2 \n");
    } else {
        printf("var no es igual a var2 \n");
    }

    var = string_destroy(var);
    var2 = string_destroy(var2);

    return 0;
}
