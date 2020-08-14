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

    //set the default z value to 0
    b->z = 0;
    b->z_init = 0;

    //copy over the sprite address
    b->s = s;

    //get the width and height of the buttons hit box from the sprite
    b->w = b->s->cell.w;
    b->h = b->s->cell.h;

    //set the clicked status to false
    b->interact = 0;

    //set ignore to 0
    b->ignore = 0;

    //set the row number
    b->row = row;

    //defgault GID
    b->gid = -1;

    //get the max column count
    b->col_max = s->texture->width  / s->cell.w;

    //generate the BID
    b->eid = clunky_hash_gen(b_name);

    //set the UID to -1, since this element is not in a eec
    b->uid = -1;

    //copy over the name
    for (i = 0; i < 256; i++)  b->name[i] = '\0';
    for (i = 0; b_name[i] != '\0'; i++){
        b->name[i] = b_name[i];
    }

    //set the misc flag to 0
    b->misc = 0;

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
    if (b->interact == 1 && b->effect != 'R' && b->effect != 'H' && b->effect != 'T'){
        //render the unclicked version
        clunky_render_sprite(b->x, b->y, b->row, 0, b->s, w);
    }
    else if (b->effect == 'T'){
        //render the toggle
        if(b->interact == 2){
            if (b->misc){
                b->misc = 0;
            }
            else{
                b->misc = 1;
            }
        }
        clunky_render_sprite(b->x, b->y, b->row, b->misc, b->s, w);
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

    //set the UID master counter to 0
    eec->uid_mstr = 0;
   
    //we want to capture text
    eec->sum.collect_string = 0;
    eec->sum.str = (char *) malloc(sizeof(char) * 32);
    eec->sum.str_used = 0;
    eec->sum.str_len = 32;



    //init the memory for the event elements
    eec->elements = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_ele);
    eec->snaps = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * eec->len_snaps);

    //init the groups
    for (int i = 0; i < 16; i++){
        eec->groups[i].calling_uid = -1;
    }

    eec->num_groups = 0;

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

int insertion_helper(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element *ele){
    //first, if there are NO elements in the array, just put it at the head
    if (!eec->num_ele){
        //add the element to the head position
        eec->num_ele++;
        eec->elements[0] = ele;
        return 0;
    }

    //if the number of elements currently in the array + 1 (the new element) >= length
    //of the array, grow it before continuing
    if ( (eec->num_ele + 1) >= eec->len_ele ) clunky_eec_grow(eec);

    //now we start at the tail position and bubble the element towards the head
    //this is a min array of if the element ahead of the new element has a larger z
    //value swap
    //And yes, I know this is NOT an efficient way to do it. a binary search would be better
    //but I'm in a time crunch
    for (int i = eec->num_ele; i > 0; i--){
        //the the element ahead of this one is greater, shift it down
        if ( eec->elements[i-1]->z > ele->z ){
            //shift the element back by one
            eec->elements[i] = eec->elements[i-1];
        }
        else{
            //we found a spot to put the new element
            eec->elements[i] = ele;
            //make note that we added another element
            eec->num_ele++;
            return i;
        }
    }

    //if we make it here, we need to put the new element at the head
    eec->elements[0] = ele;
    //make note that we're adding another element
    eec->num_ele++;

    return 0;
}


int clunky_eec_add_elements(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element **ele, int num_ele){
    int i;

    //now copy over the memory addresses!
    for (i = 0; i < num_ele; i++){
        //insert the current element into the appropreit spot
        //set the UID for the ele
        ele[i]->uid = eec->uid_mstr++;
        insertion_helper(eec, ele[i]);

        //if it is a snap-to element, add it to the spacial map
        if (ele[i]->type == 'S'){
            eec->snaps[eec->num_snaps++] = ele[i];
            if ( eec->num_snaps  >= eec->len_snaps ) clunky_eec_grow(eec);
        }
    }

    printf("--%d\n", eec->num_ele);


    return 0;
}

