#include "clunkyPQueue.h"

struct Clunky_Priority_Queue *clunky_get_pq(int mem_size){
    //init a new pq
    //allocate memory
    struct Clunky_Priority_Queue *pq = (struct Clunky_Priority_Queue *) malloc (sizeof(struct Clunky_Priority_Queue));

    //setdefault parameters
    pq->mem_size = mem_size;
    pq->len = 32;
    pq->used = 0;

    //allocate the wrapepr array
    pq->pq = (struct Clunky_Priority_Wrapper **) malloc (sizeof(struct Clunky_Priority_Wrapper *) * pq->len);

    return pq;
}

int clunky_pq_grow(struct Clunky_Priority_Queue *pq){
    //dynamically grow the pq array
    //create a temporary hold array
    struct Clunky_Priority_Wrapper **hold = pq->pq;

    //double the size of the pq array
    pq->len *= 2;

    //allocate the new memory
    pq->pq = (struct Clunky_Priority_Wrapper **) malloc (sizeof(struct Clunky_Priority_Wrapper *) * pq->len);

    //copy over the memory addr of the wrappers
    for (int i = 0; i < (pq->len/2); i++) pq->pq[i] = hold[i];

    //free the hold array
    free(hold);

    return 0;
}

int clunky_pq_free(struct Clunky_Priority_Queue *pq){
    //free all of the dynamic memory stored in the pq
    for (int i = 0; i < pq->used; i++){
        free(pq->pq[i]->obj);
    }

    free(pq->pq);

    return 0;
}


int clunky_pq_remove(int indx, struct Clunky_Priority_Queue *pq){
    //remove the requested element out of the 






