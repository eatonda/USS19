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


/*  _getMouseClick
 Description: Returns the menu option clicked on.
 Parameters: struct Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames, Clunky_Event* event
 Preconditons: An option was clicked and no parameters can be NULL
 Returns: int option clicked in array indexing
 */

int _getMouseClick(struct Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames, Clunky_Event* event) {
    assert(event != NULL && optionNames != NULL && menuOptions != NULL);  // Assert preconditions
    
    int optionNumber = -1; //Corresponds with option number selected. Array indexing thus first option is 0.
    
    for (int i = 0; i < numOfOptions; i++) {
        if (menuOptions->sum.eid_one == clunky_hash_gen(toC_String(optionNames[i]))) {
            // Check for back option
            if (optionNames[i] == "BACK" || optionNames[i] == "MAIN MENU") {
                return numOfOptions;    // To signal back was selected
            } else if (optionNames[i] == "PREVIOUS") {
                return -1;  // Special Case for previous page
            } else if (optionNames[i] == "NEXT") {
                return numOfOptions + 1;    // Special case for next page
            } else
                // If other menu option was selected return index
                return i;
        }
    }
}
    



/*	buttonSetup
Description: Creates an array of struct Clunky_Button assigning all parameters based on arguments recieved.
Parameters: int numOfButtons, std::string* arrOfDesc, struct Clunky_Sprite* sprite, int* xCoordinates, int* yCoordinates
Returns: Dynamically allocated array of Clunky_Button
Preconditions: No pointers arguments can be NULL, numOfButtons > 0, both arrays(xCoordinates and yCoordinates) must have a length equivalent to numOfButtons.
*/ 
struct Clunky_Event_Element_Container* buttonSetup(int numOfButtons, std::string* arrOfDesc, struct Clunky_Sprite* sprite, int* xCoordinates, int* yCoordinates) {
    /* Assert preconditions have been met */
    assert(arrOfDesc != NULL && sprite != NULL && xCoordinates != NULL && yCoordinates != NULL);
    assert(numOfButtons > 0);
    
    /* Create an array of Clunky_Event_Elements that will make up the menu */
    struct Clunky_Event_Element** menu = (struct Clunky_Event_Element**)malloc(sizeof(struct Clunky_Event_Element*) * numOfButtons);
    
    assert(menu != NULL);
    
    /* Initialize buttons with corresponding descriptions and locations */
    for (int i = 0; i < numOfButtons; i++) {
        menu[i] = clunky_standard_button_init(sprite, xCoordinates[i], yCoordinates[i] , i, toC_String(arrOfDesc[i]));
    }
    
    /* Transfer buttons to Event Element Container (EEC) */
    struct Clunky_Event_Element_Container* eec = (struct Clunky_Event_Element_Container*)malloc(sizeof(struct Clunky_Event_Element_Container));
    
    assert(eec != NULL);
    
    clunky_eec_init(eec);   //init eec
    
    // Add button elements to container
    clunky_eec_add_elements(eec, menu, numOfButtons);
    
    return eec;
    
}
