#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
    if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
    /* TODO: put a new process to queue [q] */
    if(q == NULL) {
        perror("Queue is NULL\n");
        exit(1);
    }
    if(q->size == MAX_QUEUE_SIZE ){
        perror("Queue is full now\n");
        exit(1);
    }
    q->proc[q->size] = proc;
    q->size ++;
}

struct pcb_t * dequeue(struct queue_t * q) {
    /* TODO: return a pcb whose priority is the highest
        * in the queue [q] and remember to remove it from q
        * */   
    if(q == NULL || q->size == 0) {
        return NULL;
    }
#ifdef MLQ_SCHED
    int size = q->size;
    struct pcb_t* temp = q->proc[0];
    for(int i = 0;i < size -1; i++) {
        q->proc[i] = q->proc[i+1];
    }
    //free(q->proc[size-1]);
    q->proc[size - 1] = NULL;
    q->size --;
    return temp;
// #else
//     return NULL;
#endif

}

