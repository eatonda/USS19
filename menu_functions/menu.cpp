//
//  menu.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/8/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "menu.hpp"


Menu::Menu(struct Clunky_Window* window, Clunky_Event_Element_Container* menuOptions, int numOfOptions, int* values, std::string* optionNames) {
    this->window = window;
    this->menuOptions = menuOptions;
    this->numOfOptions = numOfOptions;
    this->values = values;
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

/*  run
 Description: runs menu and updates the userInput parameter via reference.
 Parameters:struct Clunky_Event* event, int* userInput
 Preconditions: No parameters can be NULL
 Returns: -1 if SDL_QUIT is encountered, 0 if back is selected, 1 if a valid choice was selected
*/
int Menu::run(struct Clunky_Event* event, int* userInput) {
    int userChoice = -2;    //Stores user's selection

    while(true) {
        
        assert(event != NULL);  // Assert preconditions
        
        //NOTE: Before checking the event structure to see if
        //there are any events in it, you must fisrt call clunky_event to
        //check the system for events and populate the structure
        clunky_event(event);
        clunky_eec_update(menuOptions, event, window); //update event container
        // Sift through events if there are any.
        if (event->num_input) {
            
            // Check for SDL_QUIT
            if (_SDL_QUIT_Check(event) < 0) {
                return -1;  // Return -1 to signal exit from SDL_QUIT
            }
        }
        
        userChoice = _getMouseClick(menuOptions, numOfOptions, optionNames, event);
        
        if (values != NULL && userChoice < numOfOptions) {
            *userInput = values[userChoice];    //Update user input via reference
        }
        
        if (userChoice == numOfOptions) {
            return 0; // Back was selected, return 0
            
        }
        
        if (userChoice >= 0 && userChoice <= numOfOptions){
            return 1;    // return true for non back index selected
        } else {
            userChoice = -2;    // Reset variable
        }
        
         _display(event);
        
    }
}
        
            
        

