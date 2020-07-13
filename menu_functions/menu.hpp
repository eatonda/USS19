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

//extern "C" {
    #include "../clunky_gl/clunkyCore.h"
    #include "../clunky_gl/clunkyHash.h"
    #include "../clunky_gl/clunkyAdvEvents.h"
//}

class Menu {
    
private:
    struct Clunky_Window* window; // Reference to main's window
    
    struct Clunky_Button* menuOptions;    // Pointer to an array of Clunky_Buttons
    
    int numOfOptions;
    
    std::string* optionNames;   // Pointer to an array of option names for comparision purposes.
    
    
public:
    Menu(struct Clunky_Window* window, struct Clunky_Button* menuOptions, int numOfOptions, std::string* optionNames);
    
    struct Clunky_Button* getMenuOptions(); // Returns menuOptions member variable
    
    int getNumOfOptions();  // Returns the numOfOptions member
    
    std::string* getOptionNames();   // Returns the array of option names
    
    void display();    // Renders buttons to the screen
    
    int run(struct Clunky_Event* event);    // Runs menu and returns user input
};

#endif /* menu_hpp */
