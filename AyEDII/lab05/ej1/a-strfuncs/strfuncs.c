#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(char *str) {
    size_t i = 0;
    
    while (str[i] != '\0')
    {
        i++;
    }

    return i;
}

char *string_filter(char *str, char c) {
    size_t length_original = string_length(str);
    size_t length_res = 0;

    for (size_t i = 0; i < length_original; i++)
    {
        if (str[i] != c)
        {
            length_res++; // largo sin los simbolos filtrados.
        }
    }

    char *res = malloc((length_res + 1) * sizeof(char));

    size_t j = 0;

    for (size_t i = 0; i < length_original; i++)
    {
        if (str[i] != c)
        {
            res[j] = str[i];
            j++;
        }
    }

    res[j] = '\0';

    return res;
}

bool string_is_symmetric(char *str) {
    bool res = true;
    size_t length = string_length(str);
    size_t i = 0;
    
    while (i < length && res)
    {
        if (str[i] == str[length - 1])
        {
            i++;
            length--;
        } else {
            res = false;
        }
    }
    
    return res;
}
