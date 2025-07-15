#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <glib-2.0/glib.h>

#include "command.h"
#include "strextra.h"


// --- scommand ---

struct scommand_s
{
    GList *arg;
    char *out;
    char *in;
};

scommand scommand_new()
{
    scommand result = malloc(sizeof(struct scommand_s));

    if (result == NULL)
    {
        printf("Error al asignar memoria 'scommand' \n");
        exit(EXIT_FAILURE);
    }

    result->arg = NULL;
    result->out = NULL;
    result->in = NULL;

    assert(result != NULL &&
           scommand_is_empty(result) &&
           scommand_get_redir_in(result) == NULL &&
           scommand_get_redir_out(result) == NULL);

    return result;
}

scommand scommand_destroy(scommand self) {
    assert(self != NULL);

    if (self->arg != NULL) {
        // Recorre la lista y libera cada argumento
        for (GList* l = self->arg; l != NULL; l = l->next) {
            free(l->data);  // Libera cada cadena duplicada
        }
        g_list_free(self->arg);  // Libera la lista
        self->arg = NULL;
    }

    if (self->out != NULL) {
        free(self->out);
        self->out = NULL;
    }

    if (self->in != NULL) {
        free(self->in);
        self->in = NULL;
    }

    free(self);
    self = NULL;

    assert(self == NULL);

    return self;
}




void scommand_push_back(scommand self, char * argument){
    assert(self!=NULL && argument!=NULL);

    self->arg = g_list_append(self->arg, argument);

    assert(!scommand_is_empty(self));
}


void scommand_pop_front(scommand self){

    assert(self!=NULL && !scommand_is_empty(self));
    GList * first = g_list_nth_prev(self->arg,0);
    self->arg = g_list_delete_link(self->arg, first);
    // Revisar si funciona correctamente.
}


void scommand_set_redir_in(scommand self, char * filename){

    assert(self!=NULL);
    if(self->in != NULL){
        free(self->in);
    }
    self->in = filename;

}

void scommand_set_redir_out(scommand self, char * filename){

    assert(self!=NULL);
    if(self->out != NULL){
        free(self->out);
    }
    self->out = filename;

}

bool scommand_is_empty(const scommand self){
    assert(self != NULL);
    bool result = (self->arg == NULL);
    return result;
}

unsigned int scommand_length(const scommand self){
    
    assert(self!=NULL);

    unsigned int result = g_list_length(self->arg);
    
    // assert((scommand_length(self)==0) == scommand_is_empty(self));
    
    return result;
}

char * scommand_front(const scommand self){

    assert(self!=NULL && !scommand_is_empty(self));
    
    char* result = g_list_nth_data(self->arg, 0);

    assert(result!=NULL);
    return result;
}

char * scommand_get_redir_in(const scommand self){

    assert(self!=NULL);
    return self->in;
}

char * scommand_get_redir_out(const scommand self){
    
    assert(self!=NULL);
    return self->out;
}

char * scommand_to_string(const scommand self) {
    assert(self != NULL);
    char* result = strdup("");  // Asigna memoria con strdup
    char* temp = NULL; //var temporal para manipular 

    GList* args = self->arg;

    while (args != NULL) {
        temp = strmerge(result, (char*) g_list_nth_data(args, 0));
        free(result);  // Libera la memoria de la cadena previa
        result = temp;  // Actualiza result con la cadena fusionada

        temp = strmerge(result, " ");  // Fusión con un espacio
        free(result);  // Libera la memoria de la cadena previa
        result = temp;  // Actualiza result con la cadena fusionada

        args = g_list_next(args);  // Avanza al siguiente argumento
    }

    if (self->out != NULL) {
        temp = strmerge(result, " > ");
        free(result);
        result = temp;

        temp = strmerge(result, scommand_get_redir_out(self));
        free(result);
        result = temp;
    }

    if (self->in != NULL) {
        temp = strmerge(result, " < ");
        free(result);
        result = temp;

        temp = strmerge(result, scommand_get_redir_in(self));
        free(result);
        result = temp;
    }

    assert(scommand_is_empty(self) || scommand_get_redir_in(self) == NULL ||
           scommand_get_redir_out(self) == NULL || strlen(result) > 0);

    return result;
}


// --- PIPELINE ---


struct pipeline_s
{
    GList* cmd;
    bool fg;
};

pipeline pipeline_new(void){
    pipeline result = malloc(sizeof(struct pipeline_s));
   
    if (result == NULL)
    {
        printf("Error al asignar memoria 'scommand' \n");
        exit(EXIT_FAILURE);
    }

    result->cmd = NULL;
    result->fg = true;  

    assert(result != NULL && pipeline_is_empty(result)
            && pipeline_get_wait(result));

    return result;
}

pipeline pipeline_destroy(pipeline self){
    assert(self != NULL);

    for(unsigned int i = 0; i < pipeline_length(self); i++)
    {
        scommand_destroy(g_list_nth_data(self->cmd,i));
    }
    
    g_list_free(self->cmd);
    self->cmd = NULL;

    free(self);
    self = NULL;

    assert(self == NULL);

    return self;
}

void pipeline_push_back(pipeline self, scommand argument){
    assert(self!=NULL && argument!=NULL);

    self->cmd = g_list_append(self->cmd, argument);

    assert(!pipeline_is_empty(self));    
}

void pipeline_pop_front(pipeline self){
    assert(self!=NULL && !pipeline_is_empty(self));
    GList * first = g_list_nth_prev(self->cmd,0);
    self->cmd = g_list_delete_link(self->cmd, first);
    // Revisar si funciona correctamente.

}

void pipeline_set_wait(pipeline self, const bool w){
    assert(self != NULL);
    self->fg = w;
}

bool pipeline_is_empty(const pipeline self){
    assert(self != NULL);

    return (self->cmd == NULL);
}

unsigned int pipeline_length(const pipeline self){
    assert(self != NULL);
    unsigned int result = g_list_length(self->cmd);

    return result;
}

// Devuelve el primer comando.
scommand pipeline_front(const pipeline self){
    assert(self != NULL);

    scommand result = g_list_nth_data(self->cmd, 0);

    assert(result != NULL);
    return result;
}

bool pipeline_get_wait(const pipeline self){
    assert(self != NULL);
    
    return self->fg;
}

char *pipeline_to_string(const pipeline self) {
    assert(self != NULL);

    char *result = strdup("");  // Inicializa la cadena vacía
    char *temp = NULL;

    if (!pipeline_is_empty(self)) {
        unsigned int i = 0;
        unsigned int length = pipeline_length(self);

        while (i < length) {
            // Convierte el scommand actual a string
            char *command_str = scommand_to_string(g_list_nth_data(self->cmd, i));
            
            // Combina el resultado actual con el nuevo comando
            temp = strmerge(result, command_str);
            free(result);  // Libera la cadena previa
            result = temp; // Actualiza el resultado

            // Agrega el separador '|' si no es el último comando
            if (i < length - 1) {
                temp = strmerge(result, " | ");
                free(result);
                result = temp;
            }

            free(command_str);  // Libera la cadena del comando actual
            i++;
        }

        // Si el pipeline no espera al final, agrega ' &'
        if (!pipeline_get_wait(self)) {
            temp = strmerge(result, " &");
            free(result);
            result = temp;
        }
    }

    assert(pipeline_is_empty(self) || pipeline_get_wait(self) || strlen(result) > 0);

    return result;
}

