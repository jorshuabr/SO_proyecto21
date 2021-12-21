#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include <pthread.h>
#include <semaphore.h> 
#include "ProcessQueue.h"
#include "globals.h"
#include "machine.h"
#include "pcb.h"
#include "unistd.h"
#include <math.h>
#include <string.h>

/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */

#define MAX_PROCESS COLA_TOTAL
#define CLOCK_FRECUENCY 1000


machine_t* machine;
processQueue_t pq;
pthread_mutex_t m_clock_timer, m_clock_timer2, m_sched_timer,m_sched_core;
pthread_cond_t proceso_disponible;
sem_t nuevo_proceso,nuevo_tick;
physical_t* memoria_fisica;
cantidades_t* cantidad;

unsigned long int idPCB;
int buffer_clock_timer, tick_global, buffer_timer_sch, buffer_pg_sc, indice_archivo;
int* colas_cores;
pthread_t* arrayThreads; //vector de hilos reales

void* m_clock(void *tid); 
void* m_timer1(void *tid);
void* m_timer2(void *tid);
void* loader(void *tid);
void* m_scheduler(void *tid);
int buscarCola();
void direccionCore(int* cpu, int* core, int valor);
void* ejecutarCore(void *core);
int buscarDisponible(hilo_t * listaHilos);

void inicializar(){
    colas_cores=malloc(sizeof(int)*cantidad->cpus*cantidad->cores);
    arrayThreads=malloc(sizeof(pthread_t)*(5+cantidad->cpus*cantidad->cores));
    memoria_fisica = malloc(sizeof(physical_t));
    memoria_fisica->memoria= malloc(sizeof(int)*pow(2,24));
    memoria_fisica->tabla_paginas = malloc(sizeof(int)*49152);
    memoria_fisica->pagina_ocupada = malloc(sizeof(bool)*49152);
    srand(time(0));  
    buffer_clock_timer=0;
    buffer_pg_sc=0;
    tick_global=0;
    idPCB = 0;
    indice_archivo=0;
    pthread_mutex_init(&m_clock_timer, NULL);
    pthread_mutex_init(&m_clock_timer2, NULL);
    pthread_mutex_init(&m_sched_timer,NULL);
    pthread_mutex_init(&m_sched_core, NULL);
    pthread_cond_init(&proceso_disponible,NULL);
    sem_init(&nuevo_proceso,0,1);
    sem_init(&nuevo_tick,0,1);

    initialize_queue();
    newMachine(cantidad->cpus, cantidad->cores, cantidad->hilos);
    printf("arrancar los hilos\n ");
    int i,cpu,core,total;
    cpu=0;
    core=0;
    total = cantidad->cpus*cantidad->cores;
    for(i=0;i<total;i++ ) {
        colas_cores[i]=0;printf("todo correcto en vuelta %d \n",i);
    }
    printf("crear colas bien\n ");
    for(i=0;i< (total+5);i++){
        arrayThreads[i]=i;
        if(i<(total)){
            direccionCore(&cpu,&core,i);
            pthread_create(&arrayThreads[i],NULL,ejecutarCore,&(machine->listaCPUs[cpu].listCores[core]));
        }
        else if (i==total){
            pthread_create(&arrayThreads[i],NULL,m_clock,NULL);
        }else if(i==total+1){
            pthread_create(&arrayThreads[i],NULL,m_timer1,NULL);
        }else if(i==total+2){
            pthread_create(&arrayThreads[i],NULL,loader,NULL);
        }else if(i==total+3){
            pthread_create(&arrayThreads[i],NULL,m_scheduler,NULL);
        }else if(i==total+4){
            pthread_create(&arrayThreads[i],NULL,m_timer2,NULL);
        }
    }

    int inicio= 4194304;
    i =0;
    while (inicio<pow(2,24)){
        memoria_fisica->tabla_paginas[i]=inicio;
        memoria_fisica->pagina_ocupada[i]=false;
        printf("bloque %d en direccion %d cargado\n",i,inicio);
        i++;
        inicio+=256;
    }
    printf("Fin del proceso de creacion de paginas de memoria, la ultima direccion es %d con indice %d  \n",inicio-256,i-1);

}
    
