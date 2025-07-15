#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int i = 0;
    while (!(s[i] == '\0'))
    {
        i++;
    }
    
    return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {

    bool res = true;

    if (fstring_length(s1) != fstring_length(s2))
    {
        res = false;
    } else {
        for (unsigned int i = 0; i < fstring_length(s1); i++)
        {
            if (s1[i] != s2[i])
            {
                res = false;
            }
        }
    }
    

    return res;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = true;
    unsigned int length = fstring_length(s1);

    assert(length < FIXSTRING_MAX);

    for (unsigned int i = 0; i < length; i++)
    {     
        if (s1[i] > s2[i])
        {
            res = false;
            break;
        }

        if (s1[i] < s2[i])
        {
            break;
        }

        if (s2[i] == '\0' && length > fstring_length(s2))
        {
            res = false;
            break;
        }
            
    }

    return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;

    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}


