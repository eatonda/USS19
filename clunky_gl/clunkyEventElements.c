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

    //copy over the name
    for (i = 0; i < 256; i++)  b->name[i] = '\0';
    for (i = 0; b_name[i] != '\0'; i++){
        b->name[i] = b_name[i];
    }

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
    //start with 5 ee's and snaps
    eec->len_ele = 16;
    eec->len_snaps = 16;
    //and make note that we are using 0 cells and snaps
    eec->num_ele = 0;
    eec->num_snaps = 0;



    //init the memory for the event elements
    eec->elements = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);
    eec->snaps = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_snaps);

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
    
    //if we are out of space in the elements array, grow it
    if ( eec->num_ele  >= eec->len_ele ){

        //dynamicly allocate and grow the elements array in the eec
        //have a temp pointer to hold the addr of the current array
        struct Clunky_Event_Element **addr_hold = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);

        for (i = 0; i < eec->num_ele; i++) addr_hold[i] = eec->elements[i];

        //grow the size of the eec elements array
        //double the capacity
        eec->len_ele *= 2;
    
        //reallocate the memory
        eec->elements = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);

        //copy over all of the old ee's
        for (i = 0; i < eec->num_ele; i++){
            eec->elements[i] = addr_hold[i];
        }

        //free the hold array
        free(addr_hold);

    }

    //check to see if we need to grow the snaps array
    if ( eec->num_snaps  >= eec->len_snaps ){

        //dynamicly allocate and grow the elements array in the eec
        //have a temp pointer to hold the addr of the current array
        struct Clunky_Event_Element **addr_hold = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_snaps);
        
        for (i = 0; i < eec->num_snaps; i++) addr_hold[i] = eec->snaps[i];
        
        //grow the size of the eec elements array
        //double the capacity
        eec->len_snaps *= 2;
        
        //reallocate the memory
        eec->snaps = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_snaps);
        
        //copy over all of the old ee's
        for (i = 0; i < eec->num_snaps; i++){
            eec->snaps[i] = addr_hold[i];
        }
        
        //free the hold array
        free(addr_hold);

    }

    return 0;
}

