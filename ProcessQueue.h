#ifndef PROCESSQUEUEH
#define PROCESSQUEUEH
#include "defines.h"

void initialize_queue();
processQueue_t* init_queue_core();
void print(processQueue_t* p);
pcb_t deque(processQueue_t* p);
void enque(pcb_t task, processQueue_t* p);
bool isEmpty(processQueue_t* q);
bool max(processQueue_t* q);
int size(processQueue_t* q);

#endif

