#include <stdlib.h>
#include <stdio.h>
#include "gameCore.hpp"
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyEventElements.h"
#include "../clunky_gl/clunkyHash.h"
#include "ship.h"
#include "pause_menu/pauseMenu.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int BOARD_OFFSET_W = 250;
const int BOARD_OFFSET_H = 100;



Board::Board(int size, int color, int **ships, struct Clunky_Window *w, struct Clunky_Event *e){

    //make note of the size and color
    this->size = size;
    this->theme = color;

    //And the windowand event addresses
    this->w = w;
    this->e = e;

    //we want to make a copy of the ship array, we dont want to directly take it
    //this will be done in the init function, along with the memory allocation for the EEC
    this->init(ships);

    return;
}

int Board::init(int **ships){
    //first, allocate memory for, and init the eec
    this->eec = (struct Clunky_Event_Element_Container*) malloc(sizeof(struct Clunky_Event_Element_Container));
    clunky_eec_init(this->eec);

    //set the hits and hits to win variables to 0
    this->hits = 0;
    this->hits_to_win = 0;

    //allocate memory for the ships array
    this->ships = (int **) malloc(sizeof(int));

    //copy over the passed ship placement, and finish allocating memory
    for (int i = 0; i < this->size; i++){
        this->ships[i] = (int *) malloc(sizeof(int));

        for (int j = 0; j < this->size; j++){
            //copy over the value
            this->ships[i][j] = ships[i][j];

            //if the value isnt -1 (which is an empty cell) then its a ship part
            //count it in hits to win
            if(ships[i][j] != -1) this->hits_to_win++;
        }
    }

    //Allocate the memory for the Pins array, and set the default value to -1 for all cells
    this->pins = (int **) malloc(sizeof(int));

    //copy over the passed ship placement, and finish allocating memory
    for (int i = 0; i < this->size; i++){
        this->pins[i] = (int *) malloc(sizeof(int));

        for (int j = 0; j < this->size; j++){
            this->pins[i][j] = -1;
        }
    }

    //load the pin texture/init the sprite
    this->pin_spr = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));
    clunky_init_sprite(2, 1, "./clunky_assets/Pins.bmp", this->pin_spr, this->w);

    //allocate the memory for the board sprite
    this->ship_spr = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));

    //load the texture based off of the theme
    if(this->theme){
        clunky_init_sprite(10, 1, "./clunky_assets/DarkShip.bmp", this->pin_spr, this->w);
    }
    else{
        clunky_init_sprite(10, 1, "./clunky_assets/LightShip.bmp", this->pin_spr, this->w);
    }



    //Alright, that should be it for the moment
    return 0;
}

int ship_rotation_helper(int rotation, int row){
    //if the range is between 0 and 3: ship front
    if (row >= 0 && row <= 3){
        //if we have a positive rotation, incriment the row, wrapping back to 0 after 3
        if (roation > 0){
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
        if (roation > 0){
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
    else if (row == 9) return 9;

    //if we got here, we have an invalid row
    return -1;
}

int Board::roate(int dir){
 
    //need temporary hold arrays
    int **pinH = this->pins;
    int **shipH = this->ships;

    //now re-allocate the Ship and Pins arrays
    ////Allocate the memory for the Pins array, and set the default value to -1 for all cells
    this->pins = (int **) malloc(sizeof(int));
    this->ships = (int **) malloc(sizeof(int));

    //copy over the passed ship placement, and finish allocating memory
    for (int i = 0; i < this->size; i++){
        this->pins[i] = (int *) malloc(sizeof(int));

        for (int j = 0; j < this->size; j++){
            this->pins[i][j] = -1;
            this->ships[i][j] = -1;
        }
    }

    
    //rotate the boards
    //if we have a positive roation value, rotate clockwise
    //otherwise anti-clockwise
    if ( rotation > 0){
        //[j][size-k]
        for (int k = this->size; k >= 0; k--){
            for (int j = 0; j < this->size; j++){
                //copy over and rotate the pins
                this->pins[j][k] = pinH[j][this->size-k];

                //copy over and rotate the ship peices
                //Will need to also update the spite row after the rotation
                this->ships[j][k] = ship_rotation_helper(1, shipH[j][this->size-k]);
            }
        }
    }
    else{
        //[size-j][k]
        for (int k = this->size; k >= 0; k--){
            for (int j = 0; j < this->size; j++){
                //copy over and rotate the pins
                this->pins[j][k] = pinH[this->size-j][k];

                //copy over and rotate the ship peices
                //Will need to also update the spite row after the rotation
                this->ships[j][k] = ship_rotation_helper(1, shipH[j][this->size-k]);
            }
        }

    }


    return 0;
}


