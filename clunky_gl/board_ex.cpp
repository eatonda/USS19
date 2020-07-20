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
    struct Clunky_Texture water_tex;
    clunky_load_texture("./clunky_assets/Water.bmp", &water_tex, &window);

    //From the trexture we can create a sprite. 
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite water_spr;
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(1, 5, &water_tex, &water_spr);

    water_spr.sprite_row = 0;
    water_spr.sprite_column = -1;


    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    //create a clunky text object!
    struct Clunky_Text *text = clunky_get_text(10, 10, 512, 64, 1., &window);
    clunky_replace_text(text, "THIS IS THE BOARD! :)\0");
    for (int i = 0; i < text->str_used; i++){
        printf("%c, (%d, %d)\n", text->str[i], text->str_row[i], text->str_col[i]);
    }

    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        clunky_eec_update(eec, &event, &window);
        clunky_render_text(text, &window);
        
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

        clunky_animate_sprite(100, 100, &water_spr, &window);

        //Update the window!
        clunky_present_window(&window);
    }
    

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        

            