int main(int argc, char const *argv[])
{
    cantidad= malloc(sizeof(cantidades_t));
    if (argc != 4){
        printf("faltan o sobran parametros el orden es : cantidad->cpus, cantidad->coress, cantidad->hilos \n");
        exit(1);
    }else{
        cantidad->cpus=atoi(argv[1]);
        cantidad->cores=atoi(argv[2]);
        cantidad->hilos=atoi(argv[3]);
        
        //sleep(1000000);
        inicializar();
        int i,j,k;
        pthread_mutex_lock(&m_clock_timer);
        for (i = 0; i < cantidad->cpus; i++)
        {
            printf("--> CPU %d \n", machine->listaCPUs[i].idCPU);
        for (j = 0; j < cantidad->cores; j++)
            {
                printf(" ----> CORE %d \n", machine->listaCPUs[i].listCores[j].idCore);
                for (k = 0; k < cantidad->hilos; k++)
                {
                    printf(" -------> HILO %d \n", machine->listaCPUs[i].listCores[j].listHilos[k].idHilo);
                }
                
            }
        }
        pthread_mutex_unlock(&m_clock_timer);    
        int cont=0;
        while(1){    
            printf(""); 
        }
        return 0;
    }
    
}

/**
 * 
 * */
void* m_clock(void *tid){
    printf("empieza el clock\n");
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer2);
        pthread_mutex_lock(&m_clock_timer);
        buffer_clock_timer++;
        tick_global++;
        printf("");
        pthread_mutex_unlock(&m_clock_timer2);
        pthread_mutex_unlock(&m_clock_timer);
        usleep(1000);
    }
}

/**
 * \fn 
 * \param 
 * */
void* m_timer1(void *tid){
    printf("empieza el timer\n");
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer);
        if(buffer_clock_timer >= CLOCK_FRECUENCY){
            buffer_clock_timer=0;
            printf("--------------tic del timer\n");
            //hay que meter un semaforo por aqui
            
            buffer_timer_sch=1;
        }
        pthread_mutex_unlock(&m_clock_timer);
        usleep(1000);
    }
}

void* m_timer2(void *tid){
    printf("empieza el timer2 - reparto de tareas\n");
    while (1)
    {
        pthread_mutex_lock(&m_clock_timer2);
        if(tick_global >= CLOCK_FRECUENCY){
            tick_global=0;
            printf("--------------tic del timer global\n");
            //hay que meter un semaforo por aqui
            
            int i,j,k;
            for (i = 0; i < cantidad->cpus; i++)
            {
                for (j = 0; j < cantidad->cores; j++)
                {
                    for (k = 0; k < cantidad->hilos; k++)
                    {
                        
                        if(machine->listaCPUs[i].listCores[j].listHilos[k].ocupado){
                            machine->listaCPUs[i].listCores[j].listHilos[k].task.tiempo_vida--;
                            if(machine->listaCPUs[i].listCores[j].listHilos[k].task.tiempo_vida==0) {
                                machine->listaCPUs[i].listCores[j].listHilos[k].ocupado=false;
                                printf("el PCB con id %d en el core %d en el hilo %d ----> ha terminado  \n",machine->listaCPUs[i].listCores[j].listHilos[k].task.idPCB, machine->listaCPUs[i].listCores[j].idCore, machine->listaCPUs[i].listCores[j].listHilos[k].idHilo);
                            }
                        }
                    }
                    
                }
            }
            
        }
        pthread_mutex_unlock(&m_clock_timer2);
        usleep(1000);
    }
}

/**
 * \fn verifica el buffer que sirve de señal de verificación enviada por el timer, de estar activada(1)
 * llama a la función crearPcb() y agrega las PCBs creadas a la cola general de tareas 'generalProcessQueue'
 * */

