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

struct processQueue_t* pq;
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
processQueue_t* init_queue_core(){
    struct processQueue_t* queue_core= malloc(sizeof(processQueue_t));
    queue_core->head= NULL;
    queue_core->tail= NULL;
    queue_core->count = 0;
    queue_core->max= COLA_CORE;
}
/**
 * \fn Función que retorna si la cola se encuentra vácia.
 * \return boolean.
 * */
bool isEmpity(processQueue_t* q)
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


/**
 * \fn Método que agrega una tarea pcb_t a la cola, modelo FIFO.
 * \param  task un struct pcb_t que se añadira a la cola de tareas
 * */
void enque(pcb_t task, processQueue_t* p)
{
    struct nodo_t *nuevo;
    nuevo = malloc(sizeof(struct nodo_t));
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
pcb_t deque(processQueue_t* p)
{
    struct pcb_t  cabeza;
    if (!isEmpity(p)) {
        //pcb_t  taskDeleted = head -> data;
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
    struct nodo_t *it = head;
    printf("Listado de Elementos en cola:\n");
    while (it != NULL) {
        printf("%i - ", it->data);
        it = it->next;
    }
    printf("\n");
}