#include <stdlib.h>
#include <stdio.h>
#include "clunkyEventElements.h"

unsigned long clunky_element_init(struct Clunky_Event_Element *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type, char effect){
    //we need to verify that the element's type and effect are valid parameters
    //Declare valid type and effect labels
    char valid_type[] = {'B', 'T', 'D', 'S'};
    const int valid_type_cnt = 4;
    char valid_effect[] = {'T', 'R', 'N', 'A', 'H', 'R'};
    const int valid_effect_cnt = 6;
    
    //now check to make sure that the type and effect passed are in 
    //the list of valid options
    int i, cont = 0;
    //check the type
    for (i = 0; i < valid_type_cnt; i++){
        if (type == valid_type[i]) cont = 1;
    }
    
    //if we didnt find a valid type, stop
    if (!cont) return 0;
    else cont = 0;
    
    //check the effect
    for (i = 0; i < valid_effect_cnt; i++){
        if (effect == valid_effect[i]) cont = 1;
    }

    //if we didnt find a valid effect, stop
    if (!cont) return 0;

    //at this point we know that we have valid type and effect parameters,
    //so begin to init the element
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

    //get the max column count
    b->col_max = s->texture->width  / s->cell.w;

    //generate the BID
    b->eid = clunky_hash_gen(b_name);

    //return the BID
    return b->eid;
}

unsigned long clunky_element_update_OLD(struct Clunky_Event_Element *b, int num, struct Clunky_Event *e){

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
                else if (b[i].interact == 2 && e->lcs) b[i].interact = 2;
                else b[i].interact = 1; //hovering

                //if the mouse click is being sustained
                //and if the element is a dragable, update its position
                if (e->lcs && b[i].type == 'D'){
                    b[i].x += e->dx;
                    b[i].y += e->dy;
                }
        else{
            //set ineract to not hover or clicked
            //if the mouse click is being sustained
            //and if the element is a dragable, update its position
            if (e->lcs && b[i].interact == 2 && b[i].type == 'D'){
                b[i].x += e->dx;
                b[i].y += e->dy;
            }
            else{
                //otherwise just reset the click indicator
                b[i].interact = 0;
            }
        }

    }
    }



    return eid;
}

int clunky_element_render(struct Clunky_Event_Element *b, struct Clunky_Window *w){
    if (b->interact == 1 && b->effect != 'R' && b->effect != 'H'){
        //render the unclicked version
        clunky_render_sprite(b->x, b->y, b->row, 0, b->s, w);
    }
    else if (b->effect == 'A'){
        //render the elements sprite at the respectful animation cell
        int ani = w->animation_counter % b->col_max;
        clunky_render_sprite(b->x, b->y, b->row, ani, b->s, w);
    }
    else if (!b->interact){
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

int clunky_eec_init(struct Clunky_Event_Element_Container *eec){
    //need to allocate the initial memory for the event elements
    //start with 5 ee's
    eec->len_ele = 5;
    //and make note that we are using 0 cells
    eec->num_ele = 0;

    //init the memory for the buttons
    eec->elements = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);

    return 0;
}

int clunky_eec_free(struct Clunky_Event_Element_Container *eec){
    int i;
    //will free all of the memory assosiated with the EEC, included the ee's
    //first, free the string in the summary
    if (eec->sum.str != NULL) free(eec->sum.str);

    //now all of the elements that have been put inside the eec
    for (i = 0; i < eec->num_ele; i++) free(eec->elements[i]);

    //now free the element array itself
    free(eec->elements);
    eec->elements = NULL;

    return 0;
}

int clunky_eec_grow(struct Clunky_Event_Element_Container *eec){
    int i;
    //dynamicly allocate and grow the elements array in the eec
    //have a temp pointer to hold the addr of the current array
    struct Clunky_Event_Element **addr_hold = eec->elements;

    //grow the size of the eec elements array
    //double the capacity
    eec->len_ele *= 2;
    
    //reallocate the memory
    eec->elements = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);

    //copy over all of the old ee's
    for (i = 0; i < eec->num_ele; i++) eec->elements[i] = addr_hold[i];

    //free the hold array
    free(addr_hold);

    //return the new size of the array
    return eec->len_ele;
}

int clunky_eec_add_elements(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element *ele, int num_ele){
    int i;
    //first, make sure that the eec's element array has the capacity, 
    //if not grow it
    if ((eec->num_ele + num_ele) > eec->len_ele) clunky_eec_grow(eec);

    //now copy over the memory addresses!
    for (i = 0; i < num_ele; i++) eec->elements[i + eec->num_ele] = &(ele[i]);

    //make note of how many elements where just added
    eec->num_ele += num_ele;

    return 0;
}

int clunky_mouse_interaction_helper(struct Clunky_Event_Element * ele, struct Clunky_Event *e){
    //local helper function to set the itneract status of elements
    if ( e->mx >= ele->x && e->mx <= (ele->x + ele->w) &&
             e->my >= ele->y && e->my <= (ele->y + ele->h)){
        //check to see if the mouse was clicked
        if (e->lc){
            //set the itneraction to 2 ->clicked
            ele->interact = 2;

            //return that the element was clicked
            return 2;
        }
        else{
            //otherwise we are just hovering over the button
            ele->interact = 1;

            //return that the element is hovered over
            return 1;
       }

    }
    else{
        //the button isnt being interacted with in a meaningful way
        //set interact to 0 -> no interaction
        ele->interact = 0;

        //return that there was no interaction
        return 0;
    }
}

int clunky_eec_update(struct Clunky_Event_Element_Container *eec, struct Clunky_Event *e, struct Clunky_Window *w){
    int i, status;
    //first, for legibility, I'm going to create a pointer reference towards the eec's summary element
    //this is just to try to make the code have fewer de-references
    //because theres going to be a lot going on in this function
    struct Clunky_Event_Summary *summary = &(eec->sum);
    //clear the previous eid in case there isnt a new one this itteration
    summary->eid = 0;

    //we need to now loop through every element in the eec
    for (i = 0; i < eec->num_ele; i++){
        //check to see if the element is being interacted with
        status = clunky_mouse_interaction_helper(eec->elements[i], e);

        //if the element was clicked, status == 2, make note of the eid for the summary
        if (status == 2) summary->eid = eec->elements[i]->eid;

        //some elements require extra proccessing than just hovered or clicked
        //use a switch statement to orginize the code
        switch(eec->elements[i]->type){
            case 'D': //Draggable Element

                //Ok, first, we need to see if the element was interacted with.
                //If so, we need to set the dragging (misc) status to indicate that
                if (status == 2) eec->elements[i]->misc = 1;
                //else if misc already is 1, and lcs is not true (i.e. the player let go of the
                //element) then set the misc status back to 0
                else if (e->lcs == 0) eec->elements[i]->misc = 0;

                //if the misc status is set to true, then the element is being dragged
                //thus we need to update its x/y location
                if (eec->elements[i]->misc){
                    //update the x, y coords of the element
                    eec->elements[i]->x += e->dx;
                    eec->elements[i]->y += e->dy;
                }
                

                break;
            default:
                break;
         }

        //now render the element to the window
        clunky_element_render(eec->elements[i], w);
    }

    return 0;
}
