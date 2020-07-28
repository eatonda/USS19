// Main File for the game

#include "../menu_functions/getGameParameters.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 50;

int main(int argc, char *argv[]) {
    // initialize window to render game to
    struct Clunky_Window window;
    struct Clunky_Event event;
    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    /* Game parameters needing to be intitialized */
    int numOfShips = -1;
    int boardSize = -1;     // Square board thus w = h
    int colorScheme = -1;   // Color scheme is either 0(light) or 1(dark)

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

    float board_scale = 1.;

    //make a button 
    //
    struct Clunky_Texture buttonT;
    clunky_load_texture("./clunky_assets/button.bmp", &buttonT, &window);
    struct Clunky_Sprite button;
    clunky_init_sprite(1, 2, &buttonT, &button);
    struct Clunky_Event_Element *spawn;
    spawn = clunky_standard_button_init(&button, 10, 500, 0, "spawn\0");

    struct Clunky_Texture pp_tex;
    clunky_load_texture("./clunky_assets/PlanningPin.bmp", &pp_tex, &window);
    struct Clunky_Sprite pp_spr;
    clunky_init_sprite(1, 1, &pp_tex, &pp_spr);



    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(eec);

//    clunky_sprite_scale(0.25, &water_spr);
    
    if (getGameParameters(&window, &event, &boardSize, &numOfShips, &colorScheme)) {
        
        /* Trace Statement showing instantiated parameters */
        std::cout << " Parameters Instantiated via getGameParameters()\n";
        std::cout << "numOfShips: " << numOfShips << std::endl;
        std::cout << "Square boardSize: " << boardSize << std::endl;
        std::cout << "colorScheme 0(light) or 1(dark): " << colorScheme << std::endl;

        //for now I need a smaller board size than what david's options provide
        boardSize = 5;

        //calculate the board scale
        board_scale = 500. / ((float) water_spr.ap_w *(float) boardSize);
        printf("><><><><>%f\n", board_scale);
        clunky_sprite_scale(board_scale, &water_spr);
        clunky_sprite_scale(board_scale, &pp_spr);

        struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * boardSize*boardSize);
    int cnt = 0;
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            printf("<%d, %d>\n", i, j);
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], &water_spr, BOARD_OFFSET_W+water_spr.ap_w*i, BOARD_OFFSET_H+water_spr.ap_h*j, 0, "foo\0", 'S', 'A');

            cells[cnt]->z = 1;

            cnt++;
        }
    }

    printf("===========================\n");
    clunky_eec_add_elements(eec, cells,boardSize*boardSize);
    printf("===========================\n");
    clunky_eec_add_elements(eec, &spawn, 1);
    printf("===========================\n");

    printf("++%d, %d\n", eec->len_ele, eec->num_ele);
    for (int p = 0; p < eec->num_ele; p++){
        printf("==%d, %d\n", eec->elements[p]->z, p+1);
    }
        
        
        
        // Instantiate game objects
        

        // Run game loop
        int cont = 1, k;
        while(cont){
            //first thing: check to see if there have been any new events!
            clunky_event(&event);
            clunky_eec_update(eec, &event, &window);

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
                    else if (event.input[k] == 'S'){
                        printf("SPAWNING NEW ELEMENT from keystroke\n");
                        struct Clunky_Event_Element *ppd = clunky_dragable_element_init(&pp_spr, 0, 0, 0, "ppd\0");
                        printf("<%d, %d>\n", ppd->x, ppd->y);
                        clunky_eec_add_elements(eec, &ppd, 1);
                }
                }

            }
            if (eec->sum.event_type != 'N'){
                if (eec->sum.eid_one == clunky_hash_gen("spawn\0")){
                    printf("SPAWNING NEW ELEMENT from button\n");
                    struct Clunky_Event_Element *ppd = clunky_dragable_element_init(&pp_spr, 0, 0, 0, "ppd\0");
                    printf("<%d, %d>\n", ppd->x, ppd->y);
                    clunky_eec_add_elements(eec, &ppd, 1);
                }
            }



            //Update the window!
            clunky_present_window(&window);
        }
    }
    }
    