//la funcion actual le falta el manejo de páginas y la memoria física
void* loader(void *tid){
    printf("empieza el process generator \n");
    while (1)
    {
        usleep(rand()%1000);
        pthread_mutex_lock(&m_sched_timer);

        if (buffer_timer_sch == 1)
        {
            buffer_timer_sch = 0;
            int paginaLibre=buscarPaginaLibre(),direccion_pagina_fisica;
            if(paginaLibre!= -1){
                direccion_pagina_fisica=memoria_fisica->tabla_paginas[paginaLibre];
                pcb_t * task = crearPcb(idPCB);
                printf("---------creado pcb con id %i  \n ", task->idPCB);
                idPCB++;
                int memoria[256];
                char inicio[20], variante[20], fin[20],data[20],text[20],cero[10],ruta[20];
                int mem_pos=0;
                strcpy(cero,"0");
                strcpy(inicio,"prog0");
                strcpy(fin,".elf");
                sprintf(variante,"%d",indice_archivo);
                strcpy(ruta,inicio);
                if(indice_archivo<10){
                    strcat(ruta,cero);
                }
                strcat(ruta,variante);
                strcat(ruta,fin);
                printf("ruta del archivo:   %s    \n",ruta);
                FILE *fp = fopen(ruta, "r");
                if(fp == NULL) {
                    perror("Unable to open file!");
                    exit(1);
                }
                char *line = NULL;
                size_t len = 0;
                int j=0;
                while(getline(&line, &len, fp) != -1) {
                    int k=0,encontrado= 0, x=0;
                    char espacio =' ';
                    if(j==0){
                        while(line[k]!='\n'){
                            char act=line[k];
                            if(!encontrado) encontrado=(act==espacio)?1:0;
                            if (encontrado==1){
                                if(act!=espacio){
                                    text[x]=act;
                                    x++;
                                }
                            }
                            k++;
                        }
                        printf("direccion text %s \n", text);

                    }else if(j==1) {
                        while(line[k]!='\n'){
                            char act=line[k];
                            if(!encontrado) encontrado=(act==espacio)?1:0;
                            if (encontrado==1){
                                if(act!=espacio){
                                    data[x]=act;
                                    x++;
                                }
                            }
                            k++;
                        }
                        printf("direccion data %s \n", data);

                    }else{
                        int parte=0, pos=0;
                        char bloque[3];
                        strcpy(bloque,"0");
                        while(line[k]!='\n'){
                            if(k/2!=parte){
                                memoria[mem_pos]=(int)strtol(bloque, NULL, 16);
                                printf("bloque nº %d añadido con valor %s en posicion %d \n",parte,bloque,mem_pos);
                                parte=k/2;
                                mem_pos++;
                                pos=0;
                            }
                            bloque[pos]=line[k];
                            pos++;
                            k++;
                        }
                        memoria[mem_pos]=(int)strtol(bloque, NULL, 16);
                        printf("bloque nº %d añadido con valor %s en posicion %d \n",parte,bloque,mem_pos);
                        mem_pos++;

                    }
                    printf("la linea contiene %s",line);
                    j++;

                }
                j=0;
                while(j<mem_pos){
                    memoria_fisica->memoria[direccion_pagina_fisica+j]=memoria[j];
                    j++;
                }
                printf("bloque guardado en pagina %d con direccion fisica %d \n",paginaLibre,direccion_pagina_fisica);
                strcpy(task->meme->code,text);
                strcpy(task->meme->data,data);
                task->meme->pgb=direccion_pagina_fisica;
                fclose(fp);
                free(line);
                indice_archivo++;
                enque(*task,&pq);
                buffer_pg_sc++;
                printf("Fin ciclo loader \n"); 
            }
        }
       pthread_mutex_unlock(&m_sched_timer);     
       
       usleep(1000); 
    }
}

/**
 * Método que asigna PCB a los hilos del core enviado por parámetro.
 * \param core core
 * */
