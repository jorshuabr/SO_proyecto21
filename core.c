/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"

/**
 * \fn Crea un nuevo core
 * \param id identificador de core
 * \param cantHilos cantidad de hilos que contendrá el core
 * */
core_t * crearCore(int id, int cantHilos ){
    core_t * newCore = malloc(sizeof(core_t));
    newCore -> idCore = id + 200;
    newCore-> listHilos = (hilo_t*) malloc(sizeof(hilo_t)*cantHilos);
    return newCore;
}