int clunky_mouse_interaction_helper(struct Clunky_Event_Element * ele, struct Clunky_Event *e){
    //local helper function to set the itneract status of elements
    if ( e->mx >= ele->x && e->mx <= (ele->x + ele->s->ap_w) &&
             e->my >= ele->y && e->my <= (ele->y + ele->s->ap_h)){
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
    if ( a->x <= b->x && (a->x + a->s->ap_w) >= b->x){
        //element B overlaps A on the X axis!
        w_over = (a->x + a->s->ap_w) - b->x;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( w_over > b->s->ap_w ) w_over = b->s->ap_w;
    }
    else if ( b->x <= a->x && (b->x + b->s->ap_w) >= a->x){
        //element A overlaps B on the X axis!
        w_over = (b->x + b->s->ap_w) - a->x;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( w_over > a->s->ap_w ) w_over = a->s->ap_w;
    }
    else{
        //there is no overlap!
        return overlap;
    }

    //now check the Y axis overlap
    if ( a->y <= b->y && (a->y + a->s->ap_h) >= b->y ){
        //element B overlaps A on the Y axis!
        h_over = (a->y + a->s->ap_h) - b->y;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( h_over > b->s->ap_h ) h_over = b->s->ap_h;
    }
    else if ( b->y <= a->y && (b->y + b->s->ap_h) >= a->y ){
        //element A overlaps B on the Y axis!
        h_over = (b->y + b->s->ap_h) - a->y;

        //make sure that the overlap lengths arent larger than the sides of b
        if ( h_over > a->s->ap_h ) h_over = a->s->ap_h;
    }
    else{
        //there is no overlap!
        return overlap;
    }

    //we need to know the smallist area
    int area = 0;
    if (a->s->ap_w * a->s->ap_h < b->s->ap_w * b->s->ap_h) area = a->s->ap_w * a->s->ap_h;
    else area = b->s->ap_w * b->s->ap_h;

    //return the percent overlap
   // printf("%d, %d\n", (w_over * h_over), area);
    
    return (float) (w_over * h_over) / (float) area;

}

int draggable_ee_handler(int i, int status, struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Summary *summary,struct Clunky_Event *e){
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
                            eec->elements[i]->x = eec->snaps[over_indx]->x + (int)( 0.5 * (float) (eec->snaps[over_indx]->s->ap_w - eec->elements[i]->s->ap_w));
                            eec->elements[i]->y = eec->snaps[over_indx]->y + (int)( 0.5 * (float) (eec->snaps[over_indx]->s->ap_h - eec->elements[i]->s->ap_h));

                            //made a reference to this snap event
                            //event type(S)nap
                            summary->event_type = 'S';
                            summary->eid_one = eec->elements[i]->eid;
                            summary->eid_two = eec->snaps[over_indx]->eid;
                            summary->uid_one = eec->elements[i]->uid;
                            summary->uid_two = eec->snaps[over_indx]->uid;

                            eec_update_group(eec->elements[i], eec);

                        }
                    }
                }

                //if the misc status is set to true, then the element is being dragged
                //thus we need to update its x/y location
                if (eec->elements[i]->misc){
                    //update the x, y coords of the element
                    eec->elements[i]->x = e->mx - e->dx;
                    eec->elements[i]->y = e->my - e->dy;

                    eec_update_group(eec->elements[i], eec);
                }

    return 0;
}





