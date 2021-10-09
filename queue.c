/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include<stdio.h>
#include<stdlib.h>
#include<defines.h>

struct nodo *head = NULL;
struct nodo *tail = NULL;

/**
 * \fn Función que retorna si la cola se encuentra vácia.
 * \return boolean.
 * */
bool isEmpity()
{
    if (head == NULL)
        return true;
    else
        return false;
}

/**
 * \fn Método que agrega una tarea PCB a la cola, modelo FIFO.
 * \param  task un struct PCB que se añadira a la cola de tareas
 * */
void addNodo(PCB task)
{
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo ->data = task;
    nuevo ->next = NULL;
    if (isEmpity()) {
        head = nuevo;
        tail = nuevo;
    }
    else {
        tail->next = nuevo;
        tail = nuevo;
    }
}

/**
 * \fn Método que inserta una tarea en la primera posición de la cola.
 * \param  task un struct PCB que se añadira a la cola de tareas.
 * */
void addFirst(PCB task)
{
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo ->data = task;

    if (isEmpity()) {
        head = nuevo;
        tail = nuevo;
    }else{
        nuevo ->next = head;
        head = nuevo;
    }
}

/**
 * \fn Método que elimina el primer nodo de la cola.
 * */
void removeHead()
{
    if (!isEmpity()) {
        //PCB  taskDeleted = head -> data;
        struct Nodo *deletedNode = head;
        if (head == tail) {
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->next;
        }
        free(deletedNode);
      }
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