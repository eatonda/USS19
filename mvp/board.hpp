#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
    struct Clunky_Window *w;
    struct Clunky_Event *e;

    //we should probs put the eec in here?
    struct Clunky_Event_Element_Container* eec;

    struct Clunky_Sprite *pin_spr;
    struct Clunky_Sprite *ship_spr;

    int **pins;
    int **ships;

    int hits_to_win;
    int hits;


    int size;
    int theme;

    int x;
    int y;

    int init(int **ships);

    public:
        Board(int x, int y, int size, int color, int **ships, struct Clunky_Window *w, struct Clunky_Event *e);
        int render();
        int move(int x, int y);
        int rotate(int dir);
};




#endif
