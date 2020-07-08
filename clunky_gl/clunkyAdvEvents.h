#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYADVEVENTS_H
#define CLUNKYADVEVENTS_H

struct Clunky_Button{
    struct  Clunky_Sprite *s;

    unsigned long bid;
    int x;
    int y;
    int w;
    int h;
};
unsigned long clunky_button_init(struct Clunky_Button *b, struct Clunky_Sprite *s, int x, int y, const char *b_name);

unsigned long clunky_button_basic_init(struct Clunky_Button *b, struct Clunky_Sprite *s, int row, const char *b_name);

unsigned long clunky_button_check(struct Clunky_Button *b, int num, struct Clunky_Event *e);

#endif
