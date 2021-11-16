/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */

#include <stdbool.h>
#include <stddef.h>
#define MAX_CPUS 4
#define MAX_CORES 4
#define MAX_THREADS 20

typedef struct nodo_t {
    pcb_t data;
    struct nodo_t* next;
}nodo_t;

typedef struct processQueue_t{
    nodo_t* head;
    nodo_t* tail;
    int max;
    int count;
} processQueue_t;

typedef struct pcb_t{
    int idPCB;
    int tiempo_vida;
}pcb_t;

typedef struct hilo_t{ //validar si cada hilo o cada core debe tener cola de tareas
    int idHilo;
    pcb_t task;
    int idCorePadre;
} hilo_t;

typedef struct core_t{
    int idCore;
    hilo_t* listHilos;
    processQueue_t queueTask;
} core_t;

typedef struct cpu_t{
    int idCPU;
    core_t* listCores;
} cpu_t;

typedef struct machine_t{
    cpu_t* listaCPUs;
}machine_t;


