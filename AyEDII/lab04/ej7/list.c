#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct _list {
    elem_list elem;
    list next;
};

/* Constructores */
list empty() {
    list l = NULL;

    return l;
}

void addl(elem_list e, list * l) {
    list l0 = malloc(sizeof(struct _list));
    l0->elem = e;
    l0->next = *l;
    *l = l0;
}

void addr(elem_list e, list *l) {
    list l0 = malloc(sizeof(struct _list));
    list p = *l;
    
    l0->elem = e;
    l0->next = NULL;

    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = l0;
}

// al usar addr tengo una violacion de segmento.

void destroy(list l) {
    if (l != NULL)
    {
        free(l);
        l = NULL;
    }   
}

/* Operaciones */

bool is_empty(list l) {
    return (l == NULL);
}

elem_list head(list l) {
    assert(!is_empty(l));

    return l->elem;
}

void tail(list l) {
    assert(!is_empty(l));

    list p = l;
    l = l->next;
    p->next = NULL;
    destroy(p);    
}

unsigned int length(list l) {
    unsigned int res = 0;
    list p = l;
    while (p != NULL)
    {
        p = p->next;
        res++;
    }

    return res;
}

void concat(list l, list l0) {
    list p = l;

    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = l0;
}

elem_list index(list l, unsigned int n) {
    
    unsigned int length_list = length(l);
    assert(length_list > n);

    list p = l;    
    elem_list e = l->elem;

    while (n != 0u)
    {
        p = p->next;
        n -= 1;
    }

    e = p->elem;
    
    return e;
}

void take(list l, unsigned int n) {
    unsigned int length_list = length(l);
    assert(length_list > n);

    
    list p = l;
    list q = NULL;    

    while (n != 1u)
    {
        p = p->next;
        n -= 1;
    }

    q = p->next;
    p->next = NULL;
    destroy(q);
}

void drop(list l, unsigned int n) {
    assert(length(l) > n);
    list p = l;  
    list q = NULL;

    while (n != 1u)
    {
        p = p->next;
        n -= 1;
    }

    q = p->next;
    p->next = NULL;
    destroy(l);
    l = q;
}

list copy_list(list l) {
    list l0 = malloc(sizeof(struct _list) * length(l));
    list p = l;
    list q = l0;

    while (p->next != NULL)
    {
        q->elem = p->elem;
        q->next = p->next;
        p = p->next;
        q = q->next;
    }

    q->elem = p->elem;
    q->next = p->next;

    return l0;
}
