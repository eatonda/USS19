//
//  menu.hpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/8/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "menuHelpers.hpp"


#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"


class Menu {
    
private:
    struct Clunky_Window* window; // Reference to main's window
    
    struct Clunky_Event_Element_Container* menuOptions;    // Pointer to container of button elements
    
    int numOfOptions;
    
    std::string* optionNames;   // Pointer to an array of option names for comparision purposes.
    
    
public:
    Menu(struct Clunky_Window* window, Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames);
    
    struct Clunky_Event_Element_Container* getMenuOptions(); // Returns menuOptions member variable
    
    int getNumOfOptions();  // Returns the numOfOptions member
    
    std::string* getOptionNames();   // Returns the array of option names
    
    void _display(struct Clunky_Event* event);    // Renders buttons to the screen
    
    int run(struct Clunky_Event* event);    // Runs menu and returns user input
};

#endif /* menu_hpp */
