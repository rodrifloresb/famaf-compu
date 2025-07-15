
#include <assert.h>

#include "pair.h"

// Constructors

pair_t pair_new(int x, int y) {
    pair_t res;
    res.fst = x;
    res.snd = y;


    assert(res.fst == x && res.snd == y);
    return res;
}

pair_t pair_destroy(pair_t p) {
    return p;
}

// Operations

int pair_first(pair_t p) {

    return p.fst;
}

int pair_second(pair_t p) {

    return p.snd;
}

pair_t pair_swapped(pair_t p) {
    int aux = p.fst;
    p.fst = p.snd;
    p.snd = aux;

    return p;
}

