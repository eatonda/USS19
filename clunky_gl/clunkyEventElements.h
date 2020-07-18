#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYEVENTELEMENTS_H
#define CLUNKYEVENTELEMENTS_H

struct Clunky_Event_Summary{

    char *str;
    int str_len;
    int str_used;
    int collect_string;

    unsigned long eid;

};

//Idea: have a handler for all of the clunky specific event objects (buttons, etc)
//that are rendered to the screen and interacted with the mouse or keyboard
struct Clunky_Event_Element_Container{

    struct Clunky_Event_Element **elements;
    int len_ele;
    int num_ele;

    struct Clunky_Event_Summary sum;

};

struct Clunky_Event_Element{
    struct  Clunky_Sprite *s;


    char type; //what type of element we have: 
                //[B]utton
                //[T]extbox
                //[D]raggable
                //[S]nap-To

    char effect; //what type of cosmetic effect to add to the element's 
                //rendering
                //[T]oggle
                //[N]othing / regular
                //[A]nimate
                //[H]over
                //[R] -> Hover + Toggle

    unsigned long eid;
    int x;
    int y;
    int w;
    int h;

    int interact; // 0: No, 1: Hover, 2: Clicked
    int misc; //a misc variable to be used differently depending on the type
              //of element. EX: draging status

    int row;
    int col_max;
};

//clunky event elements
unsigned long clunky_element_init(struct Clunky_Event_Element *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type, char effect);

int clunky_element_render(struct Clunky_Event_Element *b, struct Clunky_Window *w);

//Make some helper functions to simplify the element creation proccess
struct Clunky_Event_Element *clunky_standard_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);
struct Clunky_Event_Element *clunky_toggle_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);
struct Clunky_Event_Element *clunky_dragable_element_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);

//clunky event element container
int clunky_eec_init(struct Clunky_Event_Element_Container *eec);
int clunky_eec_add_elements(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element **ele, int num_ele);
int clunky_eec_update(struct Clunky_Event_Element_Container *eec, struct Clunky_Event *e, struct Clunky_Window *w);
int clunky_eec_grow(struct Clunky_Event_Element_Container *eec);
int clunky_eec_free(struct Clunky_Event_Element_Container *eec);

#endif
