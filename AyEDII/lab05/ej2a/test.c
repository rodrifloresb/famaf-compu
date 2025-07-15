#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void test_stack_pop(stack s) {
    s = stack_pop(s);

    printf("length : %u \n", stack_size(s));
}

void test_stack_push(stack s) {
    if (stack_is_empty(s))
    {
        s = stack_push(s,4);

        printf("length : %u \n", stack_size(s));
    }   
}

void test_stack_to_array(stack s) {
    bool res1 = true;
    bool res2 = true;
    unsigned int length = stack_size(s);
    stack_elem *arr = stack_to_array(s);

    if (arr != NULL)
    {
        res1 = false;

    }
    
    for (unsigned int  i = 0; i < length; i++)
    {
        if (arr[length-i-1] != stack_top(s))
        {
            res2 = false;
        }
        s = stack_pop(s);
    }

    printf("Devuelve NULL : %s \n", res1 ? "SI" : "NO");
    printf("Orden correcto : %s \n", res2 ? "SI" : "NO");
}

int main() {
    stack s = stack_empty();
    stack s2 = stack_empty();

    s = stack_push(s, 3);
    test_stack_pop(s);


    test_stack_push(s2);

    stack_push(s, 9);
    test_stack_to_array(s); // [3,9]

    test_stack_to_array(s2); // Pila vacía

    // Va a tener memory leaks

    return EXIT_SUCCESS;
}