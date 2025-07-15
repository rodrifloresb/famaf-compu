#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> // chdir

#include "builtin.h"
#include "command.h"

#include "tests/syscall_mock.h"

/*----COMANDOS INTERNOS----*/

// comprueba si el comando es CD

static bool is_cd(scommand cmd)
{
    assert(cmd != NULL && !scommand_is_empty(cmd));
    return (strcmp(scommand_front(cmd), "cd") == 0);
}

static void exec_cd(scommand cmd)
{
    if (scommand_length(cmd) == 2)
    {
        scommand_pop_front(cmd); // elimino al 'cd'

        if (chdir(scommand_front(cmd)) != 0) // direccion valida
        {
            printf("La direccion es invalida. \n");
        }
    }
    else if (scommand_length(cmd) == 1) // cd solo
    {
        chdir("/home");
    }
    else
    {
        printf("cantidad de argumentos invalido. \n");
    }
}

// comprueba si el comando es HELP
static bool is_help(scommand cmd)
{
    assert(cmd != NULL && !scommand_is_empty(cmd));
    return (strcmp(scommand_front(cmd), "help") == 0);
}

static void exec_help(void)
{
    printf("Nombre del Shell: MyBash \n"
           "\t- INTEGRANTES:\n"
           "\t- Ahuerma Samsa\n"
           "\t- Flores Rodrigo\n"
           "\t- Loyola Antonella\n"
           "\t- Yut Carolina\n\n"
           "Comandos internos\n"
           "help: despliega esta interfaz\n\n"
           "exit: EOF, cierre de mybash\n\n"
           "cd: cd [directory_path]\n\n");
}

// comprueba si el comando es EXIT
static bool is_exit(scommand cmd)
{
    assert(cmd != NULL && !scommand_is_empty(cmd));
    return (strcmp(scommand_front(cmd), "exit") == 0);
}

// comprueba si el comando es interno
bool builtin_is_internal(scommand cmd)
{
    assert(cmd != NULL);
    return is_cd(cmd) || is_help(cmd) || is_exit(cmd);
}

// indica si el pipeline tiene un solo comando y si este es interno
bool builtin_alone(pipeline p)
{
    assert(p != NULL);
    bool res = (pipeline_length(p) == 1) && builtin_is_internal(pipeline_front(p));
    return res;
}

// ejecuta un comando interno
void builtin_run(scommand cmd)
{
    assert(cmd != NULL && builtin_is_internal(cmd));

    if (is_help(cmd))
    {
        exec_help();
    }
    else if (is_cd(cmd))
    {
        exec_cd(cmd);
    }
    else if (is_exit(cmd))
    {
        printf("Usted va a salir del shell, bye! :)\n");
        exit(EXIT_SUCCESS);
    }
}
