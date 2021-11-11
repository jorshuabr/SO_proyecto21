#include "defines.h"

void initialize_queue();
ProcessQueue* init_queue_core();
void print();
PCB deque(ProcessQueue* p);
void enque(PCB task, ProcessQueue* p);
bool isEmpity(ProcessQueue* q);
int size(ProcessQueue* q);