#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"

#include "board.hpp"

#ifndef GAMECORE_H
#define GAMECORE_H

class GameCore{
    private:
        struct Clunky_Window* window; // Reference to main's window

        struct Clunky_Event_Element_Container* eec;    // Pointer to container of button elements

        struct Clunky_Event *event;

        int board_size;
        int color_theme;
        int num_ships;
        float board_scale;

        class Board *b;

        int **player_board;
        int **ai_board;
    public:
        GameCore(int size, int color, int ships, struct Clunky_Event *event, struct Clunky_Window* window);
        int run();
        int init();
        int printShips();
};




#endif
