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
struct CPU * crearCpu(int id, int cantCore ){
    struct CPU * newCpu = malloc(sizeof(CPU));
    newCpu -> idCPU  = id + 100;
    cpu-> listCores = (Core*) malloc(sizeof(Core)*cantCore);
    return newCpu;
}