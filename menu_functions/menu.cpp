//
//  menu.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/8/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "menu.hpp"


Menu::Menu(struct Clunky_Window* window, Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames) {
    this->window = window;
    this->menuOptions = menuOptions;
    this->numOfOptions = numOfOptions;
    this->optionNames = optionNames;
}


struct Clunky_Event_Element_Container* Menu::getMenuOptions() {
    return menuOptions;
}

int Menu::getNumOfOptions() {
    return numOfOptions;
}


std::string* Menu::getOptionNames() {
    return optionNames;
}

void Menu::_display(struct Clunky_Event* event) {
    //clunky_eec_update(menuOptions, event, window); //update event container
    
    //Update and present the window
    clunky_present_window(window);
    //clunky_update_renderer(window);

    //Now we just need a small delay to prevent the loop from consuming
    //too many resources
    //SDL_Delay(10);
    
}

int Menu::run(struct Clunky_Event* event) {
    int userChoice = -2;    //Stores user's selection

    while(true) {
        
        assert(event != NULL);  // Assert preconditions
        
        //NOTE: David, before checking the event structure to see if
        //there are any events in it, you must fisrt call clunky_event to
        //check the system for events and populate the structure
        clunky_event(event);
        clunky_eec_update(menuOptions, event, window); //update event container
        // Sift through events if there are any.
        if (menuOptions->sum.eid) {
            
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
        
         _display(event);
        
    }
}
        
            
        

