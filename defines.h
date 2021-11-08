/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdbool.h>
#define MAX_CPUS 4
#define MAX_CORES 4
#define MAX_THREADS 20


struct Clock
{
    int ciclo;
};

typedef struct Timer
{
    int idTimer;
}Timer;

typedef struct PCB{
    int idPCB;
    int tiempo_vida;
}PCB;

typedef struct Nodo {
    PCB data;
    struct Nodo* next;
}Nodo;

typedef struct Hilo{ //validar si cada hilo o cada core debe tener cola de tareas
    int idHilo;
    PCB task;
} Hilo;

typedef struct Core{
    int idCore;
    Hilo* listHilos[MAX_THREADS];
    ProcessQueue queueTask;
} Core;

typedef struct CPU{
    int idCPU;
    Core* listCores[MAX_CORES];
} CPU;

struct Machine{
    CPU* listaCPUs[MAX_CPUS];
}Machine; 

typedef struct ProcessQueue{
    Nodo* head;
    Nodo* tail;
    int max;
    int count;
} ProcessQueue;