int clunky_eec_add_elements(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element **ele, int num_ele){
    int i;
    int offset = eec->num_ele;

    //now copy over the memory addresses!
    for (i = 0; i < num_ele; i++){
        eec->elements[i + offset] = ele[i];
        eec->num_ele++;

        //check to see if we need to grow the element array
        if ( eec->num_ele  >= eec->len_ele ) clunky_eec_grow(eec);

        //if it is a snap-to element, add it to the spacial map
        if (ele[i]->type == 'S'){
            eec->snaps[eec->num_snaps++] = ele[i];
            if ( eec->num_snaps  >= eec->len_snaps ) clunky_eec_grow(eec);
        }
    }

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

            //set the mouse delta
            //(position between the elements x,y point and the mouse)
            e->dx = e->mx - ele->x;
            e->dy = e->my - ele->y;

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

float EE_Overlap_Helper(struct Clunky_Event_Element *a, struct Clunky_Event_Element *b){
    //calculate the percent overlap
    //between two ee's

//    printf("%ld -- %ld\n", a->eid, b->eid);
  //   printf("(%d,%d), (%d,%d)\n", a->x, a->y, b->x, b->y);

    float overlap = 0.;

    int w_over = 0;
    int h_over = 0;

    //figure out which element is overlap which, if any overlap is even occuring
    //the width and hieght need to be checked independantly
    //first, check the X axis overlap
    if ( a->x <= b->x && (a->x + a->w) >= b->x){
        //element B overlaps A on the X axis!
        w_over = (a->x + a->w) - b->x;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( w_over > b->w ) w_over = b->w;
    }
    else if ( b->x <= a->x && (b->x + b->w) >= a->x){
        //element A overlaps B on the X axis!
        w_over = (b->x + b->w) - a->x;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( w_over > a->w ) w_over = a->w;
    }
    else{
        //there is no overlap!
        return overlap;
    }

    //now check the Y axis overlap
    if ( a->y <= b->y && (a->y + a->h) >= b->y ){
        //element B overlaps A on the Y axis!
        h_over = (a->y + a->h) - b->y;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( h_over > b->h ) h_over = b->h;
    }
    else if ( b->y <= a->y && (b->y + b->h) >= a->y ){
        //element A overlaps B on the Y axis!
        h_over = (b->y + b->h) - a->y;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( h_over > a->h ) h_over = a->h;
    }
    else{
        //there is no overlap!
        return overlap;
    }

    //we need to know the smallist area
    int area = 0;
    if (a->w * a->h < b->w * b->h) area = a->w * a->h;
    else area = b->w * b->h;

    //return the percent overlap
   // printf("%d, %d\n", (w_over * h_over), area);
    
    return (float) (w_over * h_over) / (float) area;

}



int clunky_eec_update(struct Clunky_Event_Element_Container *eec, struct Clunky_Event *e, struct Clunky_Window *w){
    int i, status;
    //first, for legibility, I'm going to create a pointer reference towards the eec's summary element
    //this is just to try to make the code have fewer de-references
    //because theres going to be a lot going on in this function
    struct Clunky_Event_Summary *summary = &(eec->sum);
    //clear the previous eid in case there isnt a new one this itteration
    summary->event_type = 'N';

    //we need to now loop through every element in the eec
    for (i = 0; i < eec->num_ele; i++){
//        printf("EEC %d/%d  %s\n", i, eec->num_ele, eec->elements[i]->name);
        //check to see if the element is being interacted with
        if (eec->elements[i]->type != 'S'){
            status = clunky_mouse_interaction_helper(eec->elements[i], e);
        }

        //if the element was clicked, status == 2, make note of the eid for the summary
        if (status == 2){
            //set the EID_One to the eid of the clicked element, and the type to 'C'
            summary->eid_one = eec->elements[i]->eid;
            summary->event_type = 'C';
        }

        //some elements require extra proccessing than just hovered or clicked
        //use a switch statement to orginize the code
        switch(eec->elements[i]->type){
            case 'D': //Draggable Element

                //Ok, first, we need to see if the element was interacted with.
                //If so, we need to set the dragging (misc) status to indicate that
                if (status == 2) eec->elements[i]->misc = 1;
                //else if misc already is 1, and lcs is not true (i.e. the player let go of the
                //element) then set the misc status back to 0
                else if (e->lcs == 0 && eec->elements[i]->misc){
                    eec->elements[i]->misc = 0;

                    //if there are any snap_to elements, calculate the overlap
                    if (eec->num_snaps){
                        //get the elements
                        float over_max = 0.;
                        int over_indx = 0;
                        for (int indx = 0; indx < eec->num_snaps; indx++){
                            float over = EE_Overlap_Helper(eec->elements[i], eec->snaps[indx]);
                            if (over > over_max){
                                over_max = over;
                                over_indx = indx;
                            }
                        }
                            
                            //choose the best non-zero overlap
                            if (over_max > 0.05){
                                //snap the elements together!
                                //center->center
                            eec->elements[i]->x = eec->snaps[over_indx]->x + (int)( 0.5 * (float) (eec->snaps[over_indx]->w - eec->elements[i]->w));
                            eec->elements[i]->y = eec->snaps[over_indx]->y + (int)( 0.5 * (float) (eec->snaps[over_indx]->h - eec->elements[i]->h));

                            //made a reference to this snap event
                            //event type(S)nap
                            summary->event_type = 'S';
                            summary->eid_one = eec->elements[i]->eid;
                            summary->eid_two = eec->snaps[over_indx]->eid;

                        }
                    }
                } 
>>>>>>> clunky

                    //check to see if we overlap with a snap-to element


                }
                //if the misc status is set to true, then the element is being dragged
                //thus we need to update its x/y location
                if (eec->elements[i]->misc){
                    //update the x, y coords of the element
                    eec->elements[i]->x = e->mx - e->dx;
                    eec->elements[i]->y = e->my - e->dy;
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

struct Clunky_Event_Element *clunky_standard_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name){
    //create a standard clunky button!
    //this function remove the need to pass in as many arguments to the init call

    //first we need to allocate the memory
    struct Clunky_Event_Element *ele = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

    //init the button
    clunky_element_init(ele, s, x, y, row, e_name, 'B', 'H');

    return ele;
}


struct Clunky_Event_Element *clunky_toggle_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name){
    //create a standard clunky button!
    //this function remove the need to pass in as many arguments to the init call
    
    //first we need to allocate the memory
    struct Clunky_Event_Element *ele = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

    //init the button
    clunky_element_init(ele, s, x, y, row, e_name, 'B', 'T');

    return ele;
}


struct Clunky_Event_Element *clunky_dragable_element_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name){
    //create a standard clunky button!
    //this function remove the need to pass in as many arguments to the init call
    
    //first we need to allocate the memory
    struct Clunky_Event_Element *ele = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

    //init the button
    clunky_element_init(ele, s, x, y, row, e_name, 'D', 'N');

    return ele;
}
