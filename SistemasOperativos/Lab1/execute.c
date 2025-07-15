#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tests/syscall_mock.h"
#include "builtin.h"
#include "execute.h"



// Funcion para ejecutar comandos
static void execute_cmd(scommand cmd){
        char* redir_in = scommand_get_redir_in(cmd);
        char* redir_out = scommand_get_redir_out(cmd);

        unsigned int length = scommand_length(cmd); // cantidad de argumentos que trae el comando
        char** args = calloc(length + 1, sizeof(char *));

        //redireccion de entrada 
        if (redir_in != NULL)
        {
            //  int fd_in = open(redir_in, O_RDONLY);
            int fd_in = open(redir_in, O_RDONLY, 0644);

            if (fd_in < 0){
                printf("fd_in no se abrio correctamente \n");
                exit(EXIT_FAILURE);
            }

            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }        

        //redireccion de salida 
        if (redir_out != NULL)
        {
            // int fd_out = open(redir_out, O_WRONLY | O_CREAT | O_TRUNC);
            int fd_out = open(redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }


        for (unsigned int i = 0; i < length; i++)
        {
            args[i] = strdup(scommand_front(cmd));
            scommand_pop_front(cmd);
        }

        if (execvp(args[0], args) == -1)
        {
            printf("Error al ejecutar \n");
            exit(EXIT_SUCCESS); // Sin esto podemos tener procesos zombies
        }

}


// Funcion para ejecutar un solo comando
static void execute_one_command(pipeline apipe) {
    pid_t pidC = fork();
    scommand cmd = pipeline_front(apipe);

    if (pidC < 0)
    {
        printf("Error al crear al hijo \n");
    } else if(pidC  == 0) // Estoy en el hijo
    {   
        execute_cmd(cmd);
    } else {        // El padre
        if (pipeline_get_wait(apipe))
        {
            wait(NULL); // para esperar a que el hijo termine
        }
    } 
}

// Función para ejecutar dos comandos con un pipe 
static void execute_two_command(pipeline apipe) {
    int fd[2];  // para los descriptores de archivos del pipe (lectura y escritura)

    if (pipe(fd) < 0) {
        printf("Error al crear un pipe \n");
        exit(EXIT_FAILURE);
    }

    // Proceso hijo que ejecuta el primer comando del pipeline
    pid_t pid1 = fork();
    if (pid1 < 0) {
        printf("Error en el fork\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {  // Primer hijo 
        close(fd[0]);  // Cierra el extremo de lectura, ya que solo debe escribir 
        dup2(fd[1], STDOUT_FILENO);  // Redirige la salida estándar al extremo de escritura
        close(fd[1]);  // Cierra el extremo de escritura después de redirigirla 

        scommand cmd1 = pipeline_front(apipe);  // Toma el primer comando 
        execute_cmd(cmd1);  // Ejecuta el primer comando 
        exit(EXIT_SUCCESS);  // Termina el primer hijo después de ejecutar el comando 
    }

    // Proceso hijo que ejecuta el segundo comando
    pid_t pid2 = fork();
    if (pid2 < 0) {
        printf("Error en el fork\n");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {  // Segundo hijo
        close(fd[1]);  // Cierra el extremo de escritura
        dup2(fd[0], STDIN_FILENO);  // Redirige la entrada estándar al extremo de lectura
        close(fd[0]);  // Cierra el extremo de lectura después de redirigir

        pipeline_pop_front(apipe);  // Remueve el primer comando, dejando el segundo cmd al frente
        scommand cmd2 = pipeline_front(apipe); 
        execute_cmd(cmd2);  // Ejecuta el segundo comando 
        exit(EXIT_SUCCESS); 
    }

    // El padre cierra los extremos del pipe porque no los necesita
    close(fd[0]);
    close(fd[1]);

    // Esperar a ambos hijos
    if (pipeline_get_wait(apipe))
    {
        waitpid(pid1, NULL, 0);  // Espera al primer hijo
        waitpid(pid2, NULL, 0);  // Espera al segundo hijo
    }
}

// Función que ejecuta en fg o bg 
void execute_pipeline(pipeline apipe){

    if (!pipeline_is_empty(apipe)) // pipeline no vacio
    {
        scommand cmd = pipeline_front(apipe);

        if (builtin_is_internal(cmd))
        {   
            builtin_run(cmd);           // ejecuto cmd interno
        } else {
            if (pipeline_length(apipe) == 1)        // Un solo comando
            {
                execute_one_command(apipe);    // ejecuto cmd simple

            } else if (pipeline_length(apipe) == 2)  // dos comandos
            {
                execute_two_command(apipe);
            } else {
                printf("Estamos trabajando en eso! \n");
            }
        }
    }
}