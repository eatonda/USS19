//
//  menu.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/8/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "menu.hpp"


Menu::Menu(struct Clunky_Window* window, struct Clunky_Button* menuOptions, int numOfOptions, std::string* optionNames) {
    this->window = window;
    this->menuOptions = menuOptions;
    this->numOfOptions = numOfOptions;
    this->optionNames = optionNames;
}




struct Clunky_Button* Menu::getMenuOptions() {
    return menuOptions;
}

int Menu::getNumOfOptions() {
    return numOfOptions;
}


std::string* Menu::getOptionNames() {
    return optionNames;
}

void Menu::display() {
    for (int i = 0; i < numOfOptions; i++) {
         clunky_button_render(&(menuOptions[i]), window);   // Render buttons
    }
    
    //Update and present the window
    clunky_present_window(window);
    clunky_update_renderer(window);

    //Now we just need a small delay to prevent the loop from consuming
    //too many resources
    SDL_Delay(10);

    
}

int Menu::run(struct Clunky_Event* event) {
    int userChoice = -2;    //Stores user's selection

    while(true) {
        
        assert(event != NULL);  // Assert preconditions
        
        //NOTE: David, before checking the event structure to see if
        //there are any events in it, you must fisrt call clunky_event to
        //check the system for events and populate the structure
        clunky_event(event);

        // Sift through events if there are any.
        if (_isEvent(event)) {
            
            // Check for SDL_QUIT
            if (_SDL_QUIT_Check(event) < 0) {
                return -1;  // Return -1 to signal exit from SDL_QUIT
            }
        }
            userChoice = _getMouseClick(menuOptions, numOfOptions, optionNames, event);
            
            if (userChoice >= 0 && userChoice < numOfOptions) {
                
                
                // If valid choice return user's choice
                return userChoice;
            } else {
                userChoice = -2;    // Reset variable
            }
        
         display();
        
    }
}
        
            
        

