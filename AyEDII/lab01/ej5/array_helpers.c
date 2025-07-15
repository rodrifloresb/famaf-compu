/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "mybool.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {

    unsigned int length = max_size + 1;
    unsigned int i = 0;
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL)
    {
        printf("Error al leer el fichero \n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp, "%u", &length);

    if (length > max_size)
    {
        printf("El largo del array es mayor al max_size \n");
        exit(EXIT_FAILURE);
    }
    
    while (!feof(fp))
    {
        fscanf(fp, "%d",&array[i]);
        i++;
    }

    if (i != length + 1)
    {
        printf("Longitud erronea \n");
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    return length;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length; i++)
    {
        if (i < length - 1)
        {
            printf(" %d,", a[i]); 
        } else {
            printf(" %d", a[i]); 
        }
    }
    printf("] \n");
}

mybool array_is_sorted(int a[], unsigned int length) {
    
    mybool res = true;

    for (unsigned int i = 1; i < length; i++)
    {
        if (a[i-1] > a[i])
        {
            res = false;
            break;
        }
    }

    return res;
}
