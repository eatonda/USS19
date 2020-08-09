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
    clunky_init(&window, &event, 1000, 700);

    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture water_tex;
    clunky_load_texture("./clunky_assets/Water.bmp", &water_tex, &window);

    //From the trexture we can create a sprite. 
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite water_spr;
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(2, 5, &water_tex, &water_spr);

    water_spr.sprite_row = 0;
    water_spr.sprite_column = -1;
//    clunky_sprite_scale(1.75, &water_spr);

    //create a 5x5 board for now
    char names[] = "cell_x_\0";
    int cnt = 0;
    struct Clunky_Event_Element **cells = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * 25);
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            names[4] = '0' + i;
            names[6] = '0' + j;

            cells[cnt] = (struct Clunky_Event_Element *) malloc(sizeof(struct Clunky_Event_Element));

            clunky_element_init(cells[cnt], &water_spr, water_spr.ap_w*i, water_spr.ap_h*j, 0, names, 'B', 'A');

            cnt++;
        }
    }

     //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture pp_tex;
    clunky_load_texture("./clunky_assets/PlanningPin.bmp", &pp_tex, &window);
    struct Clunky_Sprite pp_spr;
    clunky_init_sprite(1, 1, &pp_tex, &pp_spr);

     struct Clunky_Texture p_tex;
    clunky_load_texture("./clunky_assets/Pins.bmp", &p_tex, &window);
    struct Clunky_Sprite p_spr;
    clunky_init_sprite(2, 1, &p_tex, &p_spr);

    struct Clunky_Texture d_tex;
    clunky_load_texture("./clunky_assets/DelPlan.bmp", &d_tex, &window);
    struct Clunky_Sprite d_spr;
    clunky_init_sprite(1, 1, &d_tex, &d_spr);

    struct Clunky_Event_Element *ppd = clunky_dragable_element_init(&pp_spr, 500, 200, 0, "ppd");

    struct Clunky_Event_Element *ele1 = clunky_dragable_element_init(&d_spr, 500, 200, 0, "L");
    struct Clunky_Event_Element *ele2 = clunky_dragable_element_init(&d_spr, 400, 200, 0, "R");

    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);
    printf(">>>>>\n");
    clunky_eec_add_elements(eec, cells, 25);
//    clunky_eec_add_elements(eec, &ppd, 1);    
    clunky_eec_add_elements(eec, &ele1, 1);
    clunky_eec_add_elements(eec, &ele2, 1);
//    clunky_eec_add_elements(eec, &ele3, 1);
    printf("ASASASASAS\n");
    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;



    //attempt at testing grouping
