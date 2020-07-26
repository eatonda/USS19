#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "clunkyCore.h"
#include "clunkyHash.h"
#include "clunkyEventElements.h"

int main(int argc, char *argv[]){

    //dec common use variables
    int i, j, k;
    int cont;

    //create a clunky window object.
    //this will be the window that we will render to
    struct Clunky_Window window;

    //we need to create our event handler!
    struct Clunky_Event event;

    //now we will init the window, this will set the width and height of the
    //window, as well as call the nessisary SDL2 function calls for us
    //this has to be done first, as it inits SDL2 functions
    clunky_init(&window, &event, 640, 480);


    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    
    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    //create a clunky text object!
    struct Clunky_Text *text = clunky_get_text(130, 50, 512, 64, 1., &window);
    clunky_replace_text(text, "PLEASE ENTER YOUR NAME\0");
    for (int i = 0; i < text->str_used; i++){
        printf("%c, (%d, %d)\n", text->str[i], text->str_row[i], text->str_col[i]);
    }

    struct Clunky_Text *text2 = clunky_get_text(130, 125, 512, 64, 1., &window);
    clunky_replace_text(text2, "NAME:\0");
    for (int i = 0; i < text2->str_used; i++){
        printf("%c, (%d, %d)\n", text2->str[i], text2->str_row[i], text2->str_col[i]);
    }

    

    // string for name input
    std::string inputName = "TEXT";
    // Start accepting text input
    SDL_StartTextInput();

    SDL_Event e;
   
    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        clunky_eec_update(eec, &event, &window);
        clunky_render_text(text, &window);
        clunky_render_text(text2, &window);

        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                cont = 0;
            }
            else if (e.type == SDL_TEXTINPUT{
                inputName += e.text.text;
                std::cout << inputName << std::endl;
            }
            /*
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE){

                }
                if (e.key.keysym.sym == SDLK_BACKSPACE){

                }

            }
            */

        }
 
        //Update the window!
        clunky_present_window(&window);
    }

    SDL_StopTextInput();


    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        

            