int clunky_eec_update(struct Clunky_Event_Element_Container *eec, struct Clunky_Event *e, struct Clunky_Window *w){
    int i, status, clicked = 0;
    //first, for legibility, I'm going to create a pointer reference towards the eec's summary element
    //this is just to try to make the code have fewer de-references
    //because theres going to be a lot going on in this function
    struct Clunky_Event_Summary *summary = &(eec->sum);
    //clear the previous eid in case there isnt a new one this itteration
    summary->event_type = 'N';

    //get any text
    clunky_capture_text(&(eec->sum), e);

    //we need to now loop through every element in the eec
    for (i = eec->num_ele-1; i >= 0; i--){
        //check to see if we are ignoring to update this element
        if (eec->elements[i]->ignore) continue;

        //check to see if the element is being interacted with
        if (eec->elements[i]->type != 'S' && !clicked){
            status = clunky_mouse_interaction_helper(eec->elements[i], e);

            if (status == 2){
                clicked = 1;
                //if its a draggable element, change its z
                if (eec->elements[i]->type == 'D'){
                    printf("MOVING TO TOP\n");
                    eec->elements[i]->z = 100;
                }
            }
        }
        else{
            status = 0;
            eec->elements[i]->z = eec->elements[i]->z_init;
        }

        //if the element was clicked, status == 2, make note of the eid for the summary
        if (status == 2){
            //set the EID_One to the eid of the clicked element, and the type to 'C'
            summary->eid_one = eec->elements[i]->eid;
            summary->uid_one = eec->elements[i]->uid;
            summary->event_type = 'C';
            printf("<<%d, %d>>\ %s\n", eec->elements[i]->x, eec->elements[i]->y,  eec->elements[i]->name);
        }

        //some elements require extra proccessing than just hovered or clicked
        //use a switch statement to orginize the code
        switch(eec->elements[i]->type){
            case 'D': //Draggable Element

                draggable_ee_handler(i, status, eec, summary,e);

                break;
            case 'T':
                //if clicked, toggle the sprite
                if (status == 2){
                    if (eec->elements[i]->misc) eec->elements[i]->misc = 0;
                    else eec->elements[i]->misc = 1;
                }
                break;
            default:
                break;
        }

    }
    clunky_eec_mergesort(eec);
    for (i = 0; i < eec->num_ele; i++){
        //now render the element to the window
        group_element_update(eec->elements[i], eec);
        clunky_element_render(eec->elements[i], w);
    }

    //set the calling UID's to -1
    for (int j = 0; j < eec->num_groups; j++) eec->groups[j].calling_uid = -1;
    
//    clunky_eec_mergesort(eec);

    return 0;
}

int clunky_eec_remove(int indx, struct Clunky_Event_Element_Container *eec){
    //remove an element for the array, freeing its memory app.
    //at the same time, shift all of the elements to the right of it, left by one

    //first free the mem. safely
    free(eec->elements[indx]);

    //now shift
    for (int i = indx; i < (eec->num_ele - 1); i++){
        eec->elements[indx] = eec->elements[indx + 1];
    }

    //decriment element cntr
    eec->num_ele--;

    return 0;
}


int merge(struct Clunky_Event_Element **arr, int l, int m, int r){
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    /* create temp arrays */
    struct Clunky_Event_Element *L[n1], *R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (L[i]->z <= R[j]->z) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 


    return 0;

}

int helper_eec_mergesort(struct Clunky_Event_Element **arr, int l, int r){

    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l + (r - l) / 2; 
  
        // Sort first and second halves 
        helper_eec_mergesort(arr, l, m); 
        helper_eec_mergesort(arr, m + 1, r); 
  
        merge(arr, l, m, r); 
    } 

    return 0;

}

