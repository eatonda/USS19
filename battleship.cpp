// Main File for the game

#include "menu_functions/getGameParameters.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;

int main(int argc, char *argv[]) {
    printf("starting battleship.cpp\n");

    // initialize window to render game to
    struct Clunky_Window window;
    struct Clunky_Event event;

    printf("1\n");

    clunky_init(&window, &event, WINDOW_WIDTH, WINDOW_HEIGHT);

    printf("1\n");
    
    /* Game parameters needing to be intitialized */
    int numOfShips = -1;
    int boardSize = -1;     // Square board thus w = h
    int colorScheme = -1;   // Color scheme is either 0(light) or 1(dark)

    printf("1\n");

    //Now we will load the texture that contains all of our main menu buttons
    struct Clunky_Texture water_tex;
    clunky_load_texture("./clunky_assets/Water.bmp", &water_tex, &window);

    printf("1\n");

    struct Clunky_Texture pp;
    int px = -100, py = -100;
    clunky_load_texture("./clunky_assets/cross.bmp", &pp, &window);

    //From the trexture we can create a sprite. 
    //Clunky Sprites allow for the rendering of partial sections of
    //the texture, instead of the entire texture at once
    struct Clunky_Sprite water_spr;
    //when initing a sprite, we need to give it how many ROWS and COLUMNS there
    //are on the sprite sheet. it will do the rest
    clunky_init_sprite(1, 5, &water_tex, &water_spr);

    printf("2\n");

    water_spr.sprite_row = 0;
    water_spr.sprite_column = -1;
    
    printf("starting get params\n");
    fflush(stdin);

    if (getGameParameters(&window, &event, &boardSize, &numOfShips, &colorScheme)) {
        
        /* Trace Statement showing instantiated parameters */
        std::cout << " Parameters Instantiated via getGameParameters()\n";
        std::cout << "numOfShips: " << numOfShips << std::endl;
        std::cout << "Square boardSize: " << boardSize << std::endl;
        std::cout << "colorScheme 0(light) or 1(dark): " << colorScheme << std::endl;
        
        
        
        // Instantiate game objects
        

        // Run game loop
        int cont = 1, k;
        while(cont){
            //first thing: check to see if there have been any new events!
            clunky_event(&event);

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

            if (event.lc == 1){
                printf("(%d, %d)\n", event.mx, event.my);

                px = event.mx;
                py = event.my;
            }

            for (int i = 0; i < boardSize*16; i += 16){
                for (int j = 0; j < boardSize*16; j += 16){
                    clunky_animate_sprite(100 + i, 100 + j, &water_spr, &window);
                }
            }   

            clunky_render_texture(px, py, &pp, &window);

            //Update the window!
            clunky_present_window(&window);
        }
    }
    
}
