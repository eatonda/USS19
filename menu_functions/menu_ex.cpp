#include <stdio.h>
#include <stdlib.h>
#include "menu.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>



int windowWidth = 540;
int windowHeight = 480;

int main(int argc, char *argv[]){

    std::string menu1_desc [4] = {"start", "leaderboard", "help", "quit"};

    int x = windowWidth/3;	// For testing, all buttons are going to placed starting at the 1/3 of the window 
    int y = 140;	// Starting button height	
    int xCoordinates [4] = {x,x,x,x};
    int yCoordinates [4] = {y, y+80, y+160, y+240};	   		    

    //create a clunky window object.
    //this will be the window that we will render to
    struct Clunky_Window window;

    //now we will init the window, this will set the width and height of the
    //window, as well as call the nessisary SDL2 function calls for us
    //this has to be done first, as it inits SDL2 functions
    clunky_init(&window, windowWidth, windowHeight);

    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture main_menu_texture;
    clunky_load_texture(toC_String("./mainMenuButtons.bmp"), &main_menu_texture, &window);

    //From the trexture we can create a sprite. 
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite mmb;
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(4, 2, &main_menu_texture, &mmb);

    //now we get into buttons
    //the menu will have 4 buttons: start, options, credits, quit
    //we will store all the buttons for this menu in one dynamic array
    struct Clunky_Button *mainmenu = buttonSetup(4, menu1_desc, &mmb, xCoordinates, yCoordinates);
   

    //finally we need to create our event handler!
    struct Clunky_Event event;

    Menu* mainMenu1 = new Menu(&window, mainmenu, 4, menu1_desc);
                              
 
    //now we can begin our main loop!
    int cont = 1;
    int userInput = -5;
    
    while(cont){
        userInput = mainMenu1->run(&event);
        
        switch (userInput) {
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
                std::cout << "In main, selection was help\n";
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

        

            
