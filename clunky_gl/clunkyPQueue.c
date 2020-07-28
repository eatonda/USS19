#include "clunkyPQueue.h"

struct Clunky_Priority_Queue *clunky_get_pq(int mem_size){
    //init a new pq
    //allocate memory
    struct Clunky_Priority_Queue *pq = (struct Clunky_Priority_Queue *) malloc (sizeof(struct Clunky_Priority_Queue));

    //setdefault parameters
    pq->mem_size = mem_size;
    pq->len = 32;
    pq->used = 0;

    return pq;
}

int clunky_pq_grow(struct Clunky_Priority_Queue *pq){
    //dynamically grow the pq array

