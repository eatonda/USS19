#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYADVEVENTS_H
#define CLUNKYADVEVENTS_H

struct Clunky_Button{
    struct  Clunky_Sprite *s;


    char type; //what type of button we have: (t)oggle or (r)eg

    unsigned long bid;
    int x;
    int y;
    int w;
    int h;

    int clicked;

    int row;
};
unsigned long clunky_button_init(struct Clunky_Button *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type);

int clunky_button_render(struct Clunky_Button *b, struct Clunky_Window *w);

unsigned long clunky_button_check(struct Clunky_Button *b, int num, struct Clunky_Event *e);

#endif
