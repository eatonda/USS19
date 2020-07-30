#include <stdlib.h>
#include <stdio.h>
#include "board.hpp"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 50;

Board::Board(int size, int color, int ships, struct Clunky_Event *event, struct Clunky_Window* window){
    printf("1\n");
    this->board_size = size;
    this->color_theme = color;
    this->num_ships = ships;
    this->window = window;
    this->event = event;
    printf("2\n");

    //init the EEC
    this->eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(this->eec);

    printf("3\n");

}

int Board::init(){
    //setup the board elements
    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture *water_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Water.bmp", water_tex, this->window);

    //From the trexture we can create a sprite.
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite *water_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(2, 5, water_tex, water_spr);

    water_spr->sprite_row = 0;
    water_spr->sprite_column = -1;

    float board_scale = 1.;

    struct Clunky_Texture *buttonT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanButton.bmp", buttonT, this->window);
    struct Clunky_Sprite *button  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonT, button);
    struct Clunky_Event_Element **spawn = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *spawn = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*spawn, button, 60, 500, 0, "spawn\0", 'B', 'N');


    struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, this->window);
    struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonAT, buttonA);
    struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim, buttonA, 124, 500, 0, "aim\0", 'B', 'T');

    struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, this->window);
    struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 2, buttonFT, buttonF);
    struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*fire, buttonF, 60, 436, 1, "fire\0", 'B', 'N');

    struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, this->window);
    struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, pp_tex, pp_spr);

    struct Clunky_Texture *frameT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Frame.bmp", frameT, this->window);
    struct Clunky_Sprite *frameS  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, frameT, frameS);
    struct Clunky_Event_Element **frame = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *frame = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*frame, frameS, (WINDOW_WIDTH - 550)/2, (WINDOW_HEIGHT - 550)/2, 0, "frame\0", 'T', 'N');


    board_scale = 500. / ((float) water_spr->ap_w *(float) this->board_size);

    clunky_sprite_scale(board_scale, water_spr);
    clunky_sprite_scale(board_scale, pp_spr);

     struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * this->board_size * this->board_size);
    int cnt = 0;
    for (int i = 0; i < this->board_size; i++){
        for (int j = 0; j < this->board_size; j++){
//            printf("<%d, %d>\n", i, j);
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], water_spr, BOARD_OFFSET_W+water_spr->ap_w*i, BOARD_OFFSET_H+water_spr->ap_h*j, this->color_theme, "foo\0", 'S', 'A');

            cells[cnt]->z = 1;

            cnt++;
        }
    }

    clunky_eec_add_elements(this->eec, cells,this->board_size * this->board_size);
    clunky_eec_add_elements(this->eec, spawn, 1);
    clunky_eec_add_elements(this->eec, aim, 1);
    clunky_eec_add_elements(this->eec, fire, 1);
    clunky_eec_add_elements(this->eec, frame, 1);
    clunky_event_element_update_z(*frame, -1, this->eec);



    return 0;

}

int Board::run(){
    // Run game loop
        int cont = 1, k;
        while(cont){
            //first thing: check to see if there have been any new events!
            clunky_event(this->event);
            clunky_eec_update(this->eec, this->event, this->window);

            if (this->event->num_input != 0){
                //print any keypresses and check for any SDL specific events
                //(such as SDL_QUIT)
                for(k = 0; k < this->event->num_input; k++){
                    printf(">>%c\n", this->event->input[k]);

                    //all user keypressed are represented by either a number or
                    //a capital letter. lowercase letters I've reserved for
                    //SDL events
                    //'q' -> SDL_QUIT
                    if (this->event->input[k] == 'q') cont = 0;
                }
            }

            //Update the window!
            clunky_present_window(this->window);
        }

        return 0;
}


