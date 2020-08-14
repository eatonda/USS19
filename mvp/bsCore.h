#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"
#include "ship.h"
#include "pause_menu/pauseMenu.hpp"

#ifndef BSCORE_H
#define BSCORE_H

struct BSCore{
    struct Clunky_Window* window; // Reference to main's window

    struct Clunky_Event_Element_Container* eec;    // Pointer to container of button elements
    struct Clunky_Event_Element_Container* selector;

    struct Clunky_Event *event;

    int board_size;
    int color_theme;
    int num_ships;
    float board_scale;

    int rotation;
    
    struct Clunky_Sprite *ship_spr;
    struct Clunky_Sprite *pin_spr;
    struct Clunky_Event_Element *fire;
    struct Clunky_Sprite *cell;
    struct Clunky_Sprite *cur;

    int **pins;
    int **ai_pins;
    int **player_board;
    int **ai_board;

    int ai_hits;
    int player_hits;
    int hits_to_win;

};

int bsInit(int size, int color, int ships, struct Clunky_Event *event,  struct BSCore *c, struct Clunky_Window* window);
int bsRun(struct BSCore *c);
int bsLayout(struct BSCore *c);


#endif
