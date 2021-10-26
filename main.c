/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "defines.h"
#include pcb.c;
#define NPCB = 20;
#define PCB vTask[NPCB];

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

/**
 * \fn Crea nuevas PCB y las agrega al vector vTask
 * \param  NPCB cantidad de PCB a crear
 * */
void processGenerator(int NPCB){
    int i;
    auto gen;
    for (i = 0; i < NPCB; i++)
    {
        gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine()
        struct PCB * task = crearPcb(i);
        prioritario -> 
        vTask[i] = task;
    }
}

void clock(){

}

