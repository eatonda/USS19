#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

int main(int argc, char *argv[]){
    int i, j, k;
    int cont;

    struct Clunky_Window window; 

    struct Clunky_Event event;

    clunky_init(&window, &event, 500, 500);

    struct Clunky_Texture ship_tex;
    clunky_load_texture("rsz_yellow_square.bmp", &ship_tex, &window);

    struct Clunky_Sprite ship_sprite;
    clunky_init_sprite(1, 1, &ship_tex, &ship_sprite);

    ship_sprite.sprite_row = 0;
    ship_sprite.sprite_column = 0;

    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    struct Clunky_Text *text = clunky_get_text(10, 10, 512, 64, 1., &window);
    clunky_replace_text(text, "THIS IS A SHIP!\0");
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

        
        /*for (int i = 0; i < 1*64; i += 64){
            for (int j = 0; j < 1*64; j += 64){
               clunky_animate_sprite(100 + i, 100 + j, &ship_sprite, &window);
            }
        }*/
        clunky_render_sprite(100, 100, ship_sprite.sprite_row, ship_sprite.sprite_column, &ship_sprite, &window);
        clunky_render_sprite(164, 100, ship_sprite.sprite_row, ship_sprite.sprite_column, &ship_sprite, &window);
        //clunky_render_sprite(100, 100, ship_sprite.sprite_row, ship_sprite.sprite_column, &ship_sprite, &window);

        //Update the window!
        clunky_present_window(&window);
    }



    SDL_Quit();

    return 0;
}
