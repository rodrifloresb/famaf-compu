#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    stack next;
};
 
stack stack_empty() {
    stack res = NULL;

    return res;
}

stack stack_push(stack s, stack_elem e) {
    stack res = malloc(sizeof(struct _s_stack));
    
    if (res == NULL)
    {
        printf("Error al resevar memoria \n");
        exit(EXIT_FAILURE);
    }

    res->elem = e;
    res->next = s;

    return res;
}

stack stack_pop(stack s) {
    assert(s != NULL);

	stack res = s;
	s = s->next;
	free(res);
	res = NULL;	

	return s;
}

unsigned int stack_size(stack s) {
    unsigned int res = 0;
    stack aux = s;

    while (aux != NULL)
    {
        res++;
        aux = aux->next;
    }

    aux = NULL;

    return res;
}

stack_elem stack_top(stack s) {
    assert(s != NULL);

    return s->elem;
}

bool stack_is_empty(stack s) {
    
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    stack aux = s;
    stack_elem *res = NULL;
    unsigned int length = stack_size(s);

    if (!stack_is_empty(s))
    {
        res = calloc(length, sizeof(stack_elem));
        for (unsigned int i = 0; i < length; i++)
        {
            res[length-i-1] = aux->elem;
            aux = aux->next;
        }
    }
    
    return res;
}

stack stack_destroy(stack s) {

    while (s != NULL) {
        stack aux = s->next;
        free(s);
        s = aux;
    }

  return NULL;
}