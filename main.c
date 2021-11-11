/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include <pthread.h>
#include <semaphore.h> 
#include "ProcessQueue.h"
//generalProcessQueue = nueva cola de procesos general

#define MAX_PROCESS COLA_TOTAL
#define CLOCK_FRECUENCY 1000
#define MAX_VIDA 1000

extern Machine* machine;
extern ProcessQueue pq;
pthread_mutex_t m_clock_timer;

unsigned long int idPCB;
int buffer_clock_timer, buffer_timer_sch;

void inicializar(){
    srand(time(NULL));  
    buffer_clock_timer=0;
    idPCB = 1;
    pthread_mutex_init(&m_clock_timer, NULL);
    initialize_queue();
    newMachine();
    pthread_create(NULL,NULL,clock,NULL);
    pthread_create(NULL,NULL,timer,NULL);
    pthread_create(NULL,NULL,processGenerator,NULL); //probar a ver que tal 
}


int main(int argc, char const *argv[])
{
    /* main main */
    inicializar();


    return 0;
}

/**
 * 
 * */
void* clock(){

    while (1)
    {
        pthread_mutex_lock(&m_clock_timer);
        buffer_clock_timer++;
        pthread_mutex_unlock(&m_clock_timer);
        //y aqui haria cosas
    }
    
    
}

/**
 * \fn 
 * \param 
 * */
void* timer(){
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer);
        if(buffer_clock_timer == CLOCK_FRECUENCY){
            buffer_clock_timer=0;
            //hay que meter un semaforo por aqui
            buffer_timer_sch=1;
        }
        pthread_mutex_unlock(&m_clock_timer);
    }
}

/**
 * \fn verifica el buffer que sirve de señal de verificación enviada por el timer, de estar activada(1)
 * llama a la función crearPcb() y agrega las PCBs creadas a la cola general de tareas 'generalProcessQueue'
 * */
void* processGenerator(){
    
    if (buffer_timer_sch == 1)
    {
        buffer_timer_sch = 0;
        struct PCB * task = crearPcb(idPCB);
        task->tiempo_vida=MAX_VIDA - rand()%(MAX_VIDA/2);
        idPCB++;
        enque(*task,&pq);
    }
    
    
}