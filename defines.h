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


typedef struct mm_t {
    unsigned char* code;
    unsigned char* data;
    unsigned char* pgb;
}mm_t;

typedef struct mmu_t
{
    unsigned char* tlb;
    /* data */
}mmu_t;

typedef struct physical_t{
    unsigned int memoria;
    int* tabla_paginas;
}physical_t;

typedef struct pcb_t{
    mm_t* meme;
    int idPCB;
    bool status;
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
    bool ocupado;
    unsigned char* pc;//contador de programa
    unsigned char* ir;//registro de instruccion
    unsigned char* ptbr;
    int registro[16];
    mmu_t mmu;
} hilo_t;

typedef struct core_t{
    int idCore;
    hilo_t* listHilos;
    processQueue_t* queueTask;
} core_t;

typedef struct cpu_t{
    int idCPU;
    core_t* listCores;
} cpu_t;

typedef struct machine_t{
    cpu_t* listaCPUs;
}machine_t;

typedef struct cantidades_t{
    int cpus;
    int cores;
    int hilos;
}cantidades_t;

#endif