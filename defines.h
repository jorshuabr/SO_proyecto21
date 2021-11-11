/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdbool.h>
#define MAX_CPUS 4
#define MAX_CORES 4
#define MAX_THREADS 20


typedef struct PCB{
    int idPCB;
    int tiempo_vida;
}PCB;

typedef struct Hilo{ //validar si cada hilo o cada core debe tener cola de tareas
    int idHilo;
    PCB task;
    int idCorePadre;
} Hilo;

typedef struct Core{
    int idCore;
    Hilo* listHilos;
    ProcessQueue queueTask;
} Core;

typedef struct CPU{
    int idCPU;
    Core* listCores;
} CPU;

typedef struct Machine{
    CPU* listaCPUs;
}Machine; 

typedef struct ProcessQueue{
    Nodo* head;
    Nodo* tail;
    int max;
    int count;
} ProcessQueue;

typedef struct Nodo {
    PCB data;
    struct Nodo* next;
}Nodo;