#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    unsigned int minprior;
    node *array;
};

struct s_node
{
    unsigned int elem;
    node next;
};

static struct s_node *create_node(pqueue_elem e)
{
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    struct s_node *p = node;
    if (node != NULL)
    {
        while (p->next != NULL)
        {
            p = p->next;
            free(node);
            node = p;
        }
        free(p);
    }
    node = NULL;
    p = NULL;
    return node;
}

static bool invrep(pqueue q)
{
    bool res = (q != NULL);
    return res;
}

pqueue pqueue_empty(priority_t min_priority)
{
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority + 1, sizeof(struct s_pqueue));
    q->size = 0;
    q->minprior = min_priority;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e);

    if (priority <= q->minprior)
    {
        if (q->array[priority] == NULL)
        {
            q->array[priority] = new_node;
        }else{
            struct s_node *p = q->array[priority];
            while (p->next != NULL)
            {
                p = p->next;  
            }
                p->next = new_node;
        }
        q->size++;
    }

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    bool b = (q->size == 0);
    return b;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem e;
    unsigned int i = 0u;
    bool found = false;

    while (i <= q->minprior && !found)
    {
        if (q->array[i] != NULL)
        {
            e = q->array[i]->elem;
            found = true;
        }

        i++;
    }

    return e;
}

priority_t pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p;
    unsigned int i = 0u;
    bool found = false;

    while (i <= q->minprior && !found)
    {
        if (q->array[i] != NULL)
        {
            p = i;
            found = true;
        }

        i++;
    }

    return p;
}

size_t pqueue_size(pqueue q)
{
    assert(invrep(q));
    size_t s;
    s = q->size;
    return s;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;
    bool found = false;
    while (i <= q->minprior && !found)
    {
        if (q->array[i] != NULL)
        {
            struct s_node *p = q->array[i];
            q->array[i] = q->array[i]->next;
            p->next = NULL;
            destroy_node(p);
            found = true;
        }
        i++;
    }
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));

    for (size_t i = 0; i <= q->minprior; i++)
    {
        if (q->array[i] != NULL)
        {
            destroy_node(q->array[i]);
        }
    }

    free(q->array);
    q->array = NULL;
    free(q);
    q = NULL;
    return q;
}


