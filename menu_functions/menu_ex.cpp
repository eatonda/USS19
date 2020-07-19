#include <stdio.h>
#include <stdlib.h>
#include "menu.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>



const int WINDOW_WIDTH = 540;
const int WINDOW_HEIGHT = 480;
const int NUM_OF_SPRITE_COLS = 2;
const int MAIN_MENU_NUM_OF_BUTTONS = 4;
const int LOGIN_CONTINUE_NUM_OF_BUTTONS = 3;
const int BUTTON_WIDTH = 165;
const int BUTTON_HEIGHT = 160;

Menu* makeMainMenu(Clunky_Window* window);

int main(int argc, char *argv[]){
    /* Window for rendering to screen */
    struct Clunky_Window window;
    
    struct Clunky_Event event;
    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);    // Initialize window

                                        /* CREATE MAIN MENU */

    /* Parameters for main menu */
    std::string mainMenuDescriptions [MAIN_MENU_NUM_OF_BUTTONS] = {"start", "leaderboard", "user manual", "quit"};
    
    int x = getMiddle(BUTTON_WIDTH, WINDOW_WIDTH);  // Get x coordinate that centers the button
    int xCoordinates [MAIN_MENU_NUM_OF_BUTTONS] = {x,x,x,x};
    
    int yOffset = 80;    // button height offset from other buttons in main menu
    int y = 140;        //Starting button height
    int yCoordinates [MAIN_MENU_NUM_OF_BUTTONS];   // Stores y coordinates for buttons of the main menu
    for (int i = 0; i < MAIN_MENU_NUM_OF_BUTTONS; i++){
        yCoordinates[i] = y;
        y+= yOffset;
    }

    struct Clunky_Texture main_menu_texture;
    clunky_load_texture(toC_String("./mainMenuButtons.bmp"), &main_menu_texture, &window);  // Initialize texture for main menu
    
    struct Clunky_Sprite mmb;   //stores sprite image of main menu buttons
    clunky_init_sprite(MAIN_MENU_NUM_OF_BUTTONS, NUM_OF_SPRITE_COLS, &main_menu_texture, &mmb); // Initialize sprite

    struct Clunky_Button *main_menu = buttonSetup(MAIN_MENU_NUM_OF_BUTTONS, mainMenuDescriptions, &mmb, xCoordinates, yCoordinates);  // store buttons as an array of Clunky_Button
    
    /* Initialize a Menu object for the mainMenu*/
    Menu* mainMenu =  new Menu(&window, main_menu, MAIN_MENU_NUM_OF_BUTTONS, mainMenuDescriptions);
    

    
    
    
    
                    
    //now we can begin our main loop!
    int cont = 1;
    int main_userInput = -5;
  
    
    while(cont){
        main_userInput = mainMenu->run(&event);
        
        switch (main_userInput) {
            case -1:
                std::cout << "In main, x window selected\n";
                cont = 0;
                break;
                
            case 0:
                std::cout << "In main, selection was start\n";
                break;
                
            case 1:
                std::cout << "In main, selection was leaderboard\n";
                break;
                
            case 2:
                std::cout << "In main, selection was user manual\n";
                break;
                
            case 3:
                std::cout << "In main, selection was exit\n";
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

        
            
