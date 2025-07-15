#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;

    res.is_upperbound = true;
    res.is_lowerbound = true;
    res.exists = false;
    res.where = length + 1;

    for (unsigned int i = 0; i < length; i++)
    {
        if (value > arr[i])
        {
            res.is_lowerbound = false;
        }

        if (value < arr[i])
        {
            res.is_upperbound = false;
        }

        if (value == arr[i] && !res.exists)
        {
            res.exists = true;
            res.where = i;
        }
    }
    
    return res;
}

int main(void) {
    
    unsigned int length;
    printf("Largo del array : ");
    scanf("%d", &length);

    int a[length];
    for (unsigned int i = 0; i < length; i++)
    {
        printf("\nValor del array en posicion %d : ", i);
        scanf("%d", &a[i]);
    }

    int value;

    printf("\nValor : ");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, length);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("\n ******RESULTADOS****** \n");
    printf("%d ", result.is_upperbound); // Imprime 1
    printf("%d ", result.is_lowerbound); // Imprime 0
    printf("%u ", result.exists);        // Imprime 1
    printf("%u \n", result.where);         // Imprime 2

    return EXIT_SUCCESS;
}

