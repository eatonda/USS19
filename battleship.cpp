// Main File for the game

#include "getGameParameters.hpp"

const int WINDOW_WIDTH = 540;
const int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[]) {
    // initialize window to render game to
    struct Clunky_Window window;
    struct Clunky_Event event;
    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    /* Game parameters needing to be intitialized */
    int numOfShips = -1;
    int boardSize = -1;     // Square board thus w = h
    int colorScheme = -1;   // Color scheme is either 0(light) or 1(dark)
    
    if (getGameParameters(&window, &event, &numOfShips, &boardSize, &colorScheme)) {
        
        /* Trace Statement showing instantiated parameters */
        std::cout << " Parameters Instantiated via getGameParameters()\n";
        std::cout << "numOfShips: " << numOfShips << std::endl;
        std::cout << "Square boardSize: " << boardSize << std::endl;
        std::cout << "colorScheme 0(light) or 1(dark): " << colorScheme << std::endl;
        
        
        
        // Instantiate game objects
        
        // Run game loop
    }
    
}
