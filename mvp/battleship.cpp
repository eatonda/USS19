// Main File for the game

#include "../menu_functions/getGameParameters.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

#include "gameCore.hpp"
#include "bsCore.h"

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


	bool gameRunning = false;
   
	if (getGameParameters(&window, &event, &boardSize, &numOfShips, &colorScheme)) {
		gameRunning = true;
	}	
 
    while (gameRunning) {
        
        /* Trace Statement showing instantiated parameters */
        std::cout << " Parameters Instantiated via getGameParameters()\n";
        std::cout << "numOfShips: " << numOfShips << std::endl;
        std::cout << "Square boardSize: " << boardSize << std::endl;
        std::cout << "colorScheme 0(light) or 1(dark): " << colorScheme << std::endl;
        
        struct BSCore *bsc = (struct BSCore *) malloc (sizeof(struct BSCore));
        bsInit(boardSize, colorScheme, numOfShips, &event, bsc, &window);
        bsLayout(bsc); 

        int runVal = bsRun(bsc);

		// return to the start menu	
		// runVal of 0 indicates the game exited normally	
		// a runVal of 2 indicates the game has been exited from the pause menu
		if (runVal == 0 || runVal == 2) {
			if (!getGameParameters(&window, &event, &boardSize, &numOfShips, &colorScheme)) {
				gameRunning = false;
			}				
		}
		// runVal of 1 indicates the game has been restarted with the same setup (hence we don't need
		// to return to the start menu)
		else if (runVal != 1) {
			gameRunning = false;
		}

    }

    return 0;
}
    

