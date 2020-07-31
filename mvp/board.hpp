#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
        struct Clunky_Window* window; // Reference to main's window

        struct Clunky_Event_Element_Container* eec;    // Pointer to container of button elements

        struct Clunky_Event *event;

        int board_size;
        int color_theme;
        int num_ships;
        float board_scale;

        int **player_board;
        int **ai_board;
    public:
        Board(int size, int color, int ships, struct Clunky_Event *event, struct Clunky_Window* window);
        int run();
        int init();
};




#endif
