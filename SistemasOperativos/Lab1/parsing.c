#include <stdlib.h>
#include <stdbool.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

// Función auxiliar para parsear un comando simple
static scommand parse_scommand(Parser p) {
    // Crea un nuevo comando simple
    scommand scom = scommand_new();
    arg_kind_t type;
    char *arg;

    // Salta espacios en blanco al inicio
    parser_skip_blanks(p);
    
    // Obtiene el siguiente argumento
    arg = parser_next_argument(p, &type);
    
    
    if (arg == NULL) {
        // Si no hay argumento, reporta error y destruye el comando simple creado
        // printf("Error: El comando es vacío\n");
        scommand_destroy(scom);
        return NULL;
    }
    if (type == ARG_INPUT || type == ARG_OUTPUT) {
        // Si el primer argumento es una redirección sin un comando, reporta error
        printf("Error de parseo: No hay argumento\n");
        scommand_destroy(scom);
        free(arg); // Libera la memoria de arg
        return NULL;
    }


    // Agrega los argumentos normales al comando simple
    while (type == ARG_NORMAL && arg != NULL) {
        scommand_push_back(scom, arg); // scommand se apropia de arg
        parser_skip_blanks(p);
        arg = parser_next_argument(p, &type);
    }


    // Si encontramos una redirección de salida

    // Si encontramos una redirección de entrada
    if (type == ARG_INPUT) {
        if (arg == NULL) {
            // Si no hay archivo para la redirección de entrada, reporta error
            printf("Error sintáctico: Redirección de entrada vacía\n");
            scommand_destroy(scom);
            return NULL;
        }
        scommand_set_redir_in(scom, arg); // scommand se apropia de arg
        arg = parser_next_argument(p, &type);
    }

    if (type == ARG_OUTPUT) {
        if (arg == NULL) {
            // Si no hay archivo para la redirección de salida, reporta error
            printf("Error sintáctico: Redirección de salida vacía\n");
            scommand_destroy(scom);
            return NULL;
        }
        scommand_set_redir_out(scom, arg); // scommand se apropia de arg
        arg = parser_next_argument(p, &type);
    }


    return scom; // Devuelve el comando simple parseado
}

// Función para parsear un pipeline completo
pipeline parse_pipeline(Parser p) {
    if (p == NULL || parser_at_eof(p)) {
        // Si el parser es NULL o está al final del archivo, retorna NULL
        return NULL;
    }

    // Crea un nuevo pipeline
    pipeline result = pipeline_new();
    scommand cmd = NULL;
    bool error = false, another_pipe = true, garbage = false;

    // Parsea el primer comando simple
    cmd = parse_scommand(p);
    error = (cmd == NULL);

    // Mientras no haya errores y haya otro pipe
    while (!error && another_pipe) {
        pipeline_push_back(result, cmd); // Agrega el comando simple al pipeline
        parser_op_pipe(p, &another_pipe);
        if (another_pipe) {
            cmd = parse_scommand(p); // Parsea el siguiente comando simple
            error = (cmd == NULL);
        }
    }

    if (error) {
        // Si ocurre un error, limpia los recursos y retorna NULL
        if (cmd != NULL) {
            scommand_destroy(cmd); // Destruye el comando simple en caso de error
        }
        parser_garbage(p, &garbage); // Consume caracteres basura
        pipeline_destroy(result); // Destruye el pipeline en caso de error
        return NULL;
    }

    // Verifica si hay un operador de background
    bool is_background;
    parser_op_background(p, &is_background);
    pipeline_set_wait(result, !is_background); // Configura si el pipeline debe esperar

    parser_garbage(p, &garbage); // Consume caracteres basura
    if (garbage) {
        // Si hay caracteres no reconocidos, reporta error
        printf("Error: Caracteres no reconocidos después del pipeline\n");
        pipeline_destroy(result); // Destruye el pipeline en caso de error
        return NULL;
    }

    return result; // Devuelve el pipeline parseado
}
