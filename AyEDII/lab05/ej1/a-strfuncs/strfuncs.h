#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdbool.h>

size_t string_length(char *str);

// Calcula la longitud de str.

char *string_filter(char *str, char c);

// Devuelve un nueva cadena con chars
// distintos del char c.

bool string_is_symmetric(char *str);

// indica si str es simetrica.

#endif
