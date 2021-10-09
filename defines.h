/**
 * \mainpage Proyecto2021_SO
 * \author Alfred && Jorshua Briones
 * \date octubre-2021
 */

struct Nodo {
    int data;
    struct nodo *next;
};

struct Clock
{
    int ciclo;
};

struct Timer
{
    int idTimer;
};

typedef struct PCB{
    int idPCB;
    int tiempo_vida;
    Timer timer;
}PCB;

typedef struct Hilo{
    int idHilo;
    PCB task;
} Hilo;

typedef struct Core{
    int idCore;
    Hilo ListHilos[];
} Core;

struct CPU{
    int idCPU;
    Core listCores[];
} CPU;

