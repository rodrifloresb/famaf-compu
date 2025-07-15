#include <stdlib.h>
#include <assert.h>

#include "pair.h"

// Constructors

pair_t pair_new(int x, int y) {
    pair_t res;
    res = malloc(sizeof(pair_t));

    res->fst = x;
    res->snd = y;
    
    assert(res->fst == x && res->snd == y);

    return res;
}

pair_t pair_destroy(pair_t p) {
    
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }
    
    return p;
}


// Operations

int pair_first(pair_t p) {

    return p->fst;
}

int pair_second(pair_t p) {

    return p->snd;
}

pair_t pair_swapped(pair_t p) {
    pair_t res = NULL;
    res = malloc(sizeof(pair_t));

    res->fst = p->snd;
    res->snd = p->fst;

    return res;
}
