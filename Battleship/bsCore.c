#include "bsCore.h"
#include "aiBoards.h"
#include "name_input/inputName.hpp"
#include "data_functions/enterScore.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 100;

int endCard(struct BSCore *c){
    int CENTER_x = c->window->width * 0.5;
    int CENTER_y = c->window->height * 0.225;

    struct Clunky_Event_Element_Container * eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(eec);

    struct Clunky_Text* txt = clunky_get_text(CENTER_x, CENTER_y, 512, 64, 1.,c->window);

    if (c->winnerFlag > 0){
        clunky_add_text(txt, "YOU WON!");
    }
    else{
        clunky_add_text(txt, "YOU LOST!");
    }

    struct Clunky_Texture *buttonAT2 = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/OK.bmp", buttonAT2, c->window);
    struct Clunky_Sprite *buttonA2  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonAT2, buttonA2);
    struct Clunky_Event_Element **aim2 = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim2 = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim2, buttonA2, CENTER_x, CENTER_y*3, 0, "aim\0", 'B', 'N');
    
    clunky_eec_add_elements(eec, aim2, 1);

    int cont = 1, k;
    int sel_indx = -1;
    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(c->event);
        clunky_eec_update(eec, c->event, c->window);

        clunky_render_text(txt, c->window);


        if (c->event->num_input != 0){
            //print any keypresses and check for any SDL specific events
            //(such as SDL_QUIT)
            for(k = 0; k < c->event->num_input; k++){
            printf(">>%c\n", c->event->input[k]);

            //all user keypressed are represented by either a number or
            //a capital letter. lowercase letters I've reserved for
            //SDL events
            //'q' -> SDL_QUIT
            if (c->event->input[k] == 'q') cont = 0;
            }
        }

       //check for any eec events
       if (eec->sum.event_type == 'C'){
            //printf("CLICKED!\n");
            if (c->winnerFlag > 0){
                int score = calcScore(c->turnCnter, c->board_size, c->board_size);
                if (isHighScore(score)){
                    std::string name = inputNameT(c->window, c->event);
                    enterScore(score, name);
                }

            }

            cont = 0;
       }

        clunky_present_window(c->window);
   }

   return 0;
}



int checkForWin(struct BSCore *c){
    if ( c->ai_hits >= c->hits_to_win){
        c->winnerFlag = -1;
        return 1;
    }
    else if ( c->player_hits >= c->hits_to_win){
        c->winnerFlag = 1;
        return 1;
    }
    return 0;
}
    

int attack_ai(struct BSCore *c){
    //Find a spot randomly in the players board that hasnt been selected yet
    while(1){
        int row = rand() % c->board_size;
        int col = rand() % c->board_size;
        if (c->player_board[row][col] == -1 && c->pins[row][col] == -1){
            c->pins[row][col] = 0;
            break;
        }
        else if (c->player_board[row][col] != -1 && c->pins[row][col] == -1){
            c->pins[row][col] = 1;
            c->player_hits++;
            break;
       }
    }

    return 0;
}

int move(int row, int col, struct BSCore *c){

    //check to see if there is a pin there
    if(c->ai_pins[row][col] == -1){
        //check to see if its a hit
        if(c->ai_board[row][col] != -1){
            //its a hit!
            c->ai_pins[row][col] = 1;
            c->ai_hits++;
        }
        else{
            c->ai_pins[row][col] = 0;
        }
    }

    return 0;
}

int render(struct BSCore *c){
    //render the ships, then the pins, to the screen
    for(int i = 0; i < c->board_size; i++){
        for(int j = 0; j < c->board_size; j++){
            if ( c->player_board[i][j] >= 0){
                //render the ship
                clunky_render_sprite(BOARD_OFFSET_W+c->ship_spr->ap_w*i + 525, BOARD_OFFSET_H + j * c->ship_spr->ap_h, c->player_board[i][j], 0, c->ship_spr, c->window);
            }
            if (c->ai_pins[i][j] >= 0){
                //render the pin
                clunky_render_sprite(BOARD_OFFSET_W + i * c->pin_spr->ap_w, BOARD_OFFSET_H + j * c->pin_spr->ap_h, c->ai_pins[i][j], 0, c->pin_spr, c->window);
            }
            if (c->pins[i][j] >= 0){
                //render the pin
                clunky_render_sprite(BOARD_OFFSET_W + i * c->pin_spr->ap_w + 525, BOARD_OFFSET_H + j * c->pin_spr->ap_h, c->pins[i][j], 0, c->pin_spr, c->window);
            }
        }
    }

    return 0;
}

