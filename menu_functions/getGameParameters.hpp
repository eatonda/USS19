#ifndef getGameParameters_hpp
#define getGameParameters_hpp

#include <stdio.h>
#include <stdlib.h>
#include "menu.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>

int getGameParameters( struct Clunky_Window* window, struct Clunky_Event* event, int* dimensions, int* numOfShips, int* colorTheme); //Runs menus required to initialize game parameters in main via reference

Menu* _getMainMenu();

Menu* _getColorThemeMenu();

Menu* _getNumberOfShipsMenu();

Menu* _getBoardDimensionsMenu();

Menu* _getUserManual();

Menu* _getLeaderBoard();







#endif



