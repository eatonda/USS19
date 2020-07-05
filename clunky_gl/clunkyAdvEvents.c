#include <stdlib.h>
#include <stdio.h>
#include "clunkyAdvEvents.h"

unsigned long clunky_button_init(struct Clunky_Button *b, struct Clunky_Sprite *s, int x, int y, const char *b_name){
    //copy over the x & y positions
    b->x = x;
    b->y = y;

    //copy over the sprite address
    b->s = s;

    //get the width and height of the buttons hit box from the sprite
    b->w = b->s->cell.w;
    b->h = b->s->cell.h;

    //generate the BID
    b->bid = clunky_hash_gen(b_name);

    //return the BID
    return b->bid;
}

unsigned long clunky_button_check(struct Clunky_Button *b, int num, struct Clunky_Event *e){
    //make sure that the left button is clicked first
    if (!e->lc) return 0;

    int i;
    for (i = 0; i < num; i++){
        //check to see if the mouse is in the bounding box of one of the buttons
        if ( e->mx >= b[i].x && e->mx <= (b[i].x + b[i].w)){
            if (e->my >= b[i].y && e->my <= (b[i].y + b[i].h)){
                return b[i].bid;
            }
        }

    }

    return 0;
}