void* ejecutarCore(void *core){
    core_t* c = (core_t*) core;
    while(1){
        pthread_mutex_lock(&m_sched_core);
        pthread_cond_wait(&proceso_disponible,&m_sched_core);
        if(!(isEmpty(c->queueTask)) ){
            int hiloLibre = buscarDisponible(c->listHilos);
            if(hiloLibre!=-1){
                pcb_t t= deque(c->queueTask);
                c->listHilos[hiloLibre].task= t;
                c->listHilos[hiloLibre].ocupado= true;
                printf("Tarea %d --enviada--> Core %d: [Hilo %d]   \n",t.idPCB,c->idCore,c->listHilos[hiloLibre].idHilo);
            }
            
        }
        pthread_mutex_unlock(&m_sched_core);
    }
}

/**
 * \fn Función que realiza la comprobación si el hilo se encuentra con un PCB asignado.
 * \param listaHilos lista de hilos de un core
 * \return 1 hilo disponible | -1 hilo ocupado.
 * */
int buscarDisponible(hilo_t * listaHilos)//bol[] x
{
    int i =0;
    int pos;
    bool encontrado=false;
    while(i< cantidad->hilos && !encontrado){
        //printf("vueltaaaaa %d \n",i);
        if(!listaHilos[i].ocupado){
            encontrado = true;
            pos=i;
        }
        i++;        
    }   
    //printf("terminado \n");
    return (encontrado)?pos:-1;
}


/**
 * Método que realiza el reparto de PCB entre las colas de los diferentes cores.
 * \param tid 
 * */
void* m_scheduler(void *tid){
    int cpu, core, objetivo;
    printf("comienza el scheduler\n");
    while(1){
        
        if(buffer_pg_sc>0){
            objetivo= buscarCola();
            if(objetivo!=-1){
                direccionCore(&cpu, &core, objetivo);
                pcb_t tmp=deque(&pq);
                enque(tmp,(machine->listaCPUs[cpu].listCores[core].queueTask));
                printf("pcb con id -> %d encolado en la cola de la cpu %d y core %d \n",tmp.idPCB,cpu,core);
                if(max((machine->listaCPUs[cpu].listCores[core].queueTask))){
                    colas_cores[objetivo]=1;
                }
                buffer_pg_sc--;
                pthread_cond_signal(&proceso_disponible);
            }
        }
        usleep(1000);
        
    }
}

void direccionCore(int* cpu, int* core, int valor){
    *cpu=valor/cantidad->cores;
    *core=valor%cantidad->cores;
}

int buscarCola(){
    int i=0;
    int max=(cantidad->cpus*cantidad->cores -1)*4;
    int encontrado=0;
    int prueba =0;
    while (!encontrado && i<max){
        prueba=rand()%(cantidad->cpus*cantidad->cores);
        if (colas_cores[prueba]==0) encontrado =1;
        i++;
    }
    return (encontrado==1)? prueba:-1;
}



int buscarPaginaLibre(){
    int i=0;
    bool encontrado=false;
    while ( !encontrado && i!=49152){
        encontrado = !memoria_fisica->pagina_ocupada[i];
        i+=(encontrado)?0:1;
    }
    if(encontrado)memoria_fisica->pagina_ocupada[i]=true;
    return(encontrado)?i:-1;
}