//    int gid = clunky_create_group(500, 200, eec);
//    printf("^^%d\n", gid);
//    eec_addto_group(ele1, gid, 0, 0, eec);
//    eec_addto_group(ele2, gid, -100, 0, eec);
//    eec_addto_group(ele3, gid, -200, 0, eec);


    //create a clunky text object!
    struct Clunky_Text *text = clunky_get_text(10, 10, 512, 64, 0.5, &window);
    printf("HHH\n");
    clunky_replace_text(text, "THIS IS THE BOARD! :)\0");
    printf("CCCC\n");

    int map[5][5];
    for (int j = 0; j < 5; j++){
        for (int k = 0; k < 5; k++){
            map[j][k] = 0;
        }
    }

    int rotation = 0;
    
    map[1][2] = 4;
    map[1][3] = 4;
    map[1][4] = 4;

    int num_hits = 3;
    int ai_hits = 3;

    int ai[5][5];
    char ai_print[5][5];
    for (int j = 0; j < 5; j++){
        for (int k = 0; k < 5; k++){
            ai[j][k] = 0;
            ai_print[j][k] = '_';
        }
    }

    ai[1][2] = 4;
    ai[1][3] = 4;
    ai[1][4] = 4;

    while(cont && num_hits && ai_hits){
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
                if (event.input[k] == '`') printf("##%s\n", eec->sum.str);
            }

        }

        //check the buttons to see if anywhere clicked
        //first, check to make sure that there was a selected button
        if (eec->sum.event_type != 'N'){
            if (eec->sum.event_type == 'C'){
                int indx = clunky_indx_from_uid(eec->sum.uid_one, eec);
                if (eec->elements[indx]->name[0] == 'L'){
                    rotation++;
                    if (rotation > 3) rotation = 0;

                }
                else if (eec->elements[indx]->name[0] == 'R'){
                    rotation--;
                    if (rotation < 0) rotation = 3;

                }
                else{

                    printf("Board is clicked!\n");
                    printf("&&%s\n", eec->elements[indx]->name);

                    int j = eec->elements[indx]->name[4] - '0';
                    int k = eec->elements[indx]->name[6] - '0';
                    //see if its valid
                    if(map[j][k] != 0 && map[j][k] != 4) printf("INVALID MOVE!\n");
                    else if (map[j][k] == 0){
                        map[j][k] = 2;
                    }
                    else if (map[j][k] == 4){
                        map[j][k] = 3;
                        num_hits--;
                    }

                    int q;
                    int w;

                    while(1){
                        q = rand() % 5;
                        w = rand() % 5;
                        if (ai[q][w] == 0){
                            ai_print[q][w] = 'M';
                            ai[q][w] = 1;
                            break;
                        }
                        else if (ai[q][w] == 4){
                            ai_print[q][w] = 'H';
                            ai[q][w] = 1;
                            ai_hits--;
                            break;
                        }
                    }

                    for (int i = 0; i < 5; i++) printf("\n\n");

                    for (int i = 0; i < 5; i++){
                            printf("[%c][%c][%c][%c][%c]\n", ai_print[i][0], ai_print[i][1], ai_print[i][2], ai_print[i][3], ai_print[i][4]);
                    }
                }
                
            }
        }
        
        switch(rotation){
            case 0:
                for (int j = 0; j < 5; j++){
                    for (int k = 0; k < 5; k++){
                        if (map[j][k] == 1){
                            clunky_render_sprite(j*64, k*64, 0, 0, &pp_spr, &window);
                        }
                        else if (map[j][k] == 2){
                            clunky_render_sprite(j*64, k*64, 0, 0, &p_spr, &window);
                        }
                        else if (map[j][k] == 3){
                            clunky_render_sprite(j*64, k*64, 1, 0, &p_spr, &window);
                        }
                    }
                }
                break;
            case 1:
                for (int k = 4; k >= 0; k--){
                    for (int j = 0; j < 5; j++){
                        if (map[j][(4-k)] == 1){
                            clunky_render_sprite(k*64, j*64, 0, 0, &pp_spr, &window);
                        }
                        else if (map[j][(4-k)] == 2){
                            clunky_render_sprite(k*64, j*64, 0, 0, &p_spr, &window);
                        }
                        else if (map[j][(4-k)] == 3){
                            clunky_render_sprite(k*64, j*64, 1, 0, &p_spr, &window);
                        }
                    }
                }
                break;
            case 2:
                for (int j = 4; j >= 0; j--){
                    for (int k = 4; k >= 0; k--){
                        if (map[(4-j)][(4-k)] == 1){
                            clunky_render_sprite(j*64, k*64, 0, 0, &pp_spr, &window);
                        }
                        else if (map[(4-j)][(4-k)] == 2){
                            clunky_render_sprite(j*64, k*64, 0, 0, &p_spr, &window);
                        }
                        else if (map[(4-j)][(4-k)] == 3){
                            clunky_render_sprite(j*64, k*64, 1, 0, &p_spr, &window);
                        }
                    }
                }
                break;
            case 3:
                for (int k = 4; k >= 0; k--){
                        for (int j = 0; j < 5; j++){
                            if (map[(4-k)][j] == 1){
                                clunky_render_sprite(j*64, k*64, 0, 0, &pp_spr, &window);
                            }
                            else if (map[(4-k)][j] == 2){
                                clunky_render_sprite(j*64, k*64, 0, 0, &p_spr, &window);
                            }
                            else if (map[(4-k)][j] == 3){
                                clunky_render_sprite(j*64, k*64, 1, 0, &p_spr, &window);
                            }
                        }
                    }
                break;
        }

        //Update the window!
        clunky_present_window(&window);



    }

    if (num_hits == 0) printf("PLAYER WINS!\n");
    else printf("AI WINS!\n");
    

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

        

            
