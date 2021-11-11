/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include<stdio.h>
#include<stdlib.h>
#include"defines.h"
#define COLA_TOTAL 1000
#define COLA_CORE 30

struct ProcessQueue* pq;
struct nodo *head = NULL;
struct nodo *tail = NULL;

/**
 * \fn Método que inicializa la colo general de procesos
 * */
void initialize_queue(){
    pq = malloc(sizeof(pq));
    pq->head=head;
    pq->tail=tail;
    pq->count = 0;
    pq->max = COLA_TOTAL;
}
/**
 * \fn Función que genera una estructura de cola con un tamaño determinado
 * esta cola esta diseñada para los cores.
 * */
ProcessQueue* init_queue_core(){
    struct ProcessQueue* queue_core= malloc(sizeof(ProcessQueue));
    queue_core->head= NULL;
    queue_core->tail= NULL;
    queue_core->count = 0;
    queue_core->max= COLA_CORE;
}
/**
 * \fn Función que retorna si la cola se encuentra vácia.
 * \return boolean.
 * */
bool isEmpity(ProcessQueue* q)
{
    return q->count==0;
}
/**
 *
 */
int size(ProcessQueue* q)
{
    return q->count;
}


/**
 * \fn Método que agrega una tarea PCB a la cola, modelo FIFO.
 * \param  task un struct PCB que se añadira a la cola de tareas
 * */
void enque(PCB task, ProcessQueue* p)
{
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo ->data = task;
    nuevo ->next = NULL;
    if (isEmpity(p)) {
        p->head = nuevo;
        p->tail = nuevo;
    }
    else {
        p->tail->next=  nuevo;
        p->tail = nuevo;
    }
    p->count++;
}


/**
 * \fn Método que elimina el primer nodo de la cola.
 * //no debería devolver su elemento?
 * */
PCB deque(ProcessQueue* p)
{
    struct PCB  cabeza;
    if (!isEmpity(p)) {
        //PCB  taskDeleted = head -> data;
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
void print()
{
    struct Nodo *it = head;
    printf("Listado de Elementos en cola:\n");
    while (it != NULL) {
        printf("%i - ", it->data);
        it = it->next;
    }
    printf("\n");
}