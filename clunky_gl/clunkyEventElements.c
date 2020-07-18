#include <stdlib.h>
#include <stdio.h>
#include "clunkyEventElements.h"

unsigned long clunky_element_init(struct Clunky_Event_Element *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type, char effect){
    //check to make sure the type is 'r' or 't'
    if (type != 'B' && type != 'T' && type != 'D' && type != 'S') return 0;

    //check to make sure that the type if 'T', 'R', 'N', 'F', 'H', 'R'
    char good[] = {'T', 'R', 'N', 'F', 'H', 'R'};
    int i, cont = 0;
    for (i = 0; i < 6; i++){
        if (effect == good[i]) cont = 1;
    }

    if (!cont) return 0;

    //copy over the type
    b->type = type;

    //copy over the effect
    b->effect = effect;

    //copy over the x & y positions
    b->x = x;
    b->y = y;

    //copy over the sprite address
    b->s = s;

    //get the width and height of the buttons hit box from the sprite
    b->w = b->s->cell.w;
    b->h = b->s->cell.h;

    //set the clicked status to false
    b->interact = 0;

    //set the row number
    b->row = row;

    //generate the BID
    b->eid = clunky_hash_gen(b_name);

    //return the BID
    return b->eid;
}

unsigned long clunky_element_update(struct Clunky_Event_Element *b, int num, struct Clunky_Event *e){

    int i;
    unsigned long eid = 0;
    for (i = 0; i < num; i++){
        //check to see if the mouse is in the bounding box of one of the buttons
        if ( e->mx >= b[i].x && e->mx <= (b[i].x + b[i].w) &&
             e->my >= b[i].y && e->my <= (b[i].y + b[i].h)){
                 
                //check to see if the user is clicking or hovering
                if (e->lc){
                    //the button was clicked!
                    b[i].interact = 2; //clicked
                    //remember the eid
                    eid = b[i].eid;
                }
                else b[i].interact = 1; //hovering

                //if the mouse click is being sustained
                //and if the element is a dragable, update its position
                if (e->lcs && b[i].type == 'D'){
                    b[i].x += e->dx;
                    b[i].y += e->dy;
                }
        else{
            //set ineract to not hover or clicked
            b[i].interact = 0;
        }

    }
    }



    return eid;
}

int clunky_element_render(struct Clunky_Event_Element *b, struct Clunky_Window *w){
    //if the button isnt clicked, render col 1
    if (!b->interact){
        //render the unclicked version
        clunky_render_sprite(b->x, b->y, b->row, 0, b->s, w);
    }
    else if (b->interact == 1 && b->effect != 'R' && b->effect != 'H'){
        //render the unclicked version
        clunky_render_sprite(b->x, b->y, b->row, 0, b->s, w);
    }
    else{
        //render the clicked version
        clunky_render_sprite(b->x, b->y, b->row, 1, b->s, w);
        //incriment the clicked counter by one
        //this will be used to add a slight delay in how long the texture will change
    }

    return 0;
}


