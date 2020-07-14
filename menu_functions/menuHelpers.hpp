//
//  menuHelpers.hpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/9/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#ifndef menuHelpers_hpp
#define menuHelpers_hpp

#include <stdio.h>
#include "menu.hpp"
#include "generalHelpers.hpp"

bool _isEvent(struct Clunky_Event* event); // Helper function to check if there are events to filter through

int _SDL_QUIT_Check(struct Clunky_Event* event); // Helper function to check for SDL_QUIT

int _getMouseClick(struct Clunky_Button* menuOptions, int numOfOptions, std::string* optionNames, Clunky_Event* event); // Helper function returns user's menu option selection.

struct Clunky_Button* buttonSetup(int numOfButtons, std::string* arrOfDesc, struct Clunky_Sprite* sprite, int x, int y);

    


#endif /* menuHelpers_hpp */


