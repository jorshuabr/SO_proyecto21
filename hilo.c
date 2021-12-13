/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"s
#include<stdlib.h>
/**
 * \fn Crea un nuevo hilo
 * \param id identificador de hilo
 * */
hilo_t * crearHilo(int id){
    hilo_t * newHilo = malloc(sizeof(hilo_t));
    newHilo -> idHilo = id + 300;
    newHilo -> task = *(pcb_t *) malloc(sizeof(pcb_t));
    newHilo -> ocupado = false;
    return newHilo;
}