int ship_rotation_helper(int rotation, int row){
    //if the range is between 0 and 3: ship front
    if (row >= 0 && row <= 3){
        //if we have a positive rotation, incriment the row, wrapping back to 0 after 3
        if (rotation > 0){
            //see if we need to wrap around to 0
            if (row == 3) return 0;
            //otherwise incriment the row
            return row + 1;
        }
        else{
            //decriment the row
            //see if we need to wrap around to 3
            if (row == 0) return 3;
            //otherwise decriment
            return row - 1;
        }
    }
    //if the range is between 4 and 7: Ship rear
    else if (row >= 4 && row <= 7){
        //if we have a positive rotation, incriment the row, wrapping back to 0 after 3
        if (rotation > 0){
            //see if we need to wrap around to 0
            if (row == 7) return 4;
            //otherwise incriment the row
            return row + 1;
        }
        else{
            //decriment the row
            //see if we need to wrap around to 3
            if (row == 4) return 7;
            //otherwise decriment
            return row - 1;
        }
    }
    //otherwise we have the ship middle, 8 and 9
    //just toggle
    else if (row == 8) return 9;
    else if (row == 9) return 8;

    //if we got here, we have an invalid row
    return -1;
}

int rotate(struct BSCore *c, int dir){
    //need temporary hold arrays
    int **pinH = c->ai_pins;
    int **pinP = c->pins;
    int **shipH = c->player_board;

    //now re-allocate the Ship and Pins arrays
    ////Allocate the memory for the Pins array, and set the default value to -1 for all cells
    c->ai_pins = (int **) malloc(sizeof(int *) * c->board_size);
    c->pins = (int **) malloc(sizeof(int *) * c->board_size);
    c->player_board = (int **) malloc(sizeof(int *) * c->board_size);

    //copy over the passed ship placement, and finish allocating memory
    for (int i = 0; i < c->board_size; i++){
        c->ai_pins[i] = (int *) malloc(sizeof(int) * c->board_size);
        c->pins[i] = (int *) malloc(sizeof(int) * c->board_size);
        c->player_board[i] = (int *) malloc(sizeof(int) * c->board_size);

        for (int j = 0; j < c->board_size; j++){
            c->ai_pins[i][j] = -1;
            c->pins[i][j] = -1;
            c->player_board[i][j] = -1;
        }
    }


//    printf("ROTATING\n");
//

    //rotate the boards
    //if we have a positive roation value, rotate clockwise
    //otherwise anti-clockwise

    if( dir > 0){
        //CW
        if (c->rotation >= 3) c->rotation = 0;
        else c->rotation++;
            //Even
            for (int k = 0; k < c->board_size; k++){
                for (int j = 0; j < c->board_size; j++){
                    //copy over and rotate the pins
                    c->ai_pins[c->board_size - 1 - k][j] = pinH[j][k];
                    c->pins[c->board_size - 1 - k][j] = pinP[j][k];

                    //copy over and rotate the ship peices
                    //Will need to also update the spite row after the rotation
                    c->player_board[c->board_size - 1 - k][j] = ship_rotation_helper(dir, shipH[j][k]);
                }
            }
    }
    else{
        //CCW
        if (c->rotation <= 0) c->rotation = 3;
        else c->rotation--;
            //Even
            for (int k = 0; k < c->board_size; k++){
                for (int j = 0; j < c->board_size; j++){
                    //copy over and rotate the pins
                    c->ai_pins[k][c->board_size - 1 - j] = pinH[j][k];
                    c->pins[k][c->board_size - 1 - j] = pinP[j][k];

                    //copy over and rotate the ship peices
                    //Will need to also update the spite row after the rotation
                    c->player_board[k][c->board_size - 1 - j] = ship_rotation_helper(dir, shipH[j][k]);
                }
            }
    }

    //free the temp arrays
    printf("Free-ing [] Rotation\n");
    for (int i = 0; i < c->board_size; i++){
        free(shipH[i]);
        free(pinH[i]);
        free(pinP[i]);
    }
    printf("Free-ing hold** Rotation\n");
    free(shipH);
    free(pinH);
    free(pinP);
    printf("Rotation Free-ing Done\n");

    return 0;
}

int loadMedia(struct BSCore *c){
    //setup the board elements
    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture *water_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Water.bmp", water_tex, c->window);
    struct Clunky_Texture *blank_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/BlankCell.bmp", blank_tex, c->window);

    //From the trexture we can create a sprite.
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite *water_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    struct Clunky_Sprite *blank_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(1, 1, blank_tex, blank_spr);
    clunky_init_sprite(2, 5, water_tex, water_spr);

    water_spr->sprite_row = 0;
    water_spr->sprite_column = -1;

    struct Clunky_Texture *buttonT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PlanButton.bmp", buttonT, c->window);
    struct Clunky_Sprite *button  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonT, button);
    struct Clunky_Event_Element **spawn = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *spawn = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*spawn, button, 20, 436, 0, "plan\0", 'B', 'N');
    
    struct Clunky_Texture *buttonTCW = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/CW.bmp", buttonTCW, c->window);
    struct Clunky_Sprite *buttonCW  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonTCW, buttonCW);
    struct Clunky_Event_Element **cw = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *cw = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*cw, buttonCW, 20, 500, 0, "CW\0", 'B', 'N');
    
    struct Clunky_Texture *buttonTCCW = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/CCW.bmp", buttonTCCW, c->window);
    struct Clunky_Sprite *buttonCCW  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(1, 2, buttonTCCW, buttonCCW);
    struct Clunky_Event_Element **ccw = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *ccw = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*ccw, buttonCCW, 84, 500, 0, "CCW\0", 'B', 'N');

    struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, c->window);
    struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 2, buttonAT, buttonA);
    struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*aim, buttonA, 144, 436, 0, "aim\0", 'B', 'N');

    struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, c->window);
    struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(2, 2, buttonFT, buttonF);
    struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*fire, buttonF, 60, 436, 0, "fire\0", 'B', 'N');


	// pause button element
	struct Clunky_Texture *buttonPT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/PauseButton.bmp", buttonPT, c->window);
    struct Clunky_Sprite *buttonP = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(1, 2, buttonPT, buttonP);
    struct Clunky_Event_Element **pause = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *pause = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*pause, buttonP, 676, 640, 0, "pause\0", 'B', 'N');



    //Delete Planning Pin Element
    struct Clunky_Texture *dpt = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/DelPlan.bmp", dpt, c->window);
    struct Clunky_Sprite *dps = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
    clunky_init_sprite(1, 1, dpt, dps);
    struct Clunky_Event_Element **deletePlan = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *deletePlan = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*deletePlan, dps, 84, 436, 0, "remPlan\0", 'S', 'N');

