/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"

/**
 * \fn Crea una nueva PCB
 * \param id identificador de PCB
 * */
struct PCB * crearPcb(int id){
    struct PCB * tarea = malloc(sizeof(PCB));
    tarea -> idPCB = id + 400;
}
