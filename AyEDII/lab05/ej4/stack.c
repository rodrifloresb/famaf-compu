#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CAPACITY_INIT 10

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool invrep(stack s) {
    return (s != NULL && s->elems != NULL && s->size < s->capacity);
}

stack stack_empty() {
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = calloc(CAPACITY_INIT, sizeof(stack_elem));
    s->size = 0;
    s->capacity = CAPACITY_INIT;

    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));

    if (s->capacity == s->size)
    {
        s->elems = realloc(s->elems, 2 * sizeof(stack_elem));
        s->capacity = 2 * s->capacity;
    }

    s->elems[s->size] = e;
    s->size++;
    
    assert(invrep(s));

    return s;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    s->size--;
    
    return s;
}

unsigned int stack_size(stack s){
    unsigned int res = s->size;
    return res;
}

stack_elem stack_top(stack s) {
    assert(invrep(s));
    stack_elem res = s->elems[s->size-1];

    return res;
}

bool stack_is_empty(stack s) {
    bool res = (s->size == 0);

    return res;
}

stack_elem *stack_to_array(stack s) {
    stack_elem *res = NULL;

    if (s->size != 0)
    {
        res = calloc(s->size, sizeof(stack_elem));

        for (unsigned int i = 0; i < s->size; i++)
        {
            res[i] = s->elems[i];    
        }
    }

    return res;
}


stack stack_destroy(stack s) {
    assert(invrep(s));
    free(s->elems);
    s->elems = NULL;
    free(s);
    s = NULL;

    return s;
}