#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYADVEVENTS_H
#define CLUNKYADVEVENTS_H

struct Clunky_Event_Summary{

    char *str;
    int str_len;
    int str_used;
    int collect_string;

    unsigned long selected_ele;

};

//Idea: have a handler for all of the clunky specific event objects (buttons, etc)
//that are rendered to the screen and interacted with the mouse or keyboard
struct Clunky_Event_Element_Container{

    struct Clunky_Event_Element *elements;
    int num_ele;

    struct Clunky_Event_Summary sum;

};

struct Clunky_Event_Element{
    struct  Clunky_Sprite *s;


    char type; //what type of element we have: 
                //[b]utton
    char effect; //what type of cosmetic effect to add to the element's rendering
                //[T]oggle
                //[R]egular
                //[F]lash

    unsigned long eid;
    int x;
    int y;
    int w;
    int h;

    int clicked;

    int row;
    int col_max;
};

unsigned long clunky_element_init(struct Clunky_Event_Element *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type);

int clunky_element_render(struct Clunky_Event_Element *b, struct Clunky_Window *w);

unsigned long clunky_element_check(struct Clunky_Event_Element *b, int num, struct Clunky_Event *e);

#endif
