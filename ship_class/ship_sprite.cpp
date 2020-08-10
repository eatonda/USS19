#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

int main(int argc, char *argv[]){

    int i, j, k;
    int cont;

    //create a clunky window object.
    struct Clunky_Window window;

    //we need to create our event handler!
    struct Clunky_Event event;

    //now we will init the window
    clunky_init(&window, &event, 640, 480);

    //load the texture that contains all of our main menu buttons
    struct Clunky_Texture water_tex;
    clunky_load_texture("./clunky_assets/Water.bmp", &water_tex, &window);

    struct Clunky_Sprite water_spr;
    clunky_init_sprite(1, 5, &water_tex, &water_spr);

    water_spr.sprite_row = 0;
    water_spr.sprite_column = -1;
    clunky_sprite_scale(1.75, &water_spr);

    char names[] = "cell_x_\0";
    int cnt = 0;
    struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * 25);
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            names[4] = '0' + i;
            names[6] = '0' + j;

            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], &water_spr, water_spr.ap_w*i, water_spr.ap_h*j, 0, names, 'S', 'A');

            cnt++;
        }
    }

     //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture ship_tex;
    clunky_load_texture("/rsz_yellow_square.bmp", &ship_tex, &window);
    struct Clunky_Sprite ship_sprite;
    clunky_init_sprite(1, 1, &ship_tex, &ship_sprite);

    struct Clunky_Event_Element *ship = clunky_dragable_element_init(&ship_sprite, 500, 200, 0, "ship");



    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);
    printf(">>>>>\n");
    clunky_eec_add_elements(eec, cells, 25);
    clunky_eec_add_elements(eec, &ship, 1);
    printf("ASASASASAS\n");
    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    //create a clunky text object!
    struct Clunky_Text *text = clunky_get_text(10, 10, 512, 64, 0.5, &window);
    printf("HHH\n");
    clunky_replace_text(text, "THIS IS THE BOARD! :)\0");
    printf("CCCC\n");
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
        if (eec->sum.event_type != 'N'){
            if (eec->sum.event_type == 'S'){
                printf("Elements have been snapped together!\n");
                for (int k = 0; k < eec->num_snaps; k++){
                    if (eec->snaps[k]->eid == eec->sum.eid_two){
                        printf(">>Snap To Element: %s\n", eec->snaps[k]->name);
                    }
                }
            }
        }


        //Update the window!
        clunky_present_window(&window);
    }
    

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
