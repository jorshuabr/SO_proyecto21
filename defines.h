#ifndef DEFINEH
#define DEFINEH

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#define MAX_CPUS 4
#define MAX_CORES 4
#define MAX_THREADS 20


/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */

typedef struct pcb_t{
    int idPCB;
    int tiempo_vida;
} pcb_t;


typedef struct nodo_t {
    pcb_t data;
    struct nodo_t* next;        //OJO NO SABEMOS SI HACE FALTA VOLVER A PONER 'STRUCT' PARA REFERENCIAR AL OBJETO
} nodo_t;

typedef struct processQueue_t{
    nodo_t* head;
    nodo_t* tail;
    int max;
    int count;
} processQueue_t;

typedef struct hilo_t{ 
    int idHilo;
    pcb_t task;
    int idCorePadre;
    pthread_t pthread_real; 
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


#endif