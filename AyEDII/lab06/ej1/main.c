/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

static void ciclo(abb tree){
    
    unsigned int seleccion = 0u;
    abb_elem elem_aux;
    bool res;
    printf("\n\n//************************// \n");
    printf("\n""1. Mostrar arbol \n" "2. Agregar elemento \n"
            "3. Eliminar un elemento \n" "4. Existe tal elemento \n"
            "5. Mostrar longitud del arbol \n" "6. mostrar raiz, maximo y minimo \n"
            "7. Salir \n");


    printf("\n");
    printf("\x1b[33m""Que desea realizar: ""\x1b[0m");
    scanf("%u", &seleccion);

    if (seleccion == 1u)
    {
        printf("\n""\x1b[33m");
        printf(" 0. ABB_IN_ORDER \n"" 1. ABB_PRE_ORDER \n" 
                " 2. ABB_POST_ORDER \n""En que orden lo queres? : \n" );
    
        scanf("%u", &seleccion);
        if (seleccion == ABB_IN_ORDER)
        {
            abb_dump(tree, ABB_IN_ORDER);
        
        } else if (seleccion == ABB_PRE_ORDER) {
            abb_dump(tree, ABB_PRE_ORDER);
        } else if (seleccion == ABB_POST_ORDER) {
            abb_dump(tree, ABB_POST_ORDER);
        } else {
            printf("\x1b[31m""Selecciona un orden correcto! :] \n");
        }

        printf("\x1b[0m");
        ciclo(tree);
    } else if (seleccion == 2u) {
        printf("Que elemento desea agregar: ");
        scanf("%d", &elem_aux);

        tree = abb_add(tree, elem_aux);
        ciclo(tree);
    } else if (seleccion == 3u) {
        printf("Que elemento desea eliminar: ");
        scanf("%d", &elem_aux);

        tree = abb_remove(tree, elem_aux);
        ciclo(tree);    
    } else if (seleccion == 4u) {
        printf("Elemento: ");
        scanf("%d", &elem_aux);
        res = abb_exists(tree, elem_aux);

        if (res)
        {
            printf("\x1b[33m""Si existe. \n""\x1b[0m");
        } else {
            printf("\x1b[33m""No existe. \n""\x1b[0m");
        }
        ciclo(tree);
    } else if (seleccion == 5u) {
        printf("El largo del arbol es: %u \n", abb_length(tree));
        ciclo(tree);
    } else if (seleccion == 6u) {
        if (!abb_is_empty(tree)) {
            printf("\n");
            printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                        abb_min(tree),
                                                        abb_max(tree));
        } else {
            printf("\x1b[33m""\nÁrbol vacío\n""\x1b[0m");
        }

        ciclo(tree);
    } else if (seleccion == 7u) {
        printf("\x1b[33m""Chau ^_~ \n""\x1b[0m");
        // skip
    } else {
        printf("\x1b[31m""Tu seleccion es invalida.""\x1b[0m");
        ciclo(tree);
    }
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    // abb_dump(tree, ABB_IN_ORDER);
    // if (!abb_is_empty(tree)) {
    //     printf("\n");
    //     printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
    //                                                    abb_min(tree),
    //                                                    abb_max(tree));
    // } else {
    //     printf("\nÁrbol vacío\n");
    // }

    // parte B

    ciclo(tree);

    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
