#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

#ifndef SHIP_H
#define SHIP_H

struct Ship_Assets{

    struct Clunky_Sprite *sprite;
    struct Clunky_Texture *texture;


};

int init_ship(struct Ship_Assets *s, struct Clunky_Window *w);

struct Clunky_Event_Element **generate_ship(int length, int color, struct Clunky_Event_Element_Container *eec, struct Ship_Assets s);

#endif