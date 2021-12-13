/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "hilo.h"
#include "core.h"
#include "cpu.h"
#include "globals.h"
#define MAX_Cpu MAX_CPUS
#define MAX_Core MAX_CORES
#define MAX_t MAX_THREADS

extern machine_t* machine;
//quizas haya que meterlo en el main, esta por ver

//Como documentar en C  http://profesores.elo.utfsm.cl/~agv/elo330/2s04/projects/doxigen/documentando.html
/**
 * \fn Se genera tantos objetos cpu_t, Cores e Hilos según se indique por parámetro.
 * \param  cantCPU cantidad de cpu_t a crear
 * \param  cantCore cantidad de Cores a crear
 * \param  cantHilo cantidad de Hilos a crear
 * */
void newMachine(int cantCPU, int cantCore, int cantHilos){
    // MyObject *my1 = malloc(sizeof(MyObject));
    //https://www.delftstack.com/es/howto/c/c-malloc-struct/
    
    
    int i,j,k;
    machine = malloc(sizeof(machine_t));
    if(cantCPU>MAX_Cpu) cantCPU=MAX_Cpu;
    machine->listaCPUs = (cpu_t*) malloc(sizeof(cpu_t)* cantCPU);

    //parametrización del tamaño de las estructuras
    
    if(cantCore>MAX_Core) cantCore=MAX_Core;
    if(cantHilos>MAX_t) cantHilos=MAX_t;

    for (i = 0; i < cantCPU; i++)
    {
        cpu_t * cpu = crearCpu(i, cantCore);
        machine->listaCPUs[i]=*cpu;
        for (j = 0; j < cantCore; j++)
        {
            core_t * core = crearCore(j, cantHilos);
            cpu  ->listCores[j] = *core;
            for (k = 0; k < cantHilos; k++)
            {
                hilo_t * thread = crearHilo(10*j+k);
                core ->listHilos[k] = *thread;
            }   
        }
    }
}
