/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"
#include<stdlib.h>
/**
 * \fn Crea una nueva pcb_t
 * \param id identificador de pcb_t
 * */
pcb_t * crearPcb(int id){
    pcb_t * tarea = malloc(sizeof(pcb_t));
    tarea -> idPCB = id + 400;
    tarea -> meme =  malloc(sizeof(mm_t));
    tarea -> meme -> code= malloc(sizeof(unsigned char));
    tarea -> meme -> data = malloc(sizeof(unsigned char));
    tarea -> meme -> pgb =malloc(sizeof(unsigned char));
    return tarea;
}
