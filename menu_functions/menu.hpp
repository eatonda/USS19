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
    
    int* values;    // pointer to an array of button values
    
    std::string* optionNames;   // Pointer to an array of option names for comparision purposes.
    
    struct Clunky_Text* title; // Holds menu title
    
    struct Clunky_Text** content;   // Holds optional text content
    
    int numberOfPages = 0;  // Holds total number of pages
    int linesPerPage = 0; // Holds lines per page not including title
    int pageNumber = 0; // index for navigating through pages
    
    
public:
    Menu(struct Clunky_Window* window, struct Clunky_Event_Element_Container* menuOptions, int numOfOptions, int* values, std::string* optionNames, struct Clunky_Text* title);
    
    Menu(struct Clunky_Window* window, struct Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames, struct Clunky_Text* title, struct Clunky_Text** content, int numberOfPages, int linesPerPage);    // Constructor if there is content to intitialize
    
    struct Clunky_Event_Element_Container* getMenuOptions(); // Returns menuOptions member variable
    
    int getNumOfOptions();  // Returns the numOfOptions member
    
    std::string* getOptionNames();   // Returns the array of option names
    
    void _display(struct Clunky_Event* event);    // Renders buttons to the screen
    
    void _displayPage(struct Clunky_Event* event, int pageNum); // Renders page content as well as buttons
    
    int run(struct Clunky_Event* event, int* userInput);    // Runs menu and updates user input via reference, returns -1 if SDL_Quit is encountered, 0 if 'back' is encountered(note back has to be a optionName).
    
    int runPage(struct Clunky_Event* event); //Pager menu version of run. Like previous run function but doesn't need to update a userinput variable. It simply returns when back to main menu is selected, and returns 0 if so.
};

#endif /* menu_hpp */
