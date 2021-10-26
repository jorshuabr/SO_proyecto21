/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"


struct pcb * crearPcb(int id){
    struct PCB * tarea = malloc(sizeof(PCB));
    tarea -> idPCB = id + 400;
}
