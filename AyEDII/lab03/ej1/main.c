#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000


char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        //print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *patch, unsigned int indexes[], char letters[], unsigned int max_size) {
    FILE *file = fopen(patch, "r");
    unsigned int length = 0;
    
    if (file == NULL)
    {
        printf("Error al leer el fichero \n");
        exit(EXIT_FAILURE);
    }

    while ((!feof(file)) && length < max_size)
    {
        int res = fscanf(file, "%u -> *%c*\n", &indexes[length], &letters[length]);

        if (res != 2) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }

        if (indexes[length] > max_size)
        {
            printf("Error, max_size superado. \n");
            exit(EXIT_FAILURE);
        }
        
        length++;
    }

    fclose(file);

    return length;
}

static void sort(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {

    for (unsigned int i = 0; i < length; i++)
    {
        sorted[indexes[i]] = letters[i];
    }
}

int main(int argc, char *argv[]) {
    char *file = NULL;

    file = parse_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 

    length = data_from_file(file, indexes, letters, MAX_SIZE);
    sort(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

