#include <stdlib.h>
#include <stdio.h>
#include "board.hpp"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"
#include "../clunky_gl/clunkyHash.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 100;

Board::Board(int size, int color, int ships, struct Clunky_Event *event, struct Clunky_Window* window){
    printf("1\n");
    this->board_size = size;
    this->color_theme = color;
    this->num_ships = ships;
    this->window = window;
    this->event = event;
    printf("2\n");

    //create the board arrays
    this->player_board = (int **) malloc(sizeof(int *) * size);
    this->ai_board = (int **) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++){
        this->player_board[i] = (int *) malloc(sizeof(int ) * size);
        this->ai_board[i] = (int *) malloc(sizeof(int *) * size);

        for (int j = 0; j < size; j++){
            this->player_board[i][j] = -1;
            this->ai_board[i][j] = -1;
        }
    }

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

    struct Clunky_Texture *buttonT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanButton.bmp", buttonT, this->window);
    struct Clunky_Sprite *button  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonT, button);
    struct Clunky_Event_Element **spawn = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *spawn = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*spawn, button, 20, 436, 0, "plan\0", 'B', 'N');


    struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, this->window);
    struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 2, buttonAT, buttonA);
    struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim, buttonA, 144, 436, 0, "aim\0", 'B', 'N');

    struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, this->window);
    struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 2, buttonFT, buttonF);
    struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*fire, buttonF, 60, 436, 0, "fire\0", 'B', 'N');

    //Delete Planning Pin Element
    struct Clunky_Texture *dpt = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/DelPlan.bmp", dpt, this->window);
    struct Clunky_Sprite *dps = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(1, 1, dpt, dps);
    struct Clunky_Event_Element **deletePlan = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *deletePlan = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*deletePlan, dps, 84, 436, 0, "remPlan\0", 'S', 'N');

    /*
    //Ship Element
    struct Clunky_Texture *ships_t = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Ships.bmp", ships_t, this->window);
    struct Clunky_Sprite *ships_s = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 10, ships_t, ships_s);
    struct Clunky_Event_Element **shipItems = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    *shipItems = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*shipItems, ships_s, 500, 500, 0, "ship\0", 'B', 'N');

    //struct Clunky_Event_Element *shipItems = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));

    //clunky_render_sprite(40, 500, 1, 5, ships_s, this->window);*/


//    struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
//    clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, this->window);
//    struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
 //   clunky_init_sprite(1, 1, pp_tex, pp_spr);

    struct Clunky_Texture *frameT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Frame.bmp", frameT, this->window);
    struct Clunky_Sprite *frameS  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, frameT, frameS);
    struct Clunky_Event_Element **frame = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *frame = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    struct Clunky_Event_Element **frameP = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *frameP = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*frame, frameS, (WINDOW_WIDTH - 550)/2, (WINDOW_HEIGHT - 550)/2, 0, "frame\0", 'T', 'N');
    clunky_element_init(*frameP, frameS, (WINDOW_WIDTH - 550)/2 + 525, (WINDOW_HEIGHT - 550)/2 , 0, "frame\0", 'T', 'N');
    (*frame)->ignore = 1;
    (*frameP)->ignore = 1;


    this->board_scale = 500. / ((float) water_spr->ap_w *(float) this->board_size);

    clunky_sprite_scale(this->board_scale, water_spr);
    //clunky_sprite_scale(board_scale, pp_spr);

     struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * this->board_size * this->board_size);
    int cnt = 0;
    for (int i = 0; i < this->board_size; i++){
        for (int j = 0; j < this->board_size; j++){
//            printf("<%d, %d>\n", i, j);
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], water_spr, BOARD_OFFSET_W+water_spr->ap_w*i, BOARD_OFFSET_H+water_spr->ap_h*j, this->color_theme, "water\n", 'S', 'A');

            cells[cnt]->z = 1;

            cnt++;
        }
    }

    clunky_eec_add_elements(this->eec, cells,this->board_size * this->board_size);
    clunky_eec_add_elements(this->eec, spawn, 1);
    clunky_eec_add_elements(this->eec, aim, 1);
    clunky_eec_add_elements(this->eec, deletePlan, 1);