//    struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
//    clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, this->window);
//    struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
 //   clunky_init_sprite(1, 1, pp_tex, pp_spr);

    struct Clunky_Texture *frameT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Frame.bmp", frameT, c->window);
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

    c->board_scale = 500. / ((float) water_spr->ap_w *(float) c->board_size);

    clunky_sprite_scale(c->board_scale, water_spr);
    clunky_sprite_scale(c->board_scale, blank_spr);
    //clunky_sprite_scale(board_scale, pp_spr);

     struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * c->board_size * c->board_size);
     struct Clunky_Event_Element **pcells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * c->board_size * c->board_size);
     struct Clunky_Event_Element **empty_cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * c->board_size * c->board_size);
    int cnt = 0;
    char name[2] = {'0', '\0'};
    for (int i = 0; i < c->board_size; i++){
        for (int j = 0; j < c->board_size; j++){
//            printf("<%d, %d>\n", i, j);
            name[0] = '0' + cnt;
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));
            empty_cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], water_spr, BOARD_OFFSET_W+water_spr->ap_w*i, BOARD_OFFSET_H+water_spr->ap_h*j, c->color_theme, "water\n", 'S', 'A');
            clunky_element_init(empty_cells[cnt], blank_spr, BOARD_OFFSET_W+water_spr->ap_w*i, BOARD_OFFSET_H+water_spr->ap_h*j, 0, name, 'B', 'N');

            pcells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));
              clunky_element_init(pcells[cnt], water_spr, BOARD_OFFSET_W+water_spr->ap_w*i+525, BOARD_OFFSET_H+water_spr->ap_h*j, 0, name, 'B', 'A');
              pcells[cnt]->z = 1;
              pcells[cnt]->ignore = 1;

            cells[cnt]->z = 1;
            empty_cells[cnt]->z = 1;

            cnt++;
        }
    }

    clunky_eec_add_elements(c->eec, cells, c->board_size * c->board_size);
    clunky_eec_add_elements(c->eec, pcells, c->board_size * c->board_size);
    clunky_eec_add_elements(c->selector, empty_cells, c->board_size * c->board_size);
    clunky_eec_add_elements(c->eec, spawn, 1);
    clunky_eec_add_elements(c->eec, aim, 1);
	clunky_eec_add_elements(c->eec, pause, 1);
    clunky_eec_add_elements(c->eec, deletePlan, 1);
    clunky_eec_add_elements(c->eec, cw, 1);
    clunky_eec_add_elements(c->eec, ccw, 1);
    clunky_eec_add_elements(c->selector, cw, 1);
    clunky_eec_add_elements(c->selector, ccw, 1);
//    clunky_eec_add_elements(c->eec, fire, 1);
    clunky_eec_add_elements(c->eec, frame, 1);
    clunky_event_element_update_z(*frame, -5, c->eec);
    clunky_eec_add_elements(c->eec, frameP, 1);
    clunky_event_element_update_z(*frameP, -1, c->eec);


     //load the pin texture/init the sprite
    struct Clunky_Texture * pt = (struct Clunky_Texture *) malloc (sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Pins.bmp", pt, c->window);
    c->pin_spr = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 1, pt, c->pin_spr);
    clunky_sprite_scale(c->board_scale,c->pin_spr);

    //allocate the memory for the board sprite
    struct Clunky_Texture * st = (struct Clunky_Texture *) malloc (sizeof(struct Clunky_Texture));
    c->ship_spr = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));

    //load the texture based off of the theme
    if(c->color_theme){
        clunky_load_texture("./clunky_assets/DarkShip.bmp", st, c->window);
    }
    else{
        clunky_load_texture("./clunky_assets/LightShip.bmp", st, c->window);
    }
    clunky_init_sprite(10, 1, st, c->ship_spr);
    clunky_sprite_scale(c->board_scale,c->ship_spr);

    //the aim cursor
      struct Clunky_Texture *cur_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/Crosshairs.bmp", cur_tex, c->window);
      c->cur = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(1, 1, cur_tex, c->cur);

