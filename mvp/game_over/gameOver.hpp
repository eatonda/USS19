
#ifndef gameOver_hpp
#define getOver_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cassert>

#include "../menu_functions/menu.hpp"
#include "/data_functions/getHighScores.hpp"
#include "/data_functions/writeScores.hpp"
#include "/data_functions/enterScore.hpp"


void gameOver( struct Clunky_Window* window, struct Clunky_Event* event, int dimensions, int numOfRounds, int winnerFlag); //Runs game over protocols, such as displaying game over and saving high score.



#endif



