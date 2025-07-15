#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct _list * list;
typedef int elem_list;

/* Constructores */

list empty();
// Crea una lista vacia

void addl(elem_list e,list *l);
// Agrega e al comienzo de l

void addr(elem_list e, list *l);
// Agrega e al final de l
// al usar addr tengo una violacion de segmento.

void destroy(list l);
// Libera memoria usada por l

/* Operaciones */

bool is_empty(list l);
// True si l es vacio

elem_list head(list l);
// PRE: !is_empty(l)
// Devuelve el primer elemento de l

void tail(list l);
// PRE: !is_empty(l)
// Elimina el primer elemento de l

unsigned int length(list l);
// largo de l

void concat(list l, list l0);
// Agrega l0 al final de l

elem_list index(list l, unsigned int n);
// PRE: length(l) > n
// Devuelve el elemento en la posicion n

void take(list l, unsigned int n);
// PRE: length(l) > n
// Deja en el l solo los primeros n elementos

void drop(list l, unsigned int n);
// PRE: length(l) > n
// Elimina los primeros n elementos 

list copy_list(list l);
// Devuelve una copia de l

#endif // _LIST_H
