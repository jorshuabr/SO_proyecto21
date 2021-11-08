/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"

/**
 * \fn Crea un nuevo hilo
 * \param id identificador de hilo
 * */
struct Hilo * crearHilo(int id){
    struct Hilo * newHilo = malloc(sizeof(Hilo));
    newHilo -> idHilo = id + 300;
}