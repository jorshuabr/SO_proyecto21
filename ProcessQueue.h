#include "defines.h"

void initialize_queue();
processQueue_t* init_queue_core();
void print();
pcb_t deque(processQueue_t* p);
void enque(pcb_t task, processQueue_t* p);
bool isEmpity(processQueue_t* q);
int size(processQueue_t* q);