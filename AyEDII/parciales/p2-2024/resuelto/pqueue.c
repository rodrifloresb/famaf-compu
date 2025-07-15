#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "character/character.h"
#include "pqueue.h"

/* ============================================================================
STRUCTS!
============================================================================ */
typedef struct s_node * node;

struct s_pqueue {
  unsigned int size;
  node first;
};

struct s_node {
  Character personaje;
  float priority;
  node next;
};


/* ============================================================================
INVREP
============================================================================ */

static bool invrep(pqueue q) {
  bool inv = (q != NULL);
  return inv;
}

/* ============================================================================
NEW
============================================================================ */

pqueue pqueue_empty(void) {
  pqueue q = malloc(sizeof(struct s_pqueue));
  q->size = 0u;
  q->first = NULL;

  return q;
}

/* ============================================================================
ENQUEUE
============================================================================ */

static float calculate_priority(Character character) {
  float priority = 0;
  unsigned int baseInitiative = character_agility(character);
  unsigned int isAlive = 0;
  float modificador = 1;

  if (character_is_alive(character))
  {
    isAlive = 1;
  }

  if (character_ctype(character) == agile)
  {
    modificador = 1.5;
  } else if (character_ctype(character) == tank) {
    modificador = 0.8;
  }
  
  priority = baseInitiative * isAlive * modificador;

  return priority;
}

static struct s_node *create_node(Character character) {
  struct s_node *new_node = NULL;
  float priority = calculate_priority(character);
  new_node = malloc(sizeof(struct s_node));
  new_node->priority = priority;
  new_node->personaje = character;
  new_node->next = NULL;
  assert(new_node != NULL);
  return new_node;
}

pqueue pqueue_enqueue(pqueue q, Character character) {
  assert(invrep(q));
  node new_node = create_node(character);
  node aux = NULL;
  node aux_before = NULL;
  bool found = false;

  if (q->first == NULL) // Caso sin ningun elemento
  {
    q->first = new_node;
  } else if (q->first != NULL && q->first->priority < new_node->priority) { // new_node tiene mas prioridad que todos
    new_node->next = q->first;
    q->first = new_node;
  } else if (q->first != NULL && q->first->priority >= new_node->priority) {
    aux = q->first;
    aux_before = aux;
    while (aux != NULL && !found)
    {
      if (aux->priority >= new_node->priority)
      {
        aux_before = aux;
        aux = aux->next;
      } else if (aux->priority < new_node->priority) {
        found = true;
        new_node->next = aux;
        aux_before->next = new_node;
      } 

      if (aux == NULL && !found)
      {
        aux_before->next = new_node;
        found = true;
      }
    }
  }

  q->size += 1;
  
  return q;
}

/* ============================================================================
IS EMPTY?
============================================================================ */

bool pqueue_is_empty(pqueue q) {
  bool res = (q->size == 0);
  return res;
}

/* ============================================================================
PEEKS
============================================================================ */

Character pqueue_peek(pqueue q) {
  Character res;
  if (q->first != NULL)
  {
    res = q->first->personaje;
  }
  
  return res;
}

float pqueue_peek_priority(pqueue q) {
  float res = 0;
  if (q->first != NULL)
  {
    res = q->first->priority;
  }
  
  return res;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int pqueue_size(pqueue q) {
  assert(invrep(q));
  unsigned int size = 0;
  size = q->size;

  return size;
}

/* ============================================================================
COPY
============================================================================ */

pqueue pqueue_copy(pqueue q) {
  assert(invrep(q));
  pqueue copy = pqueue_empty();
  node aux = q->first                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             ;
  node node_copy = NULL;
  node aux_node_copy = NULL;
  copy->size = q->size;
  copy->first = NULL; //                                                                                                                                                                                                                                

  if (aux != NULL)
  {
    node_copy = create_node(aux->personaje);
    copy->first = node_copy;
    aux_node_copy = copy->first;
    aux = aux->next;
    while (aux != NULL)
    {
      node_copy = create_node(aux->personaje);
      aux_node_copy->next =node_copy;
      aux = aux->next;
      aux_node_copy = aux_node_copy->next;
    }
  }

  return copy;
}

/* ============================================================================
DESTROY!
============================================================================ */
static struct s_node *destroy_node(struct s_node *n) {
  assert(n != NULL);
  node p = n;

  while (p->next != NULL)
  {
    p = p->next;
    free(n);
    n = p;
  }
  
  free(p);

  n = NULL;
  p = NULL;

  assert(n == NULL);
  return n;
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  node aux = q->first;
  q->first = q->first->next;
  aux->next = NULL;
  aux = destroy_node(aux);
  q->size -= 1;

  assert(invrep(q));
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  assert(invrep(q));

  if (q->first != NULL)
  {
    destroy_node(q->first);
  }
  
  free(q);
  q = NULL;
  
  assert(q == NULL);
  return q;
}
