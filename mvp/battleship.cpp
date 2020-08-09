// Main File for the game

#include "../menu_functions/getGameParameters.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

#include "gameCore.hpp"

const int WINDOW_WIDTH = 1350;
const int WINDOW_HEIGHT = 700;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 50;

int main(int argc, char *argv[]) {
    // initialize window to render game to
    struct Clunky_Window window;
    struct Clunky_Event event;
    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    /* Game parameters needing to be intitialized */
    int numOfShips = -1;
    int boardSize = -1;     // Square board thus w = h
    int colorScheme = -1;   // Color scheme is either 0(light) or 1(dark)

    
    if (getGameParameters(&window, &event, &boardSize, &numOfShips, &colorScheme)) {
        
        /* Trace Statement showing instantiated parameters */
        std::cout << " Parameters Instantiated via getGameParameters()\n";
        std::cout << "numOfShips: " << numOfShips << std::endl;
        std::cout << "Square boardSize: " << boardSize << std::endl;
        std::cout << "colorScheme 0(light) or 1(dark): " << colorScheme << std::endl;
        
        GameCore *b = new GameCore(boardSize, colorScheme, numOfShips, &event, &window);
        printf("Made the board\n");
        b->init();
        printf("Board Init'd\n");
        b->printShips();
        b->run();

    }

    return 0;
}
    

