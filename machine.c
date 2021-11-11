/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#define MAX_Cpu MAX_CPUS
#define MAX_Core MAX_CORES
#define MAX_t MAX_THREADS

//quizas haya que meterlo en el main, esta por ver

//Como documentar en C  http://profesores.elo.utfsm.cl/~agv/elo330/2s04/projects/doxigen/documentando.html
struct Machine* machine;
/**
 * \fn Se genera tantos objetos CPU, Cores e Hilos según se indique por parámetro.
 * \param  cantCPU cantidad de CPU a crear
 * \param  cantCore cantidad de Cores a crear
 * \param  cantHilo cantidad de Hilos a crear
 * */
void newMachine(int cantCPU, int cantCore, int cantHilos){
    // MyObject *my1 = malloc(sizeof(MyObject));
    //https://www.delftstack.com/es/howto/c/c-malloc-struct/
    
    
    int i,j,k;
    machine= malloc(sizeof(Machine));
    machine->listaCPUs = (CPU*) malloc(sizeof(CPU)* cantCPU);

    //parametrización del tamaño de las estructuras
    if(cantCPU>MAX_Cpu) cantCPU=MAX_Cpu;
    if(cantCore>MAX_Core) cantCore=MAX_Core;
    if(cantHilos>MAX_t) cantHilos=MAX_t;

    for (i = 0; i < cantCPU; i++)
    {
        struct CPU * cpu = crearCpu(i, cantCore);
        for (j = 0; j < cantCore; j++)
        {
            struct Core * core = crearCore(j, cantHilos);
            cpu  ->listCores[j] = core;
            for (k = 0; k < cantHilos; k++)
            {
                struct Hilo * thread = crearHilo(k);
                core ->listHilos[k] = thread;
            }   
        }
    }
}