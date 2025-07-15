#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

// Constructores

counter counter_init(void) {
    counter res = malloc(sizeof(struct _counter));
    res->count = 0;

    assert(counter_is_init(res));
    return res;
}

void counter_destroy(counter c) {
    if (c != NULL)
    {
        free(c);
        c = NULL;
    }
}

// Operaciones

void counter_inc(counter c) {
    c->count += 1;
}

bool counter_is_init(counter c) {
    return (c->count == 0);
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));

    c->count -= 1;    
}

counter counter_copy(counter c) {
    counter copy = malloc(sizeof(struct _counter));

    copy->count = c->count;

    return copy;
}
