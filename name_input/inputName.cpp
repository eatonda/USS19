#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

int main(int argc, char *argv[]){

    //dec common use variables
    int i, j, k;
    int cont;

    //create a window to render objects to.
    struct Clunky_Window window;

    //we need to create our event handler!
    struct Clunky_Event event;

    //now we will init the window, this will set the width and height of the
    //window, as well as call the nessisary SDL2 function calls for us
    clunky_init(&window, &event, 640, 480);

    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    //create a clunky text object!
    struct Clunky_Text *gameOverText = clunky_get_text(225, 25, 512, 64, 1., &window);
    clunky_replace_text(gameOverText, "GAME OVER!\0");
    for (int i = 0; i < gameOverText->str_used; i++){
        printf("%c, (%d, %d)\n", gameOverText->str[i], gameOverText->str_row[i], gameOverText->str_col[i]);
    }

    struct Clunky_Text *promptText = clunky_get_text(130, 125, 512, 64, 1., &window);
    clunky_replace_text(promptText, "PLEASE ENTER YOUR NAME\0");
    for (int i = 0; i < promptText->str_used; i++){
        printf("%c, (%d, %d)\n", promptText->str[i], promptText->str_row[i], promptText->str_col[i]);
    }

    struct Clunky_Text *inputText = clunky_get_text(130, 200, 512, 64, 1., &window);
    clunky_replace_text(inputText, "NAME:\0");
    for (int i = 0; i < inputText->str_used; i++){
        printf("%c, (%d, %d)\n", inputText->str[i], inputText->str_row[i], inputText->str_col[i]);
    }

    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        clunky_eec_update(eec, &event, &window);
        clunky_render_text(gameOverText, &window);
        clunky_render_text(promptText, &window);
        clunky_render_text(inputText, &window);

        //
        if (event.num_input != 0){
            //print any keypresses and check for any SDL specific events 
            //(such as SDL_QUIT)
            for(k = 0; k < event.num_input; k++){
                printf(">>%c\n", event.input[k]);

                //'q' -> SDL_QUIT
                if (event.input[k] == 'q') cont = 0;

                // Prints input into console
                if (event.input[k] == '`') printf("Name: %s\n", eec->sum.str);
            }
        }

        char* name = eec->sum.str;

        // Create text
        struct Clunky_Text *nameText = clunky_get_text(225, 200, 512, 64, 1., &window);
        clunky_replace_text(nameText, name);

        // Render name to window
        clunky_render_text(nameText, &window);

        //Update the window!
        clunky_present_window(&window);
    }

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
