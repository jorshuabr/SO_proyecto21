#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include "ProcessQueue.h"
#include "globals.h"
#include "machine.h"
#include "pcb.h"
//generalProcessQueue = nueva cola de procesos general

/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */

#define MAX_PROCESS COLA_TOTAL
#define CLOCK_FRECUENCY 1000
#define MAX_VIDA 1000

#define cantCPU 1
#define cantCore 4
#define cantHilos 4


machine_t* machine;
processQueue_t pq;
pthread_mutex_t m_clock_timer;

unsigned long int idPCB;
int buffer_clock_timer, buffer_timer_sch;

void* m_clock(void *tid); 
void* m_timer(void *tid);
void* processGenerator(void *tid);

void inicializar(){
    srand(time(0));  
    buffer_clock_timer=0;
    idPCB = 1;
    pthread_mutex_init(&m_clock_timer, NULL);
    initialize_queue();
    newMachine(cantCPU, cantCore, cantHilos);
    printf("arrancar los hilos\n ");
    pthread_create(&(machine->listaCPUs[0].listCores[0].listHilos[0].pthread_real),NULL,m_clock,&(machine->listaCPUs[0].listCores[0].listHilos[0].idHilo));
    pthread_create(&(machine->listaCPUs[0].listCores[0].listHilos[1].pthread_real),NULL,m_timer,&(machine->listaCPUs[0].listCores[0].listHilos[1].idHilo));
    pthread_create(&(machine->listaCPUs[0].listCores[0].listHilos[2].pthread_real),NULL,processGenerator,&(machine->listaCPUs[0].listCores[0].listHilos[2].idHilo)); //probar a ver que tal 
    //&(machine->listaCPUs[0].listCores[0].listHilos[0].pthread_real)
}

int main(int argc, char const *argv[])
{
    /* main main */
    inicializar();
    int i,j,k;
    pthread_mutex_lock(&m_clock_timer);
    for (i = 0; i < cantCPU; i++)
    {
        printf("--> CPU %d \n", machine->listaCPUs[i].idCPU);
        for (j = 0; j < cantCore; j++)
        {
            printf(" ----> CORE %d \n", machine->listaCPUs[i].listCores[j].idCore);
            for (k = 0; k < cantHilos; k++)
            {
                printf(" -------> HILO %d \n", machine->listaCPUs[i].listCores[j].listHilos[k].idHilo);
            }
            
        }
    }
    sleep(2);
    pthread_mutex_unlock(&m_clock_timer);    
    int cont=0;
    while(1){    
        printf(""); 
    }
    return 0;
}

/**
 * 
 * */
void* m_clock(void *tid){
    printf("empieza el clock\n");
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer);
        buffer_clock_timer++;
        printf("");//printf("pulso de reloj\n");
        pthread_mutex_unlock(&m_clock_timer);
        //y aqui haria cosas
        usleep(1000);
    }
}

/**
 * \fn 
 * \param 
 * */
void* m_timer(void *tid){
    printf("empieza el timer\n");
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer);
        if(buffer_clock_timer == CLOCK_FRECUENCY){
            buffer_clock_timer=0;
            printf("--------------tic del timer\n");
            //hay que meter un semaforo por aqui
            buffer_timer_sch=1;
        }
        pthread_mutex_unlock(&m_clock_timer);
        usleep(1000);
    }
}

/**
 * \fn verifica el buffer que sirve de señal de verificación enviada por el timer, de estar activada(1)
 * llama a la función crearPcb() y agrega las PCBs creadas a la cola general de tareas 'generalProcessQueue'
 * */
void* processGenerator(void *tid){
    printf("empieza el process generator \n");
    while (1)
    {
        if (buffer_timer_sch == 1)
        {
            buffer_timer_sch = 0;

            pcb_t * task = crearPcb(idPCB,MAX_VIDA - rand()%(MAX_VIDA/2));
            printf(":::::::::::::creado pcb con id %i y con vida %i \n ", task->idPCB, task->tiempo_vida);
            idPCB++;
            enque(*task,&pq);
            if(idPCB % 20 == 0){
                pthread_mutex_lock(&m_clock_timer);
                printf("\n elementos de la Process Queue: \n");
                print(&pq);
                sleep(5);
                pthread_mutex_unlock(&m_clock_timer);
            }
        }
    }
}