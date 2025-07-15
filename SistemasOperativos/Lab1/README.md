# MyBash - grupo 34
***Realizado por : Antonella Loyola, Carolina Yut, Rodrigo Flores y Samsa Ahuerma***

## Cambios en prompt (modulo principal)
Agregamos las siguientes librerias para poder ver el directorio en el que estamos.

```
#include <unistd.h> // para usar getcwd
#include <limits.h> // para tener path max
```

Para que se vea de esta manera

`mybash ~/home/rodrigo/so_labs/so24lab1g34>`

## Estructuras utilizadas dentro del scommand.c

- Para manejar los comandos :

```
struct scommand_s
{
    GList *arg;
    char *out;
    char *in;
};
```

- Para manejar los pipeline :


```
struct pipeline_s
{
    GList* cmd;
    bool fg;
};
```

## Casos especiales (comandos internos)

- Caso 1 : 'entra' un comando interno unico → Simplemente lo ejecutamos. `cd so_labs`

- Caso 2 : 'entra' solo el comando `cd` → este nos llevara al directorio `mybash ~/home>`

- Caso 3 : 'entra' un comando interno junto a cualquier otro comando → Ejecutamos solo el comando interno. `cd | ls`

- Caso 4 : 'entra' un comando simple junto a un comando interno → Error al ejecutar. `ls -l | help`
