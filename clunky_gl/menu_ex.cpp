#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

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

    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture main_menu_texture;
    clunky_load_texture("./buttons.bmp", &main_menu_texture, &window);

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
    struct Clunky_Event_Element **mainMenuElements = (struct Clunky_Event_Element **)malloc(sizeof(struct Clunky_Event_Element*) * 4);
    //now we need to init all of the buttons
    mainMenuElements[0] = clunky_standard_button_init(&mmb, 100, 10, 0, "start");
    mainMenuElements[1] = clunky_standard_button_init(&mmb, 100, 60, 1, "options");
    mainMenuElements[2] = clunky_standard_button_init(&mmb, 100, 110, 2, "credits");
    mainMenuElements[3] = clunky_standard_button_init(&mmb, 100, 160, 3, "quit");

    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    //add the Main Menu Elements (aka buttons at this point) to the eec
    clunky_eec_add_elements(eec, mainMenuElements, 4);
    
    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        clunky_eec_update(eec, &event, &window);
        
        //if there has been a keypress (indicated with num_input != 0)
        //or a mouse click (indicated with lc || rc == 1)
        //then check to see what has happened
        if (event.num_input != 0){
            //print any keypresses and check for any SDL specific events 
            //(such as SDL_QUIT)
            for(k = 0; k < event.num_input; k++){
                printf(">>%c\n", event.input[k]);

                //all user keypressed are represented by either a number or
                //a capital letter. lowercase letters I've reserved for
                //SDL events
                //'q' -> SDL_QUIT
                if (event.input[k] == 'q') cont = 0;
            }

        }

        //check the buttons to see if anywhere clicked
        //first, check to make sure that there was a selected button
        if (eec->sum.eid != 0){
            //ok, a button was interacted with!
            //find out which one
            if (eec->sum.eid == clunky_hash_gen("start")){
                printf("START\n");
            }
            else if (eec->sum.eid == clunky_hash_gen("options")){
                printf("OPTIONS\n");
            }
            else if (eec->sum.eid == clunky_hash_gen("credits")){
                printf("CREDITS\n");
            }
            else if (eec->sum.eid == clunky_hash_gen("quit")){
                printf("QUIT\n");
                cont = 0;
            }
        }

        //Update the window!
        clunky_present_window(&window);
    }
    

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        

            
