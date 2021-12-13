/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include<stdio.h>
#include<stdlib.h>
#include"defines.h"
#include "globals.h"
#define COLA_TOTAL 1000
#define COLA_CORE 30

extern processQueue_t pq;
nodo_t *head = NULL;
nodo_t *tail = NULL;

/**
 * \fn Método que inicializa la cola general de procesos
 * */
void initialize_queue(){
    pq = *(processQueue_t *)malloc(sizeof(processQueue_t));
    pq.head=head;
    pq.tail=tail;
    pq.count = 0;
    pq.max = COLA_TOTAL;
}
/**
 * \fn Función que genera una estructura de cola con un tamaño determinado
 * esta cola esta diseñada para los cores.
 * */
processQueue_t* init_queue_core(){
    processQueue_t* queue_core= malloc(sizeof(processQueue_t));
    queue_core->head= NULL;
    queue_core->tail= NULL;
    queue_core->count = 0;
    queue_core->max= COLA_CORE;
    return queue_core;
}

/**
 * \fn Función que retorna si la cola se encuentra vácia.
 * \return boolean.
 * */
bool isEmpty(processQueue_t* q)
{
    return q->count==0;
}
/**
 *
 */
int size(processQueue_t* q)
{
    return q->count;
}

bool max(processQueue_t* q)
{
    return q->count==q->max;
}


/**
 * \fn Método que agrega una tarea pcb_t a la cola, modelo FIFO.
 * \param  task un struct pcb_t que se añadira a la cola de tareas
 * */
void enque(pcb_t task, processQueue_t* p)
{
    nodo_t *nuevo;
    nuevo = malloc(sizeof(nodo_t));
    nuevo ->data = task;
    nuevo ->next = NULL;
    if (isEmpty(p)) {
        p->head = nuevo;
        p->tail = nuevo;
        p->count++;
    }
    else if (!max(p)){
        p->tail->next=  nuevo;
        p->tail = nuevo;
        p->count++;
    }
    
}


/**
 * \fn Método que elimina el primer nodo de la cola.
 * \param p cola en la que se desee aplicar la operación
 * \return PCB asociada al nodo eliminado.
 * */
pcb_t deque(processQueue_t* p)
{
    pcb_t  cabeza;
    if (!isEmpty(p)) {

        cabeza = p->head->data;
        if (p->count==1) {
            p->head = NULL;
            p->tail = NULL;
        }
        else{
            p->head = p->head->next;
        }
        p->count--;

      }
    return cabeza;
}

/**
 * \fn Método que imprime los elementos de la cola.
 * */
void print(processQueue_t* p)
{
    nodo_t *it = p->head;
    printf("Listado de Elementos en cola:\n");
    int i =0;
    while (i != size(&p)) {
        printf("PCB#  %d - con vida %d", it->data.idPCB, it->data.tiempo_vida);
        printf("\n");
        it = it->next;
    }
    printf("\n");
}
