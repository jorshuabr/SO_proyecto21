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
struct cpu_t * crearCpu(int id, int cantCore ){
    struct cpu_t * newCpu = malloc(sizeof(cpu_t));
    newCpu -> idCPU  = id + 100;
    newCpu-> listCores = (core_t*) malloc(sizeof(core_t)*cantCore);
    return newCpu;
}