//     struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
  //    clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, c->window);
    //  struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
      clunky_init_sprite(2, 2, buttonFT, buttonF);
      c->fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
      clunky_element_init(c->fire, buttonF, 20, 436, 1, "fire\0", 'B', 'N');
        clunky_eec_add_elements(c->selector, &(c->fire), 1);
    //need to create the selector sprite sheets
      struct Clunky_Texture *sel_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/Selector.bmp", sel_tex, c->window);
     c->cell= (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(3, 2, sel_tex, c->cell);
      clunky_sprite_scale(c->board_scale, c->cell);
      c->cell->sprite_column = -1;

      //aim button element
      struct Clunky_Texture *buttonAT2 = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT2, c->window);
      struct Clunky_Sprite *buttonA2  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(2, 2, buttonAT2, buttonA2);
      struct Clunky_Event_Element **aim2 = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
      *aim2 = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
      clunky_element_init(*aim2, buttonA2, 144, 436, 1, "aim\0", 'B', 'N');
      (*aim2)->misc = 1;
        clunky_eec_add_elements(c->selector, aim2, 1);


    return 0;
}

int bsInit(int size, int color, int ships, struct Clunky_Event *event, struct BSCore *c, struct Clunky_Window* window){

    c->board_size = size;
    c->color_theme = color;
    c->num_ships = ships;
    c->window = window;
    c->event = event;
    c->rotation = 0;
    c->hits_to_win = 0;
    c->ai_hits = 0;
    c->player_hits = 0;
    c->winnerFlag = 0;
    c->turnCnter = 0;

    //create the board arrays
    c->pins = (int **) malloc(sizeof(int *) * size);
    c->player_board = (int **) malloc(sizeof(int *) * size);
    c->ai_pins = (int **) malloc(sizeof(int *) * size);
//    c->ai_board = (int **) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++){
        c->player_board[i] = (int *) malloc(sizeof(int ) * size);
  //      c->ai_board[i] = (int *) malloc(sizeof(int ) * size);
        c->pins[i] = (int *) malloc(sizeof(int ) * size);
        c->ai_pins[i] = (int *) malloc(sizeof(int ) * size);

        for (int j = 0; j < size; j++){
            c->pins[i][j] = -1;
            c->ai_pins[i][j] = -1;
            c->player_board[i][j] = -1;
    //        c->ai_board[i][j] = -1;
        }
    }

//    c->player_board[0][0] = 0;
//    c->player_board[4][4] = 0;

    //init the EECs
    c->eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(c->eec);
    c->selector = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(c->selector);

    //load the media
    loadMedia(c);

    return 0;
}

