#include "clunkyCore.h"

#ifndef CLUNKYPQUEUE_H
#define CLUNKYPQUEUE_H

struct Clunky_Priority_Wrapper{
    int prio;

    void *obj;

};

struct Clunky_Priority_Queue{
    struct Clunky_Priority_Wrapper **q;
    int len;
    int used;
}

struct Clunky_Priority_Queue *clunky_get_pq();


#endif