bool ejecutarCicloHilo(hilo_t *hiloActual){
    bool terminado;
    int  direccion_instruccion_act=0;
    if (hiloActual->pc != "X"){
        direccion_instruccion_act=traducirDireccion(hiloActual->pc);
    }

    direccion_instruccion_act+= hiloActual->task.meme->pgb;
    unsigned char* palabra =malloc(sizeof(unsigned char)*9);
    palabra= obtenerPalabra(direccion_instruccion_act);
    strcpy(hiloActual->ir,palabra);
    char instruccion = palabra[0];
    switch (instruccion){
        //caso exit
        case 'F' : 
            terminado= true;
            break;

        //caso load
        case '0' :
            int direccion_registro;
            char rx[2];
            strcpy(rx,palabra[1]);
            direccion_registro=traducirDireccion(rx);
            char v_direccion[7];
            int i=2;
            while(i!=8){
                char tmp[2];
                sprintf(tmp,"%X",palabra[i]);
                if(i==2){
                    strcpy(v_direccion,tmp);
                }else{
                    strcat(v_direccion,tmp);
                }
                i++;
            }
            int direccion_virtual= traducirDireccion(v_direccion)+hiloActual->task.meme->pgb;
            palabra=obtenerPalabra(direccion_virtual);
            int valor_memoria= traducirDireccion(palabra);
            hiloActual->registro[direccion_registro]=valor_memoria;
            break;


        //caso store
        case '1':
            int direccion_registro;
            char rx[2];
            strcpy(rx,palabra[1]);
            direccion_registro=traducirDireccion(rx);
            char v_direccion[7];
            int i=2;
            while(i!=8){
                char tmp[2];
                sprintf(tmp,"%X",palabra[i]);
                if(i==2){
                    strcpy(v_direccion,tmp);
                }else{
                    strcat(v_direccion,tmp);
                }
                i++;
            }
            int direccion_virtual= traducirDireccion(v_direccion)+hiloActual->pc;
            unsigned char* valor_reg = malloc(sizeof(unsigned char)*9);
            sprintf(valor_reg,"%X",hiloActual->registro[direccion_registro]);
            while(valor_reg[8]!='\n'){
                char cero[9];
                strcpy(cero,"0");
                strcat(cero,valor_reg);
                strcpy(valor_reg,cero);
            }

            int parte=0, pos=0, k =0;
            char bloque[3];
            strcpy(bloque,"0");
            while(valor_reg[k]!='\n'){
                if(k/2!=parte){
                    memoria_fisica->memoria[direccion_virtual]=(int)strtol(bloque, NULL, 16);
                    printf("bloque nº %d añadido con valor %s en posicion %d \n",parte,bloque,direccion_virtual);
                    parte=k/2;
                    direccion_virtual++;
                    pos=0;
                }
                bloque[pos]=valor_reg[k];
                pos++;
                k++;
            }
            memoria_fisica->memoria[direccion_virtual]=(int)strtol(bloque, NULL, 16);
            printf("bloque nº %d añadido con valor %s en posicion %d \n",parte,bloque,direccion_virtual);
            
            
        //caso add
        case '2':
            char rx[2];
            strcpy(rx,palabra[1]);
            int direccion_registro_destino= traducirDireccion(rx);
            strcpy(rx,palabra[2]);
            int direccion_registro_a=traducirDireccion(rx);
            strcpy(rx,palabra[3]);
            int direccion_registro_b=traducirDireccion(rx); 
            hiloActual->registro[direccion_registro_destino]=hiloActual->registro[direccion_registro_a] + hiloActual->registro[direccion_registro_b];
            break;
            
    }
    direccion_instruccion_act=0;
    if(hiloActual->pc!="X")direccion_instruccion_act=traducirDireccion(hiloActual->pc);
    direccion_instruccion_act+=4;  
    sprintf(hiloActual->pc,"%X",direccion_instruccion_act);
    return terminado;
}


//recibe un char en hexadecimal y devuelve un entero en base 10 tambien sirve para convertir los valores de los datos
int traducirDireccion(unsigned char *direccion){
    int x=(int)strtol(direccion, NULL, 16); 
    char temp[10];
    sprintf(temp,"%d",x);
    x=(int)strtol(temp, NULL, 10);
    return x;
}

unsigned char* obtenerPalabra(int posicion){
    unsigned char* palabra= malloc(sizeof(unsigned char)*9);
    int max= posicion+4;

    char reconstruccion[20],cero[2];
    strcpy(cero,"0");
    while(posicion<max){
        char temp[3];
        if(max-posicion==4){
            sprintf(temp,"%X",memoria_fisica->memoria[posicion]);
            if(strlen(temp)==1){
            strcpy(reconstruccion,cero);
            strcat(reconstruccion,temp);
            }else{
            strcpy(reconstruccion,temp);
            }
            
        }else{
            sprintf(temp,"%X",memoria_fisica->memoria[posicion]);
            if(strlen(temp)==1) strcat(reconstruccion,cero);
            strcat(reconstruccion,temp);
        }
        printf("el valor en %d es %s\n",posicion,temp);
        posicion++;
    }
    strcpy(palabra,reconstruccion);
    return palabra;
}
