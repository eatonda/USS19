#include "gameOver.hpp"

const int WINDOW_WIDTH = 1350;
const int WINDOW_HEIGHT = 700;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 50;

int main() {
    // initialize window to render game to
    struct Clunky_Window window;
    struct Clunky_Event event;
    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    int rounds = 12;
    int size = 10;
    int isWinner = 1;
    
    gameOver(&window, &event, boardSize, rounds, isWinner);
}