//    clunky_eec_add_elements(this->eec, fire, 1);
    clunky_eec_add_elements(this->eec, frame, 1);
    clunky_event_element_update_z(*frame, -1, this->eec);
    clunky_eec_add_elements(this->eec, frameP, 1);
    clunky_event_element_update_z(*frameP, -1, this->eec);



    return 0;

}

int Board::placeShips(){
    struct Clunky_Texture *shipT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Ships.bmp", shipT, this->window);
    struct Clunky_Sprite *ship_S = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 10, shipT, ship_S);

    struct Clunky_Event_Element **ships= (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *ships = clunky_dragable_element_init(ship_S, 400, 400, 0, "ship");
    clunky_event_element_update_z(*ships, 3, this->eec);

    struct Clunky_Event_Element **ships_m= (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *ships_m = clunky_dragable_element_init(ship_S, 500, 500, 0, "ship");
    clunky_event_element_update_z(*ships_m, 3, this->eec);

    //(ship_S)->sprite_column = 10;

    clunky_eec_add_elements(this->eec, ships, 1);
    clunky_eec_add_elements(this->eec, ships_m, 1);

    /*
    struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, this->window);
    struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, pp_tex, pp_spr);
    clunky_sprite_scale(this->board_scale, pp_spr);

    //missed pin
    struct Clunky_Texture *mp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Pins.bmp", mp_tex, this->window);
    struct Clunky_Sprite *mp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 1, mp_tex, mp_spr);
    clunky_sprite_scale(this->board_scale, mp_spr);

    //setup the EEC user move colector overlay
    struct Clunky_Event_Element_Container *move_eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(move_eec);

    
    //need to create the selector sprite sheets
    struct Clunky_Texture *sel_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Selector.bmp", sel_tex, this->window);
    struct Clunky_Sprite *sel_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(3, 2, sel_tex, sel_spr);
    clunky_sprite_scale(this->board_scale, sel_spr);

    //aim button element
    struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, this->window);
    struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 2, buttonAT, buttonA);
    struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim, buttonA, 144, 436, 1, "aim\0", 'B', 'N');
    (*aim)->misc = 1;

    //fire button element
    struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, this->window);
    struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 2, buttonFT, buttonF);
    struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*fire, buttonF, 20, 436, 1, "fire\0", 'B', 'N');


    //the aim cursor
    struct Clunky_Texture *cur_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Crosshairs.bmp", cur_tex, this->window);
    struct Clunky_Sprite *cur_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, cur_tex, cur_spr);

    clunky_eec_add_elements(move_eec, aim, 1);
    clunky_eec_add_elements(move_eec, fire, 1);

    struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * this->board_size * this->board_size);
    int cnt = 0;
    char name[2] = {'0', '\0'};
    for (int i = 0; i < this->board_size; i++){
        for (int j = 0; j < this->board_size; j++){
            name[0] = '0' + cnt;
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));
            clunky_element_init(cells[cnt], sel_spr, BOARD_OFFSET_W+sel_spr->ap_w*i, BOARD_OFFSET_H+sel_spr->ap_h*j, 0, name, 'B', 'A');
            cells[cnt]->z = 1;
            cnt++;
        }
    }

    //============
    //Add the elements to the EEC
    clunky_eec_add_elements(move_eec, cells,this->board_size * this->board_size);

    //create our text elements
    struct Clunky_Text *plyr_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 + 700, 10, 200, 100, 1., this->window);
    clunky_replace_text(plyr_txt, "YOUR SHIPS\0");
    struct Clunky_Text *ai_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 +175, 10, 200, 100, 1., this->window);
    clunky_replace_text(ai_txt, "ENEMY SHIPS\0");


    // Run game loop
        int cont = 1, k;
        int sel_indx = -1;
        while(cont){
            //first thing: check to see if there have been any new events!
            clunky_event(this->event);
            clunky_eec_update(this->eec, this->event, this->window);

            clunky_render_text(plyr_txt, this->window);
            clunky_render_text(ai_txt, this->window);

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

            //check for any eec events
            if (this->eec->sum.event_type != 'N'){
                //check for a button click
                printf("EVENT TYPE: %c\n", this->eec->sum.event_type);
                if (this->eec->sum.event_type == 'C'){
                    //check to see if it was the Planning Pin buttong
                    if (this->eec->sum.eid_one == clunky_hash_gen("plan\0")){
                        //spawn in a new planning pin
                        struct Clunky_Event_Element **pin = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
                        *pin = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
                        clunky_element_init(*pin, pp_spr, 60 - (pp_spr->ap_w /2), 500 - (pp_spr->ap_h / 2), 0, "frame\0", 'D', 'N');
                        (*pin)->misc = 1;
                        clunky_event_element_update_z(*pin, 5, this->eec);
                        clunky_eec_add_elements(this->eec, pin, 1);
                    }
                    else if (this->eec->sum.eid_one == clunky_hash_gen("aim\0")){
                        while(cont){
                            //====================================
                            //Aim Selector Screen
                            //====================================
                            //

                            //if a cell is selected, animate the fire button
                            if (sel_indx != -1) (*fire)->effect = 'A';
                            else (*fire)->effect = 'N';
                                

                            for (int i = 0; i < eec->num_ele; i++){
                                //now render the element to the window
                                clunky_element_render(this->eec->elements[i], this->window);
                            }
                            clunky_event(this->event);
                            clunky_eec_update(move_eec, this->event, this->window);

                            //render the courser
                            clunky_render_sprite(this->event->mx - cur_spr->ap_w/2, this->event->my - cur_spr->ap_h/2, 0, 0, cur_spr, this->window);

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

                            
                            if (move_eec->sum.event_type != 'N'){
                                //check for a button click
                                if (move_eec->sum.event_type == 'C'){
            //                        indx = clunky_indx_from_eid(move_eec->sum.eid_one, move_eec);
                                    if (move_eec->sum.eid_one == clunky_hash_gen("aim\0")){
                                        //set all cells that have been revliusly selected, back to unselected
                                        for (int j = 0; j < this->board_size * this->board_size; j++){
                                            if (cells[j]->row == 1) cells[j]->row = 0;
                                        }
                                        sel_indx = -1;
                                        break;
                                    }
                                    else if (move_eec->sum.eid_one == clunky_hash_gen("fire\0")){
                                        if (sel_indx != -1){
                                            printf("FIRE!\n");
                                            //set the ignore flag and change the row
                                            move_eec->elements[sel_indx]->row = 2;
                                            move_eec->elements[sel_indx]->ignore = 1;

                                            int cell_num = move_eec->elements[sel_indx]->name[0] - '0';

                                            //get the row & col
                                            int row = cell_num % this->board_size;
                                            int col = cell_num / this->board_size;

                                            //spawn in a miss pin
                                            struct Clunky_Event_Element **pin = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
                                            *pin = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
                                            clunky_element_init(*pin, mp_spr, BOARD_OFFSET_W+mp_spr->ap_w*col, BOARD_OFFSET_H+mp_spr->ap_h*row, 0, "miss\0", 'B', 'N');
                                            (*pin)->ignore = 1;
                                            clunky_event_element_update_z(*pin, 4, this->eec);
                                            clunky_eec_add_elements(this->eec, pin, 1);
                                            //add a miss pin
                                            this->player_board[row][col] = 0;


                                            printf("R:%d, C:%d\n", row, col);

                                            sel_indx = -1;

                                            //break
                                            break;
                                        }
                                    }
                                    else{
                                        //this should be a selection cell
                                        //set all cells that have been revliusly selected, back to unselected
                                        for (int j = 0; j < this->board_size * this->board_size; j++){
                                            if (cells[j]->row == 1) cells[j]->row = 0;
                                        }
                                        //get the index
                                        sel_indx = clunky_indx_from_uid(move_eec->sum.uid_one, move_eec);
                                        printf("SELECTED CELL #%d\n", move_eec->elements[sel_indx]->name[0] - '0');
                                        
                                        //set the row to select
                                        move_eec->elements[sel_indx]->row = 1;
                                    }
                                }
                            }


                            //Update the window!
                            clunky_present_window(this->window);
                        }
                    }
                }
                else if (this->eec->sum.event_type == 'S'){
                    printf("SNAP!\n");
                    if (this->eec->sum.eid_two == clunky_hash_gen("remPlan\0")){
                        //delete the planning pin
                        //
                        int indx = clunky_indx_from_uid(this->eec->sum.uid_one, this->eec);
                        clunky_eec_remove(indx, this->eec);
                   }

                }
            }

            //Update the window!
            clunky_present_window(this->window);
        }
    
    */
    
    return 0;
}

int Board::run(){

    struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, this->window);
    struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, pp_tex, pp_spr);
    clunky_sprite_scale(this->board_scale, pp_spr);

    //missed pin
    struct Clunky_Texture *mp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Pins.bmp", mp_tex, this->window);
    struct Clunky_Sprite *mp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 1, mp_tex, mp_spr);
    clunky_sprite_scale(this->board_scale, mp_spr);

    //setup the EEC user move colector overlay
    struct Clunky_Event_Element_Container *move_eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(move_eec);

    //need to create the selector sprite sheets
    struct Clunky_Texture *sel_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Selector.bmp", sel_tex, this->window);
    struct Clunky_Sprite *sel_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(3, 2, sel_tex, sel_spr);
    clunky_sprite_scale(this->board_scale, sel_spr);

    //aim button element
    struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, this->window);
    struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 2, buttonAT, buttonA);
    struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim, buttonA, 144, 436, 1, "aim\0", 'B', 'N');
    (*aim)->misc = 1;

    //fire button element
    struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, this->window);
    struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 2, buttonFT, buttonF);
    struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*fire, buttonF, 20, 436, 1, "fire\0", 'B', 'N');


    //the aim cursor
    struct Clunky_Texture *cur_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Crosshairs.bmp", cur_tex, this->window);
    struct Clunky_Sprite *cur_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 1, cur_tex, cur_spr);

    clunky_eec_add_elements(move_eec, aim, 1);
    clunky_eec_add_elements(move_eec, fire, 1);

    struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * this->board_size * this->board_size);
    int cnt = 0;
    char name[2] = {'0', '\0'};
    for (int i = 0; i < this->board_size; i++){
        for (int j = 0; j < this->board_size; j++){
            name[0] = '0' + cnt;
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));
            clunky_element_init(cells[cnt], sel_spr, BOARD_OFFSET_W+sel_spr->ap_w*i, BOARD_OFFSET_H+sel_spr->ap_h*j, 0, name, 'B', 'A');
            cells[cnt]->z = 1;
            cnt++;
        }
    }

    //============
    //Add the elements to the EEC
    clunky_eec_add_elements(move_eec, cells,this->board_size * this->board_size);

    //create our text elements
    struct Clunky_Text *plyr_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 + 700, 10, 200, 100, 1., this->window);
    clunky_replace_text(plyr_txt, "YOUR SHIPS\0");
    struct Clunky_Text *ai_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 +175, 10, 200, 100, 1., this->window);
    clunky_replace_text(ai_txt, "ENEMY SHIPS\0");


    // Run game loop
        int cont = 1, k;
        int sel_indx = -1;
        while(cont){
            //first thing: check to see if there have been any new events!
            clunky_event(this->event);
            clunky_eec_update(this->eec, this->event, this->window);

            clunky_render_text(plyr_txt, this->window);
            clunky_render_text(ai_txt, this->window);

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

            //check for any eec events
            if (this->eec->sum.event_type != 'N'){
                //check for a button click
                printf("EVENT TYPE: %c\n", this->eec->sum.event_type);
                if (this->eec->sum.event_type == 'C'){
                    //check to see if it was the Planning Pin buttong
                    if (this->eec->sum.eid_one == clunky_hash_gen("plan\0")){
                        //spawn in a new planning pin
                        struct Clunky_Event_Element **pin = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
                        *pin = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
                        clunky_element_init(*pin, pp_spr, 60 - (pp_spr->ap_w /2), 500 - (pp_spr->ap_h / 2), 0, "frame\0", 'D', 'N');
                        (*pin)->misc = 1;
                        clunky_event_element_update_z(*pin, 5, this->eec);
                        clunky_eec_add_elements(this->eec, pin, 1);
                    }
                    else if (this->eec->sum.eid_one == clunky_hash_gen("aim\0")){
                        while(cont){
                            //====================================
                            //Aim Selector Screen
                            //====================================
                            //

                            //if a cell is selected, animate the fire button
                            if (sel_indx != -1) (*fire)->effect = 'A';
                            else (*fire)->effect = 'N';
                                

                            for (int i = 0; i < eec->num_ele; i++){
                                //now render the element to the window
                                clunky_element_render(this->eec->elements[i], this->window);
                            }
                            clunky_event(this->event);
                            clunky_eec_update(move_eec, this->event, this->window);

                            //render the courser
                            clunky_render_sprite(this->event->mx - cur_spr->ap_w/2, this->event->my - cur_spr->ap_h/2, 0, 0, cur_spr, this->window);

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

                            
                            if (move_eec->sum.event_type != 'N'){
                                //check for a button click
                                if (move_eec->sum.event_type == 'C'){
            //                        indx = clunky_indx_from_eid(move_eec->sum.eid_one, move_eec);
                                    if (move_eec->sum.eid_one == clunky_hash_gen("aim\0")){
                                        //set all cells that have been revliusly selected, back to unselected
                                        for (int j = 0; j < this->board_size * this->board_size; j++){
                                            if (cells[j]->row == 1) cells[j]->row = 0;
                                        }
                                        sel_indx = -1;
                                        break;
                                    }
                                    else if (move_eec->sum.eid_one == clunky_hash_gen("fire\0")){
                                        if (sel_indx != -1){
                                            printf("FIRE!\n");
                                            //set the ignore flag and change the row
                                            move_eec->elements[sel_indx]->row = 2;
                                            move_eec->elements[sel_indx]->ignore = 1;

                                            int cell_num = move_eec->elements[sel_indx]->name[0] - '0';

                                            //get the row & col
                                            int row = cell_num % this->board_size;
                                            int col = cell_num / this->board_size;

                                            //spawn in a miss pin
                                            struct Clunky_Event_Element **pin = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
                                            *pin = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
                                            clunky_element_init(*pin, mp_spr, BOARD_OFFSET_W+mp_spr->ap_w*col, BOARD_OFFSET_H+mp_spr->ap_h*row, 0, "miss\0", 'B', 'N');
                                            (*pin)->ignore = 1;
                                            clunky_event_element_update_z(*pin, 4, this->eec);
                                            clunky_eec_add_elements(this->eec, pin, 1);
                                            //add a miss pin
                                            this->player_board[row][col] = 0;


                                            printf("R:%d, C:%d\n", row, col);

                                            sel_indx = -1;

                                            //break
                                            break;
                                        }
                                    }
                                    else{
                                        //this should be a selection cell
                                        //set all cells that have been revliusly selected, back to unselected
                                        for (int j = 0; j < this->board_size * this->board_size; j++){
                                            if (cells[j]->row == 1) cells[j]->row = 0;
                                        }
                                        //get the index
                                        sel_indx = clunky_indx_from_uid(move_eec->sum.uid_one, move_eec);
                                        printf("SELECTED CELL #%d\n", move_eec->elements[sel_indx]->name[0] - '0');
                                        
                                        //set the row to select
                                        move_eec->elements[sel_indx]->row = 1;
                                    }
                                }
                            }


                            //Update the window!
                            clunky_present_window(this->window);
                        }
                    }
                }
                else if (this->eec->sum.event_type == 'S'){
                    printf("SNAP!\n");
                    if (this->eec->sum.eid_two == clunky_hash_gen("remPlan\0")){
                        //delete the planning pin
                        //
                        int indx = clunky_indx_from_uid(this->eec->sum.uid_one, this->eec);
                        clunky_eec_remove(indx, this->eec);
                   }

                }
            }

            //Update the window!
            clunky_present_window(this->window);
        }

        return 0;
}


