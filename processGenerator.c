/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"
#include "pcb.h"
#include "queue.h"
//#define NPCB 20;
//#define pcb_t vTask[NPCB];

//cambiar el vector por processQueue

/**
 * \fn llama a la función crearPcb() y las agrega a la cola general de tareas generalProcessQueue
 * \param  NPCB cantidad de tareas a crear
 * \param  generalProcessQueue vector donde se almacenarán las tareas 
 * */
void* processGenerator(int *NPCB, processQueue_t generalProcessQueue){
    int i;
    for (i = 0; i < size(generalProcessQueue); i++)
    {
        struct pcb_t * task = crearPcb(i);   
        enque(*task, &generalProcessQueue); //dudas sobre pasar el objeto al que hace referencia el puntero
    }
}