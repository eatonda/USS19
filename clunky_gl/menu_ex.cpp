#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "clunkyCore.h"
#include "clunkyHash.h"
#include "clunkyAdvEvents.h"

int main(int argc, char *argv[]){

    //dec common use variables
    int i, j, k;
    int cont;

    //create a clunky window object.
    //this will be the window that we will render to
    struct Clunky_Window window;

    //now we will init the window, this will set the width and height of the
    //window, as well as call the nessisary SDL2 function calls for us
    //this has to be done first, as it inits SDL2 functions
    clunky_init(&window, 640, 480);

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
    struct Clunky_Button *mainmenu = (struct Clunky_Button *)malloc(sizeof(struct Clunky_Button) * 4);
    //now we need to init all of the buttons
    //unfortuantly, this is best done manually on a small scale
    clunky_button_init(&(mainmenu[0]), &mmb, 100, 10, 0, "start\0", 'r');
    clunky_button_init(&(mainmenu[1]), &mmb, 100, 60, 1, "options\0", 'r');
    clunky_button_init(&(mainmenu[2]), &mmb, 100, 110, 2, "credits\0", 't');
    clunky_button_init(&(mainmenu[3]), &mmb, 100, 160, 3, "quit\0", 'r');

    //finally we need to create our event handler!
    struct Clunky_Event event;

    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;
    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        
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
       //now lets deal with mouse clicks!
       if (event.lc || event.rc){
            //check to see if there is any button activity
            //if a button has been clicked, its BID will be returned by the function
            //we can get the BID using the buttons name by hashing it
            //only one button can be clicked at a time, so we only need to
            //check once per loop
            bid = clunky_button_check(mainmenu, 4, &event);

            //if bid == 0, there was no button press
            //therefore, we dont need to check
            if (bid){
                //check to see if the start button was pressed
                if (bid == clunky_hash_gen("start\0")){
                    printf("CLICKED THE START BUTTON\n");
                }
                else if (bid == clunky_hash_gen("options\0")){
                    printf("CLICKED THE OPTIONS BUTTON\n");
                }
                else if (bid == clunky_hash_gen("credits\0")){
                    printf("CLICKED THE CREDITS BUTTON\n");
                }
                else if (bid == clunky_hash_gen("quit\0")){
                    printf("CLICKED THE QUIT BUTTON\n");
                    cont = 0;
                }
            }
        }

        //alright, now we need to render the buttons!
        clunky_button_render(&(mainmenu[0]), &window);
        clunky_button_render(&(mainmenu[1]), &window);
        clunky_button_render(&(mainmenu[2]), &window);
        clunky_button_render(&(mainmenu[3]), &window);

        //finally, we need to update and present the window
        clunky_present_window(&window);
        clunky_update_renderer(&window);

        //Now we just need a small delay to prevent the loop from consuming
        //too many resources
        SDL_Delay(10);
    }


    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        

            
