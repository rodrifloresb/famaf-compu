En este laboratorio se implemento un sistema de Semaforos que sirve como mecanismo de sincronizacion entre procesos.	
Para correr el codigo hacemos lo siguiente
Instalacion:
1- Clonar el repositorio git clone https://bitbucket.org/sistop-famaf/so24lab2g34.git
2- Instalar qemu sudo-apt-get install qemu-system-riscv64
Compilacion:
Ejecutar en en el directorio so24lab2g34/ 
	- make qemu
	
Implementacion del proyecto
Syscall utilizadas: acquire(), release(), sleep() ,wakeup() , argint()
Estructura del semaforo

struct semaphore_int{
    int value;
    bool using;
    struct spinlock blocked;
};

struct semaphore_int semaphores[SEM_MAX];

Prototipo formado por
sem_open se encarga de crear un nuevo semaforo o abrir uno que ya existe. sem_up se utiliza para incrementar el valor de un semaforo y sem_down para decrementar  utilizando syscalls sleep y wakeup. 
sem_close se utiliza para cerrar un semaforo que ya esta abierto
	
Tambien escribimos el programa "pingpong"  que sincroniza la escritura por pantalla 

Para utlizar el programa pingpong deberas escribir 
	- pingpong N
donde N es un numero natural elegido.

Implementacion
Se inicializo dos semáforos, uno para controlar el proceso que imprime por pantalla "ping" y otro para el proceso que imprime "pong". El semáforo del "ping" se inicializa en 1 y el semáforo del "pong" se inicializa en 0 para luego a través de las funciones sem_up y sem_down se intercale la ejecución de cada proceso.

En definitiva, usando la syscall fork, creamos el hijo y luego intercalamos entre el proceso hijo y padre cada print.

El laboratorio fue desarrollado usando editor de codigo Visual Studio Code. 
La forma en que nos organizamos fue en pareja resolver la implementacion de Semaforos y Pingpong utilizando medios de comunicacion como Discord, WhatsApp e incluyendo encuentros en Meet.

Integrantes Grupo 34:  Antonella Loyola, Carolina Yut , Rodrigo Flores , Samsa Ahuerma.  
