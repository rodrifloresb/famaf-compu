
#include <assert.h>

#include "pair.h"

// Constructors

pair_t pair_new(int x, int y) {
    pair_t res;
    res.values[0] = x;
    res.values[1] = y;


    assert(res.values[0] == x && res.values[1] == y);
    return res;
}

pair_t pair_destroy(pair_t p) {
    return p;
}

// Operations

int pair_first(pair_t p) {

    return p.values[0];
}

int pair_second(pair_t p) {

    return p.values[1];
}

pair_t pair_swapped(pair_t p) {
    int aux = p.values[0];
    p.values[0] = p.values[1];
    p.values[1] = aux;

    return p;
}

