/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"

/**
 * \fn Crea una nueva pcb_t
 * \param id identificador de pcb_t
 * */
struct pcb_t * crearPcb(int id, int tiempoVida){
    struct pcb_t * tarea = malloc(sizeof(pcb_t));
    tarea -> idPCB = id + 400;
    tarea -> tiempo_vida=tiempoVida;
    return tarea;
}
