#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    unsigned long total = sizeof(messi.name) + sizeof(messi.age) + sizeof(messi.height);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n",
           sizeof(messi.name),
           sizeof(messi.age),
           sizeof(messi.height),
           total);
    
    // El tamaño del campo name depende de NAME_MAXSIZE

    printf("direccion de memoriaa campo NAME : %p \n"
           "direccion de memoria campo AGE : %p \n"
           "direccion de memoria campo HEIGHT : %p \n",
           (void *) &messi.name,
           (void *) &messi.age,
           (void *) &messi.height);

    // Las direcciones son cotiguas
    // entre name y age hay 30 bytes de diferencia
    // entre age y height hay 4 bytes de diferencia
    // Ejemplo : 0x7ffc19624640 : 0x7ffc19624660 : 0x7ffc19624664

    return EXIT_SUCCESS;
}

