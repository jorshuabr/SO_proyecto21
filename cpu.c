/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

//Como documentar en C  http://profesores.elo.utfsm.cl/~agv/elo330/2s04/projects/doxigen/documentando.html

/**
 * \fn Se genera tantos objetos CPU, Cores e Hilos según se indique por parámetro.
 * \param  cantCPU cantidad de CPU a crear
 * \param  cantCore cantidad de Cores a crear
 * \param  cantHilo cantidad de Hilos a crear
 * */
void newCPU(int cantCPU, int cantCore, int cantHilos){
    // MyObject *my1 = malloc(sizeof(MyObject));
    //https://www.delftstack.com/es/howto/c/c-malloc-struct/
    int i,j,k;
    for (i = 0; i < cantCPU; i++)
    {
        struct CPU * cpu = malloc(sizeof(CPU));
        cpu->idCPU = i+100;
        for (j = 0; j < cantCore; j++)
        {
            struct Core * core = malloc(sizeof(Core));
            core ->idCore = j+200;
            cpu  ->listCores[j] = core;
            for (k = 0; k < CantHilos; k++)
            {
                struct Hilo * thread = malloc(sizeof(Hilo));
                thread->idHilo = k+300;
                core  ->listHilos[k] = thread;
            }   
        }
    }
}