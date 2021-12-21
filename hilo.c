/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"
#include<stdlib.h>
#include <string.h>
/**
 * \fn Crea un nuevo hilo
 * \param id identificador de hilo
 * */
hilo_t * crearHilo(int id){
    hilo_t * newHilo = malloc(sizeof(hilo_t));
    newHilo -> idHilo = id + 300;
    newHilo -> task = *(pcb_t *) malloc(sizeof(pcb_t));
    newHilo -> ocupado = false;
    for(int i = 0 ; i<16 ; i++) newHilo -> registro[i] = -1;
    newHilo -> pc= malloc(sizeof(unsigned char)*9);
    newHilo -> ir= malloc(sizeof(unsigned char)*9);
    strcpy(newHilo -> pc,"X");
    strcpy(newHilo -> ir,"X");
    return newHilo;
}