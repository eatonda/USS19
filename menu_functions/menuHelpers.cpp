//
//  menuHelpers.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/9/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "menuHelpers.hpp"

bool _isEvent(struct Clunky_Event* event) {
    assert(event != NULL);  // Assert precondition
    
    if (event->num_input != 0)
        return true;    // If there is an event return true
    else
        return false;
}

int _SDL_QUIT_Check(struct Clunky_Event* event) {
    assert(event != NULL);  // Assert precondition
    
    for (int i = 0; i < event->num_input; i++) {
            
        /*
         For debugging print any keypresses.
         All user input are represented by either a number or a capital letter.
         Lowercase letters are reserved for SDL events */
        printf(">>%c\n", event->input[i]);
            
        if (event->input[i] == 'q'){
            std::cout << "q event encountered\n";
            return -1;  // Quit SDL events will return a negative value to differentiate from choices
        }
    }
    return 1; // Return 1 to represent passing the check.
}


int _getMouseClick(struct Clunky_Button* menuOptions, int numOfOptions, std::string* optionNames, Clunky_Event* event) {
    assert(event != NULL && optionNames != NULL && menuOptions != NULL);  // Assert preconditions
    
    unsigned long bid;  //Button id
    
    // If there is a mouse click see if it selected a menu options
    if (event->lc || event->rc) {
        
        /*
         check to see if there is any button activity
         if a button has been clicked, its BID will be returned by the function
         we can get the BID using the buttons name by hashing it
         only one button can be clicked at a time, so we only need to
         check once per loop */
         bid = clunky_button_check(menuOptions, numOfOptions, event);

        if (bid) {
            for (int i = 0; i < numOfOptions; i++) {
                if (bid == clunky_hash_gen((toC_String(optionNames[i])))) {
                    printf("Clicked the %s Button\n", optionNames[i].c_str());   //For debugging
                    
                    return i;    //Return index to deal with choice
                }
            }
            
        }
    }
    return numOfOptions + 1;  // Signal a choice has not been made and to continue the loop
}


/*	buttonSetup
Description: Creates an array of struct Clunky_Button assigning all parameters based on arguments recieved.
Parameters: int numOfButtons, std::string* arrOfDesc, struct Clunky_Sprite* sprite, int* xCoordinates, int* yCoordinates
Returns: Dynamically allocated array of Clunky_Button
Preconditions: No pointers arguments can be NULL, numOfButtons > 0, both arrays(xCoordinates and yCoordinates) must have a length equivalent to numOfButtons.
*/ 
struct Clunky_Button* buttonSetup(int numOfButtons, std::string* arrOfDesc, struct Clunky_Sprite* sprite, int* xCoordinates, int* yCoordinates) {
    /* Assert preconditions have been met */
    assert(arrOfDesc != NULL && sprite != NULL && xCoordinates != NULL && yCoordinates != NULL);
    assert(numOfButtons > 0);
    
    /* Create an array of Clunky_Buttons that will make up the menu */
    struct Clunky_Button* menu = (struct Clunky_Button*)malloc(sizeof(struct Clunky_Button) * numOfButtons);
    assert(menu != NULL);
    
    /* Initialize buttons with corresponding descriptions and locations */
    for (int i = 0; i < numOfButtons; i++) {
        clunky_button_init(&(menu[i]), sprite, xCoordinates[i], yCoordinates[i] , i, toC_String(arrOfDesc[i]));	
    }
    
    return menu;
}