int clunky_eec_mergesort(struct Clunky_Event_Element_Container *eec){
    //sort the elements array
    helper_eec_mergesort(eec->elements, 0, eec->num_ele-1);

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

int helper_eec_text_grow(struct Clunky_Event_Summary *sum){
    //create a temporary hold array
    char *hold = sum->str;

    //double the size of the array
    sum->str_len *= 2;

    //reallocate the mem
    sum->str = (char *)malloc(sizeof(char) * sum->str_len);

    //copy over the old data
    for (int i = 0; i < sum->str_used; i++) sum->str[i] = hold[i];

    //free the hold array
    printf("GROWING TEXT\n");
    free(hold);
    printf("TEXT IS BIG NOW\n");

    return 0;
}


int clunky_capture_text(struct Clunky_Event_Summary *sum, struct Clunky_Event *e){
    //first, make sure that we WANT to capture text
    if (!sum->collect_string) return 0;

    //check to see if there was a keydown event
    if (e->num_input){
        for ( int i = 0; i < e->num_input; i++){
            //check to see if we need to grow the array
            if (sum->str_used >= sum->str_len + 1) helper_eec_text_grow(sum);

            //check to see if its a valid character A-Z, ' ', 0-9
            if (e->input[i] >= 48 && e->input[i] <= 57){
                //Number inpit
                sum->str[sum->str_used++] = e->input[i];
            }
            else if (e->input[i] >= 65 && e->input[i] <= 90){
                //A-Z
                sum->str[sum->str_used++] = e->input[i];
            }
            else if (e->input[i] == ' '){
                //space
                sum->str[sum->str_used++] = e->input[i];
            }
        }
    }

    sum->str[sum->str_used] = '\0';


    return 0;
}

int clunky_clear_text(struct Clunky_Event_Summary *sum){
    //just set used to 0
    sum->str_used = 0;
    return 0;
}

int clunky_event_element_update_z(struct Clunky_Event_Element *ele, int z, struct Clunky_Event_Element_Container *eec){
    printf("--UPDATING Z\n");
    ele->z = z;
    ele->z_init = z;
    clunky_eec_mergesort(eec);
    return 0;
}

int clunky_indx_from_uid(int uid, struct Clunky_Event_Element_Container *eec){
    for (int i = 0; i < eec->num_ele; i++){
        if (eec->elements[i]->uid == uid) return i;
    }

    return -1;
}
    
int clunky_create_group(int x, int y, struct Clunky_Event_Element_Container *eec){
    //if there is currently no more spcace for groups 
    //since we're curently hard coding the limit
    //return -1
    if (eec->num_groups >= 16) return -1;

    eec->groups[eec->num_groups].gx = x;
    eec->groups[eec->num_groups].gy = y;

    //other wise return the next gid and incriment the coutner
    return eec->num_groups++;
}

int eec_addto_group(struct Clunky_Event_Element *ele, int gid, int x_off, int y_off, struct Clunky_Event_Element_Container *eec){
    printf("ADD TO GROUP START\n");
    //first, make sure the GID is valid
    if (gid < 0 || gid >= eec->num_groups) return -1;


    //change the elements gid
    ele->gid = gid;
    ele->gx_off = x_off;
    ele->gy_off = y_off;


    printf("ADD TO GROUP END %d\n", ele->uid);

    return 0;
}

int eec_update_group(struct Clunky_Event_Element *ele,struct Clunky_Event_Element_Container *eec){
    printf("EUG START GID: %d\n", ele->gid);
    //make sure the element is in a group
    if (ele->gid < 0) return -1;

    eec->groups[ele->gid].gx = ele->x - ele->gx_off; 
    eec->groups[ele->gid].gy = ele->y - ele->gy_off;
    eec->groups[ele->gid].calling_uid = ele->uid;

    printf("EUG END\n");

    return 1;
}

int group_element_update(struct Clunky_Event_Element *ele,struct Clunky_Event_Element_Container *eec){
//    printf("GEU START\n");
    //check to see if the element is in a group
    if (ele->gid < 0 || ele->gid > eec->num_groups) return -1;
    
    //check to see if there is a group movement update
    if (eec->groups[ele->gid].calling_uid < 0) return -1;

    //check to see if this element triggered the move
    if (eec->groups[ele->gid].calling_uid == ele->uid){
        //reset the calling uid
      //  eec->groups[gid].calling_uid = -1;
        return 0;
    }

    //ok, at this point we need to update x/y positions of the element!
    ele->x = eec->groups[ele->gid].gx + ele->gx_off;
    ele->y = eec->groups[ele->gid].gy + ele->gy_off;

  //  printf("GEU END\n");

    return 1;

}
