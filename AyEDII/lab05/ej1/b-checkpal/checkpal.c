#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 50  // MAX_LENGTH original era 20.

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;
    char *str = user_input;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    fgets(user_input, sizeof(user_input), stdin);

    size_t length = string_length(str);
    if (length > 0 && user_input[length-1] == '\n' )
    {
        user_input[length-1] = '\0'; // fgets escribe \n al final.
    }
    

    //scanf("%s", user_input); 
    //scanf solo lee la primer "palabra".
    
    filtered = string_filter(user_input, ignore_chars[0]);
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        str = filtered;
        filtered = string_filter(filtered, ignore_chars[i]);
        free(str);
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");

    free(filtered);


    return EXIT_SUCCESS;
}

