#include <stdlib.h>
#include <stdio.h>
#include "clunkyAdvEvents.h"

unsigned long clunky_button_init(struct Clunky_Button *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type){
    //check to make sure the type is 'r' or 't'
    if (type != 'r' && type != 't') return 0;

    //copy over the type
    b->type = type;

    //copy over the x & y positions
    b->x = x;
    b->y = y;

    //copy over the sprite address
    b->s = s;

    //get the width and height of the buttons hit box from the sprite
    b->w = b->s->cell.w;
    b->h = b->s->cell.h;

    //set the clicked status to false
    b->clicked = 0;

    //set the row number
    b->row = row;

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
                if (b[i].type == 'r'){    
                    //regular button
                    //set the clicked status to 1 ->true
                    b[i].clicked = 1;
                }
                else{
                    //toggle button
                    if (b[i].clicked) b[i].clicked = 0;
                    else b[i].clicked = 1;
                }
                return b[i].bid;
            }
        }

    }

    return 0;
}

int clunky_button_render(struct Clunky_Button *b, struct Clunky_Window *w){
    //if the button isnt clicked, render col 1
    if (!b->clicked){
        //render the unclicked version
        clunky_render_sprite(b->x, b->y, b->row, 0, b->s, w);
    }
    else{
        //render the clicked version
        clunky_render_sprite(b->x, b->y, b->row, 1, b->s, w);
        //incriment the clicked counter by one
        //this will be used to add a slight delay in how long the texture will change

        if (b->type == 'r'){
            //regular button sprite rendering
            b->clicked += 1;

            //if the clicked couter is over 10, reset it
            if (b->clicked > 10) b->clicked = 0;
        }
    }

    return 0;
}