int bsLayout(struct BSCore *c){
    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    //get the ship assets
    struct Ship_Assets s;
    init_ship(c->board_scale, &s, c->window);

    //Ship sizes
    int shipSizes [] = {5, 4, 3, 2, 2, 3, 4, 2, 2, 2};

    //get the AI board
    c->ai_board = get_ai_board(c->board_size, c->num_ships);

	// will hold the clunky event elements for each of the ships
    struct Clunky_Event_Element ***ships = (struct Clunky_Event_Element***) malloc(sizeof(struct Clunky_Event_Element**) * c->num_ships);

    //Generating the ships
    for(int i = 0; i < c->num_ships; i++){
        ships[i] = generate_ship(shipSizes[i], 1, eec, s);
        for(int j = 0; j < shipSizes[i]; j++){
            ships[i][j]->y = 64*i;
        }
        c->hits_to_win += shipSizes[i];
    }

    struct Clunky_Texture *water_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/Water.bmp", water_tex, c->window);

    //From the trexture we can create a sprite.
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite *water_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(2, 5, water_tex, water_spr);

    water_spr->sprite_row = 0;
    water_spr->sprite_column = -1;
    clunky_sprite_scale(c->board_scale, water_spr);

    struct Clunky_Texture *startBtnT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    clunky_load_texture("./clunky_assets/StartButton.bmp", startBtnT, c->window);

    //From the trexture we can create a sprite.
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite *startBtnS = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(1, 2, startBtnT, startBtnS);
    struct Clunky_Event_Element **start = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
    *start = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
    clunky_element_init(*start, startBtnS, 900, 300, 0, "start\0", 'B', 'N');



    struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * c->board_size * c->board_size);
    int cnt = 0;
    char name[2] = {'0', '\0'};
    for (int i = 0; i < c->board_size; i++){
        for (int j = 0; j < c->board_size; j++){
            name[0] = '0' + cnt;
            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));
            clunky_element_init(cells[cnt], water_spr, BOARD_OFFSET_W+water_spr->ap_w*i, BOARD_OFFSET_H+water_spr->ap_h*j, 0, name, 'S', 'A');
            cells[cnt]->z = -1;
            cnt++;
        }
    }

    //============
    //Add the elements to the EEC
    clunky_eec_add_elements(eec, cells,c->board_size * c->board_size);
    clunky_eec_add_elements(eec, start, 1);

    int cont = 1, k;
    int sel_indx = -1;

	// 2D array that will hold the positions of all ships on the board
	// -1 : no ship in that cell
	// ship cells are identified by the sprite column of the ship
	int** boardGrid =  (int**) malloc(sizeof(int*) * c->board_size);
	for (int i = 0; i < c->board_size; i++) {
		boardGrid[i] = (int*) malloc(sizeof(int) * c->board_size);
	}

	// set all cells in the board grid to -1 indicating that no ships have
	// been placed yet
	for (int i = 0; i < c->board_size; i++) {
		for (int j = 0; j < c->board_size; j++) {
			boardGrid[i][j] = -1;
		}
	}

	// array holding the orientation of each ship
	// 0 - for the 0 offset event element as the leftmost
	// 1 - 0 offset element as the topmost
	// 2 - 0 offset element as the rightmost
	// 3 - 0 offset element as the bottommost
	// ** SETTING THE DEFAULT TO LEFTMOST. IF WE ADD IN THE ABILITY TO ROTATE SHIPS
	//		THIS SECTION WILL NEED TO BE MODIFIED **
	int* orientation = (int*) malloc(sizeof(int) * c->num_ships);
	for (int i = 0; i < c->num_ships; i++) {
		orientation[i] = 0;
	}

	// holds the position of the 0 offset event element of each ship
	// first index represents the index of the ship. For the second index,
	// a 0 gives the row of the 0 offset and a 1 gives the column of the 0 offset
	int** shipPos = (int**) malloc(sizeof(int*) * c->num_ships);
	for (int i = 0; i < c->num_ships; i++) {
		shipPos[i] = (int*) malloc(sizeof(int) * 2);
	}	
	for (int i = 0; i < c->num_ships; i++) {
		for (int j = 0; j < 2; j++) {
			shipPos[i][j] = -1;
		}
	}

	// holds a 1 if a ship is placed within the bounds of the board and a 0 otherwise
	int* shipPlaced = (int*) malloc(sizeof(int) * c->num_ships);
	for (int i = 0; i < c->num_ships; i++) {
		shipPlaced[i] = 0;
	} 

	// holds the number of ships that are currently correctly placed on the board
	int placedShips = 0;

    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(c->event);
        clunky_eec_update(eec, c->event, c->window);

        if (c->event->num_input != 0){
            //print any keypresses and check for any SDL specific events
            //(such as SDL_QUIT)
            for(k = 0; k < c->event->num_input; k++){
                printf(">>%c\n", c->event->input[k]);

                //all user keypressed are represented by either a number or
                //a capital letter. lowercase letters I've reserved for
                //SDL events
                //'q' -> SDL_QUIT
                if (c->event->input[k] == 'q') cont = 0;
            }
        }
		// see if a ship has been dropped outside the bounds of the board
		if (eec->sum.event_type == 'D'){
			printf("DROP!\n");
			int indx = clunky_indx_from_uid(eec->sum.uid_one, eec);
   			int shipGid = eec->elements[indx]->gid;	
			if (shipPlaced[shipGid]) {
				placedShips--;
				shipPlaced[shipGid] = 0;
				shipPos[shipGid][0] = -1;
				shipPos[shipGid][1] = -1;
			}
		}
        else if (eec->sum.event_type == 'S'){
            printf("SNAP!\n");
            int indx = clunky_indx_from_uid(eec->sum.uid_one, eec);
            int length = eec->elements[indx]->name[1]-'0';
            int offset = eec->elements[indx]->name[0]-'0';
			int shipGid = eec->elements[indx]->gid; 
			printf("event elem row: %d\n", eec->elements[indx]->row);		
			printf("event elem gid: %d\n", shipGid);
            indx = clunky_indx_from_uid(eec->sum.uid_two, eec);
            int cellnum = eec->elements[indx]->name[0]-'0';
            printf("$$%d, %d, %d\n", length, offset, cellnum);

			// find the 0 offset element of the ship and determine if ship is on board
			int onBoard = 1;
			int cellRow = cellnum / c->board_size;
			int cellCol = cellnum % c->board_size;
			printf("cellRow: %d, cellCol: %d\n", cellRow, cellCol);
			// 0 offset is bottommost	
			if (orientation[shipGid] == 3) {
				cellCol = cellCol - offset;
				if (cellCol < 0) {
					onBoard = 0;
				}
				else {
					onBoard = (cellCol + length <= c->board_size);
				}
			}
			// 0 offset is leftmost
			else if (orientation[shipGid] == 0) {
				cellRow = cellRow - offset;
				if (cellRow < 0) {
					onBoard = 0;
				}
				else {
					onBoard = (cellRow + length <= c->board_size);
				}
			}
			// 0 offset is topmost
			else if (orientation[shipGid] == 1) {
				cellCol = cellCol + offset;
				if (cellCol >= c->board_size) {
					onBoard = 0;
				}
				else {
					onBoard = (cellCol - length >= -1);
				}
			}
			// 0 offset is rightmost
			else {
				cellRow = cellRow + offset;	
				if (cellRow >= c->board_size) {
					onBoard = 0;
				}
				else {
					onBoard = (cellRow - length >= -1);	
				}
			}

			// the ship was placed within the bounds of the board
			if (onBoard) {
				if (!shipPlaced[shipGid]) {
					placedShips++;
					shipPlaced[shipGid] = 1;	
				}
				shipPos[shipGid][0] = cellRow;
				shipPos[shipGid][1] = cellCol;
			}
			// the ship was not placed within the bounds of the board
			else {
				if (shipPlaced[shipGid]) {
					placedShips--;
					shipPlaced[shipGid] = 0;
					shipPos[shipGid][0] = -1;
					shipPos[shipGid][1] = -1;
				}	
			}
		}
        else if (eec->sum.event_type == 'C'){
            if (eec->sum.eid_one == clunky_hash_gen("start\0")){
				// only start the game if all the ships are placed correctly
				printf("Placed ships: %d\n", placedShips);
				if (placedShips == c->num_ships) {
					// ensure there is no overlap of any ships on the board
					int noOverlap = 1;				

					// build up the board, but stop if there is any overlap
					for (int i = 0; i < c->num_ships; i++) {
						int zeroOffRow = shipPos[i][0];
						int zeroOffCol = shipPos[i][1];

						// set as the event element sprite row for each offset

						// ship oriented with 0 offset as bottommost
						if (orientation[i] == 3) {
							for (int j = 0; j < shipSizes[i]; j++) {
								// ensure the grid space isn't already occupied
								if (boardGrid[zeroOffRow][zeroOffCol + j] == -1) {
									boardGrid[zeroOffRow][zeroOffCol + j] = ships[i][j]->row;
								}
								// the space was already occupied, so the game cannot be started
								else {
									printf("Overlap at %d, %d\n", zeroOffRow, zeroOffCol + j);
									noOverlap = 0;
									break;
								}							
							}
						}
						// ship oriented with 0 offset as leftmost
						else if (orientation[i] == 0) {
							for (int j = 0; j < shipSizes[i]; j++) {
								// ensure the grid space isn't already occupied
								if (boardGrid[zeroOffRow + j][zeroOffCol] == -1) {
									boardGrid[zeroOffRow + j][zeroOffCol] = ships[i][j]->row;
								}
								// the space was already occupied, so the game cannot be started
								else {
									noOverlap = 0;
									break;
								}							
							}
						}
						// ship oriented with 0 offset as topmost
						else if (orientation[i] == 1) {
							for (int j = 0; j < shipSizes[i]; j++) {
								// ensure the grid space isn't already occupied
								if (boardGrid[zeroOffRow][zeroOffCol - j] == -1) {
									boardGrid[zeroOffRow][zeroOffCol - j] = ships[i][j]->row;
								}
								// the space was already occupied, so the game cannot be started
								else {
									noOverlap = 0;
									break;
								}							
							}
						}
						// ship oriented with 0 offset as rightmost
						else {
							for (int j = 0; j < shipSizes[i]; j++) {
								// ensure the grid space isn't already occupied
								if (boardGrid[zeroOffRow - j][zeroOffCol] == -1) {
									boardGrid[zeroOffRow - j][zeroOffCol] = ships[i][j]->row;
								}
								// the space was already occupied, so the game cannot be started
								else {
									noOverlap = 0;
									break;
								}							
							}
						}			

						if (!noOverlap) {
							break;
						}
					}					


					// only start the game if there is no overlap of any ships
					if (noOverlap) {
						cont = 0;
					}
					// restart the boardGrid to all -1
					else {
						for (int i = 0; i < c->board_size; i++) {
							for (int j = 0; j < c->board_size; j++) {
								boardGrid[i][j] = -1;
							}
						}
					}
                }		
            }
        }
        //Update the window!
        clunky_present_window(c->window);
    }

	// free the memory for the ships array (holding the ships event elements. The ship event
	// elements themselves do not need to be freed here (they are managed by the eec)
	free(ships);
	ships = NULL;
	// free the orientation array
	free(orientation);
	orientation = NULL;	
	// free memory allocated for the ship positions	
	for (int i = 0; i < c->num_ships; i++) {
		free(shipPos[i]);
		shipPos[i] = NULL;
	}
	free(shipPos);
	shipPos = NULL;
	// free memory that was used for ship placements
	free(shipPlaced);
	shipPlaced = NULL;


	//********************
	// we want to return the positions of the ship on the board, but it's commented out
	// until we can properly deal with it in our main function. The function that takes in the
	// boardGrid will also need to handle freeing its memory
	//********************

	// return boardGrid;
    for (int i = 0; i < c->board_size; i++){
        for (int j = 0; j < c->board_size; j++){
            c->player_board[i][j] = boardGrid[i][j];
        }
        free(boardGrid[i]);
    }
    free(boardGrid);

    return 0;
}

