/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"
#include "pcb.h"
#include "queue.h"
//#define NPCB 20;
//#define PCB vTask[NPCB];

//cambiar el vector por processQueue

/**
 * \fn llama a la función crearPcb() y las agrega a la cola general de tareas generalProcessQueue
 * \param  NPCB cantidad de tareas a crear
 * \param  vTak vector donde se almacenarán las tareas 
 * */
void* processGenerator(int *NPCB, ProcessQueue generalProcessQueue{
    int i;
    for (i = 0; i < generalProcessQueue->size(); i++)
    {
        struct PCB * task = crearPcb(i);   
        vTask[i] = task;
    }
}