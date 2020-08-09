#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
    //we should probs put the eec in here?
    struct Clunky_Event_Element_Container* eec;
    struct Clunky_Event_Element *ele;
    int num_ele;
    int len_ele;
    int grow_ele();

    int rotation;

    public:
        Board(int size, int color, int ships);
        int run();
        int init();
};




#endif