int cell_selector(struct BSCore *c){

  int cont = 1;
  int sel_indx = -1;
  int ready = 0;
  while(cont){
      //====================================
      //Aim Selector Screen
      //====================================
      //
      

      //if a cell is selected, animate the fire button
      if (ready) c->fire->effect = 'A';
      else c->fire->effect = 'N';

        //render the normal board and elements
      for (int i = 0; i < c->eec->num_ele; i++){
          //now render the element to the window
          clunky_element_render(c->eec->elements[i], c->window);
      }
      render(c);
      clunky_event(c->event);
      clunky_eec_update(c->selector, c->event, c->window);

      //render the curser
      clunky_render_sprite(c->event->mx - c->cur->ap_w/2, c->event->my - c->cur->ap_h/2, 0, 0, c->cur, c->window);

      if (c->event->num_input != 0){
          //print any keypresses and check for any SDL specific events
          //(such as SDL_QUIT)
          for(int k = 0; k < c->event->num_input; k++){
              printf(">>%c\n", c->event->input[k]);

              //all user keypressed are represented by either a number or
              //a capital letter. lowercase letters I've reserved for
              //SDL events
              //'q' -> SDL_QUIT
              if (c->event->input[k] == 'q') cont = 0;
              }
      }


      if (c->selector->sum.event_type != 'N'){
          //check for a button click
          if (c->selector->sum.event_type == 'C'){
//                        indx = clunky_indx_from_eid(move_eec->sum.eid_one, move_eec);
              if (c->selector->sum.eid_one == clunky_hash_gen("aim\0")){
                  break;
              }
              else if (c->selector->sum.eid_one == clunky_hash_gen("fire\0")){
                  if (ready){
                      printf("FIRE!\n");
                      //set the ignore flag and change the row
                      //get the row & col
                      int row = sel_indx% c->board_size;
                      int col = sel_indx / c->board_size;
                        //incriment the turn counter
                        c->turnCnter++;
                        //attack the ai
                        move(col, row,c);
                        //if there is a win conditon, quit
                        if (checkForWin(c)) return 0;
                        //have the AI attack the player
                        attack_ai(c);

                        //if there is a win conditon, quit
                        if (checkForWin(c)) return 0;



                      //break
                      break;
                  }
              }
              else if (c->selector->sum.eid_one == clunky_hash_gen("CW\0")){
                    rotate(c, 1);
              }
              else if (c->selector->sum.eid_one == clunky_hash_gen("CCW\0")){
                    rotate(c, -1);
              }
              else{
                  //this should be a selection cell
                  //set all cells that have been revliusly selected, back to unselected
                  //for (int j = 0; j < c->board_size * c->board_size; j++){
                  //    if (cells[j]->row == 1) cells[j]->row = 0;
                 // }
                  //get the index
                  sel_indx = c->selector->elements[clunky_indx_from_uid(c->selector->sum.uid_one, c->selector)]->name[0] - '0';
              }
          }
      }
        ready = 0;
      //render the selection grid
      int cell_cnt = 0;
      for (int i = 0; i < c->board_size; i++){
        for (int j = 0; j < c->board_size; j++){
            //if sel_indx == -1, dont render anything special
            //if ai_pins != -1 render the NULL (row = 2)
            //if ai_pins == -1: render flash
            if(c->ai_pins[i][j] != -1){
                clunky_render_sprite(BOARD_OFFSET_W + i * c->cell->ap_w, BOARD_OFFSET_H + j * c->cell->ap_h, 2, 0, c->cell, c->window);
            }
            else{
                if (cell_cnt == sel_indx){
                    clunky_render_sprite(BOARD_OFFSET_W + i * c->cell->ap_w, BOARD_OFFSET_H + j * c->cell->ap_h, 1, c->window->animation_counter % 2, c->cell, c->window);
                    ready = 1;
                }
                else{
                    clunky_render_sprite(BOARD_OFFSET_W + i * c->cell->ap_w, BOARD_OFFSET_H + j * c->cell->ap_h, 0, c->window->animation_counter % 2, c->cell, c->window);
                }
            }
            cell_cnt++;
        }
    }
            


      //Update the window!
      clunky_present_window(c->window);
  }

  return 1;

}

