#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h> // para usar getcwd
#include <limits.h> // para tener path max

#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"

#include "obfuscated.h"
static void show_prompt(void) {

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf ("mybash ");
        printf("\033[34m~%s> \033[0m", cwd); // Ver el directorio actual
    } else {
        perror("Error al obtener el directorio actual");
    }
    fflush (stdout);
}

int main(int argc, char *argv[]) {
    pipeline pipe;
    Parser input;
    bool quit = false;

    input = parser_new(stdin);
    while (!quit) {
        //ping_pong_loop(NULL);
        show_prompt();
        pipe = parse_pipeline(input);

        /* Hay que salir luego de ejecutar? */
        quit = parser_at_eof(input);    

        execute_pipeline(pipe);
        pipeline_destroy(pipe);

    }
    parser_destroy(input); input = NULL;
    return EXIT_SUCCESS;
}
