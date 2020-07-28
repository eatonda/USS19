#include "clunkyCore.h"

#ifndef CLUNKYPQUEUE_H
#define CLUNKYPQUEUE_H

struct Clunky_Priority_Wrapper{
    int prio;

    void *obj;

};

struct Clunky_Priority_Queue{
    struct Clunky_Priority_Wrapper **pq;
    int len;
    int used;
    int mem_size;
}

struct Clunky_Priority_Queue *clunky_get_pq(int mem_size);
int clunky_pq_grow(struct Clunky_Priority_Queue *pq);
int clunky_pq_remove(int indx, struct Clunky_Priority_Queue *pq);
void *clunky_pop(struct Clunky_Priority_Queue *pq);
void *clunky_peek(struct Clunky_Priority_Queue *pq);
int clunky_insert(void *obj, int prio, struct Clunky_Priority_Queue *pq);
int clunky_pq_free(struct Clunky_Priority_Queue *pq);


#endif
