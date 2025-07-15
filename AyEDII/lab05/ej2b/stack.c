#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    nodos next;
};

struct _size_stack {
    nodos stack;
    unsigned int length;
};
 
// El primer elem en el primer nodo va a ser el largo de la pila.

static bool invrep(stack s) {
    return (s->stack != NULL && s->length == 0);
}

stack stack_empty() {
    stack s = malloc(sizeof(struct _size_stack));
    s->stack = NULL;
    s->length = 0u;

    return s;
}

stack stack_push(stack s, stack_elem e) {
    nodos new_nodo = malloc(sizeof(struct _s_stack));
    
    if (new_nodo == NULL)
    {
        printf("Error al resevar memoria \n");
        exit(EXIT_FAILURE);
    }

    new_nodo->elem = e;
    new_nodo->next = s->stack;
    
    s->stack = new_nodo;
    s->length++;

    return s;
}

stack stack_pop(stack s) {
    assert(!invrep(s));

    nodos aux_nodo = s->stack;
    s->stack = s->stack->next;
    
    aux_nodo->next = NULL;
    free(aux_nodo);
    aux_nodo = NULL;

    s->length--;

	return s;
}

unsigned int stack_size(stack s) {
    
    return s->length;
}

stack_elem stack_top(stack s) {
    assert(!invrep(s));

    return (s->stack)->elem;
}

bool stack_is_empty(stack s) {
    
    return (s->stack == NULL && s->length == 0);
}

stack_elem *stack_to_array(stack s) {
    nodos aux_nodo = s->stack;
    stack_elem *res = NULL;
    unsigned int length = stack_size(s);

    if (!stack_is_empty(s))
    {
        res = calloc(length, sizeof(stack_elem));
        for (unsigned int i = 0; i < length; i++)
        {
            res[length-i-1] = aux_nodo->elem;
            aux_nodo = aux_nodo->next;
        }
    }
    
    return res;
}

stack stack_destroy(stack s) {
    nodos aux_nodo = s->stack;
    nodos aux2_nodo = NULL;
    
    free(s);
    s = NULL;


    while (aux_nodo != NULL) {
        aux2_nodo = aux_nodo->next;
        free(aux_nodo);
        aux_nodo = aux2_nodo;
    }

    return s;
}