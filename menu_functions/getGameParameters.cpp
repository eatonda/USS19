/*  getGameParameters
 Description: Runs menus required to initialize game parameters in main via reference
 Parameters: struct Clunky_Window* window,  struct Clunky_Event* event, struct Clunky_Window* window, int* dimensions, int* numOfShips, int* colorTheme
 Returns: Updates all parameters except window via reference based on user selection
 
 Preconditions: No parameter can be NULL and the window parameter must be properly intitiated
 */

#include "getGameParameters.hpp"

int getGameParameters(struct Clunky_Window* window,  struct Clunky_Event* event, int* dimensions, int* numOfShips, int* colorTheme) {


const int NUM_OF_SPRITE_COLS = 2;
const int MAIN_MENU_NUM_OF_BUTTONS = 4;
const int LOGIN_CONTINUE_NUM_OF_BUTTONS = 3;
const int BUTTON_WIDTH = 165;
const int BUTTON_HEIGHT = 160;



    
                            /* CREATE MAIN MENU */

    /* Parameters for main menu */
    std::string mainMenuDescriptions [MAIN_MENU_NUM_OF_BUTTONS] = {"start", "leaderboard", "user manual", "quit"};
    
    int x = getMiddle(BUTTON_WIDTH, window->width);  // Get x coordinate that centers the button
    
    int xCoordinates [MAIN_MENU_NUM_OF_BUTTONS] = {x,x,x,x};
    
    int yOffset = window->height * 0.15;    // button height offset from other buttons in main menu, relative to window height
    
    int y = window->height * 0.20;        //Starting button height, relative positioning
    
    int yCoordinates [MAIN_MENU_NUM_OF_BUTTONS];   // Stores y coordinates for buttons of the main menu
    for (int i = 0; i < MAIN_MENU_NUM_OF_BUTTONS; i++){
        yCoordinates[i] = y;
        y+= yOffset;
    }

    struct Clunky_Texture main_menu_texture;
    clunky_load_texture(toC_String("./mainMenuButtons.bmp"), &main_menu_texture, window);  // Initialize texture for main menu
    
    struct Clunky_Sprite mmb;   //stores sprite image of main menu buttons
    clunky_init_sprite(MAIN_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &main_menu_texture, &mmb); // Initialize sprite

    struct Clunky_Event_Element_Container* main_menu = buttonSetup(MAIN_MENU_NUM_OF_BUTTONS, mainMenuDescriptions, &mmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    /* Initialize a Menu object for the mainMenu*/
    Menu* mainMenu =  new Menu(window, main_menu, MAIN_MENU_NUM_OF_BUTTONS, mainMenuDescriptions);
    
                    
    // Menus main loop
    int cont = 1;
    
    // Variables holding user input per menu, different ones used for readabiality sake.
    int main_userInput = -5;
  
    
    while(cont){
        main_userInput = mainMenu->run(event);
        std::cout << "In getGameParameters:\n"; // Trace statement
        switch (main_userInput) {
            case -1:
                std::cout << "x icon selected\n";
                cont = 0;
                break;
                
            case 0:
                std::cout << "selection was start\n";
                break;
                
            case 1:
                std::cout << "selection was leaderboard\n";
                break;
                
            case 2:
                std::cout << "selection was user manual\n";
                break;
                
            case 3:
                std::cout << "selection was exit\n";
        cont = 0;
                break;
            default:
                break;
        }
        
    }

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        
            