int bsRun(struct BSCore *c){

      struct Clunky_Texture *pp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/PlanningPin.bmp", pp_tex, c->window);
      struct Clunky_Sprite *pp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(1, 1, pp_tex, pp_spr);
      clunky_sprite_scale(c->board_scale, pp_spr);

      //missed pin
      struct Clunky_Texture *mp_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/Pins.bmp", mp_tex, c->window);
      struct Clunky_Sprite *mp_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(2, 1, mp_tex, mp_spr);
      clunky_sprite_scale(c->board_scale, mp_spr);

      //need to create the selector sprite sheets
      struct Clunky_Texture *sel_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/Selector.bmp", sel_tex, c->window);
      struct Clunky_Sprite *sel_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(3, 2, sel_tex, sel_spr);
      clunky_sprite_scale(c->board_scale, sel_spr);

      //aim button element
      struct Clunky_Texture *buttonAT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/AimButton.bmp", buttonAT, c->window);
      struct Clunky_Sprite *buttonA  = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(2, 2, buttonAT, buttonA);
      struct Clunky_Event_Element **aim = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
      *aim = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
      clunky_element_init(*aim, buttonA, 144, 436, 1, "aim\0", 'B', 'N');
      (*aim)->misc = 1;

      //fire button element
      struct Clunky_Texture *buttonFT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/FireButton.bmp", buttonFT, c->window);
      struct Clunky_Sprite *buttonF = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
      clunky_init_sprite(2, 2, buttonFT, buttonF);
      struct Clunky_Event_Element **fire = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
      *fire = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
      clunky_element_init(*fire, buttonF, 20, 436, 1, "fire\0", 'B', 'N');

      // pause button element
	  struct Clunky_Texture *buttonPT = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/PauseButton.bmp", buttonPT, c->window);
      struct Clunky_Sprite *buttonP = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));;
      clunky_init_sprite(1, 2, buttonPT, buttonP);
      struct Clunky_Event_Element **pause = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
      *pause = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
      clunky_element_init(*pause, buttonP, 100, 100, 0, "pause\0", 'B', 'N');


      //the aim cursor
      struct Clunky_Texture *cur_tex = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
      clunky_load_texture("./clunky_assets/Crosshairs.bmp", cur_tex, c->window);
      struct Clunky_Sprite *cur_spr = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));
      clunky_init_sprite(1, 1, cur_tex, cur_spr);


      //create our text elements
      struct Clunky_Text *plyr_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 + 700, 10, 200, 100, 1., c->window);
      clunky_replace_text(plyr_txt, "YOUR SHIPS\0");
      struct Clunky_Text *ai_txt = clunky_get_text((WINDOW_WIDTH - 550)/2 +175, 10, 200, 100, 1., c->window);
      clunky_replace_text(ai_txt, "ENEMY SHIPS\0");


      // Run game loop
          int cont = 1, k;
          int sel_indx = -1;
          while(cont){
              //first thing: check to see if there have been any new events!
              clunky_event(c->event);
              clunky_eec_update(c->eec, c->event, c->window);

              clunky_render_text(plyr_txt, c->window);
              clunky_render_text(ai_txt, c->window);

              render(c);

              if (c->event->num_input != 0){
                  //print any keypresses and check for any SDL specific events
                  //(such as SDL_QUIT)
                  for(k = 0; k < c->event->num_input; k++){
                      printf(">>%c\n", c->event->input[k]);

                      //all user keypressed are represented by either a number or
                      //a capital letter. lowercase letters I've reserved for
                      //SDL events
                      //'q' -> SDL_QUIT
                      if (c->event->input[k] == 'q') cont = 0;
                  }
              }

              //check for any eec events
              if (c->eec->sum.event_type != 'N'){
                  //check for a button click
                  printf("EVENT TYPE: %c\n", c->eec->sum.event_type);
                  if (c->eec->sum.event_type == 'C'){
                      //check to see if it was the Planning Pin buttong
                      if (c->eec->sum.eid_one == clunky_hash_gen("plan\0")){
                          //spawn in a new planning pin
                          struct Clunky_Event_Element **pin = (struct Clunky_Event_Element **) malloc (sizeof(struct Clunky_Event_Element *));
                          *pin = (struct Clunky_Event_Element *) malloc (sizeof(struct Clunky_Event_Element));
                          clunky_element_init(*pin, pp_spr, 60 - (pp_spr->ap_w /2), 500 - (pp_spr->ap_h / 2), 0, "frame\0", 'D', 'N');
                          (*pin)->misc = 1;
                          clunky_event_element_update_z(*pin, 5, c->eec);
                          clunky_eec_add_elements(c->eec, pin, 1);
                      }
                      else if (c->eec->sum.eid_one == clunky_hash_gen("aim\0")){
                            cont = cell_selector(c);
                      }
                      else if (c->eec->sum.eid_one == clunky_hash_gen("CW\0")){
                            rotate(c, 1);
                      }
                      else if (c->eec->sum.eid_one == clunky_hash_gen("CCW\0")){
                            rotate(c, -1);
                      }
					  else if (c->eec->sum.eid_one == clunky_hash_gen("pause\0")){
						printf("Pause button clicked\n");
						int pauseVal = getPauseSelection(c->window, c->event); 
						// 1 indicates game restart, 2 indicates exit game
						if (pauseVal == 1 || pauseVal == 2) {
							return pauseVal;
						}
					}
                  }
                  else if (c->eec->sum.event_type == 'S'){
                      printf("SNAP!\n");
                      if (c->eec->sum.eid_two == clunky_hash_gen("remPlan\0")){
                          //delete the planning pin
                          //
                          int indx = clunky_indx_from_uid(c->eec->sum.uid_one, c->eec);
                          clunky_eec_remove(indx, c->eec);
                     }

                  }
              }

              //Update the window!
              clunky_present_window(c->window);
          }
          endCard(c);
    return 2;
}
