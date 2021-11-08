/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include "defines.h"

/**
 * \fn Crea un nuevo core
 * \param id identificador de core
 * */
struct Core * crearCore(int id){
    struct Core * newCore = malloc(sizeof(Core));
    newCore -> idCore = id + 200;
}
