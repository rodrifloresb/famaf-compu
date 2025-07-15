#include <stdbool.h>
#include <stdlib.h>

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"


#define SEM_MAX 100

struct semaphore_int{
    int value;
    bool using;
    struct spinlock blocked;
};

struct semaphore_int semaphores[SEM_MAX];

// Inicia todos los semaforos
// void sem_init(){
//     for (unsigned int i = 0; i < SEM_MAX; i++)
//     {
//         acquire(&semaphores[i].blocked);
//         semaphores[i].value = 0;
//         semaphores[i].using = false;
//         release(&semaphores[i].blocked);
//     }
// }


// Selecciona un semaforo libre
static unsigned int sem_select(int sem){
    unsigned int res = sem;
    bool select_free = false;

    if (sem > SEM_MAX || sem == SEM_MAX || sem < 0) // No deberiamos de estar aca
    {
        printf("Sem fuera de los limites \n");
        exit(EXIT_FAILURE);
    }
    
    if (semaphores[res].using)
    {
        while (!select_free)
        {
            if (res < SEM_MAX - 1)
            {
                res++;

                if (!semaphores[res].using)
                {
                    select_free = true;
                }
            }
            
            if (res == SEM_MAX - 1 && select_free == false)
            {
                res = 0;

                if (!semaphores[res].using)
                {
                    select_free = true;
                }
            }
        }
    }

    return res;
}

// Abre el semaforo 'sem'
uint64 sys_sem_open(void){
    int sem, value;
    argint(0, &sem);
    argint(1, &value);

    if (sem < 0 || sem >  SEM_MAX || value < 0)
    {
        printf("Semaforo inexistente o valor negativo. \n");
        return 0; // Error
    } else {
        sem = sem_select(sem);

        acquire(&semaphores[sem].blocked);
        semaphores[sem].value = value;
        semaphores[sem].using = true;
        release(&semaphores[sem].blocked);
    }

    return sem;
}

// Cierra el semaforo 'sem'
uint64 sys_sem_close(void){
    int sem;
    argint(0,&sem);

    if (sem < 0 || sem >  SEM_MAX)
    {
        printf("El semaforo no esta en uso o no existe \n");
        return 0; // Error
    } else {
        acquire(&semaphores[sem].blocked);
        semaphores[sem].value = 0;
        semaphores[sem].using = false;
        release(&semaphores[sem].blocked);
    }

    return sem;
}

// Incrementa el semaforo 'sem'
uint64 sys_sem_up(void){
    int sem;
    argint(0,&sem);

    if (sem < 0 || sem >  SEM_MAX || !semaphores[sem].using)
    {
        printf("El semaforo no esta en uso o no existe \n");
        return 0; // Error
    } else {
        acquire(&semaphores[sem].blocked);
        
        if ((semaphores[sem].value == 0)) 
        {
            wakeup(&semaphores[sem]);
        }
        
        semaphores[sem].value += 1;
         
        release(&semaphores[sem].blocked);
    }

    return sem;

}

// Decrementa el semaforo
uint64 sys_sem_down(void){
    int sem;
    argint(0,&sem);

    if (sem < 0 || sem >  SEM_MAX || !semaphores[sem].using)
    {
        printf("El semaforo no esta en uso o no existe \n");
        return 0; // Error
    } else {
        acquire(&semaphores[sem].blocked);
        
        while(semaphores[sem].value == 0){
            sleep(&semaphores[sem], &semaphores[sem].blocked);
        }
         
        semaphores[sem].value -= 1;
        
        release(&semaphores[sem].blocked);
    }

    return sem;
}
