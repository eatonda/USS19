//
//  menu.cpp
//  BattleShip_Playground
//
//  Created by David Eaton on 7/8/20.
//  Copyright © 2020 David Eaton. All rights reserved.
//

#include "menu.hpp"

/*  Menu
 Description: Typical menu constructor with no additional text content.
 Parameters: struct Clunky_Window* window, Clunky_Event_Element_Container* menuOptions, int numOfOptions, int* values, std::string* optionNames, Clunky_Text* title
 */
Menu::Menu(struct Clunky_Window* window, struct Clunky_Event_Element_Container* menuOptions, int numOfOptions, int* values, std::string* optionNames, struct Clunky_Text* title) {
    this->window = window;
    this->menuOptions = menuOptions;
    this->numOfOptions = numOfOptions;
    this->values = values;
    this->optionNames = optionNames;
    this->title = title;
}

/* Menu
 Description: Menu constructor when utilizing a menu as a page with additional text content
 Parameters:
 */
Menu::Menu(struct Clunky_Window* window, Clunky_Event_Element_Container* menuOptions, int numOfOptions, std::string* optionNames, struct Clunky_Text* title, struct Clunky_Text** content, int numberOfPages, int linesPerPage) {
    this->window = window;
    this->menuOptions = menuOptions;
    this->numOfOptions = numOfOptions;
    this->optionNames = optionNames;
    this->title = title;
    this->content = content;
    this->numberOfPages = numberOfPages;
    this->linesPerPage = linesPerPage;
    this->pageNumber = 0;
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
    clunky_render_text(title, window);
    //clunky_update_renderer(window);

    //Now we just need a small delay to prevent the loop from consuming
    //too many resources
    //SDL_Delay(10);
    
}

/*  _displayPage
 Description: Page version of menu display
 Parameters:
 Preconditons: event != NULL and pageNum >= 0 pageNum < numberOfPages
 */
void Menu::_displayPage(struct Clunky_Event* event, int pageNum){
    // Assert preconditions
    assert(event != NULL);
    assert(pageNum >= 0 && pageNum < numberOfPages);
    
    //Update and present the window
    clunky_present_window(window);
    clunky_render_text(title, window);
    
//    for (int i = 0; i < linesPerPage; i++) {
//        clunky_render_text(&(content[pageNumber][i]), window);    // Render page to screen
//    }
    //std::cout << "displayPage() pageNumber = " << pageNumber << std::endl;
    if (pageNumber > 0) {
        for (int i = linesPerPage * pageNumber; i < linesPerPage * (pageNumber + 1); i++){
            clunky_render_text(content[i], window);
        }
    } else if (pageNumber == 0){
        for (int i = 0; i < linesPerPage; i++){
            clunky_render_text(content[i], window);
        }    }
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
        if (menuOptions->sum->type != 'N') {
            
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
        
            

/*  runPage
 Description: Pager menu version of run. Like previous run function but doesn't need to update a userinput variable. It simply returns when back to main menu is selected, and returns 0 if so.
 Parameters: struct Clunky_Event* event
 Preconditions: event cannot be NULL and member variables cannot be null. Also number of pages >= 0, linesPerPage must be greater than 0.
 Returns: -1 if SDL_QUIT is encountered, 0 if 'BACK TO MAIN' is selected
*/
int Menu::runPage(struct Clunky_Event* event) {
    // asset preconditions
    assert(content != NULL);
    assert(event != NULL);
    assert(numberOfPages >= 0 && linesPerPage > 0);

    int userChoice = -2;    //Stores user's selection

    while(true) {
        //NOTE: Before checking the event structure to see if
        //there are any events in it, you must fisrt call clunky_event to
        //check the system for events and populate the structure
        clunky_event(event);
        clunky_eec_update(menuOptions, event, window); //update event container
        // Sift through events if there are any.
        if (menuOptions->sum->type != 'N') {

            // Check for SDL_QUIT
            if (_SDL_QUIT_Check(event) < 0) {
                return -1;  // Return -1 to signal exit from SDL_QUIT
            }
        }

        userChoice = _getMouseClick(menuOptions, numOfOptions, optionNames, event);

        if (userChoice == numOfOptions) {
            return 0; // MAIN MENU  was selected, return 0

        } else if (userChoice == -1) {
            // Previous page was selected.
            if (pageNumber - 1 >= 0) {
                pageNumber--;   //If not first page decrement index
            }
        } else if (userChoice == numOfOptions + 1) {
            // Next page was selected
            if (pageNumber + 1 < numberOfPages) {
                pageNumber++;   // If not last page increment page number
            }
        }

         _displayPage(event, pageNumber);   // Call pager version of _display

    }
}

