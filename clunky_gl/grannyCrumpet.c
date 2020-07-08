#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>

#include "clunkyCore.h"
#include "clunkyHash.h"
#include "clunkyAdvEvents.h"


int main( int argc, char* args[] ) {


	struct Clunky_Window window;
	struct Clunky_Event event;

	clunky_init(&window, 640, 480);

	struct Clunky_Texture bt;
	clunky_load_texture("./buttons.bmp\0", &bt, &window);

	struct Clunky_Sprite sprite;

	clunky_init_sprite(1, 2, &bt, &sprite);
	sprite.sprite_row = 0;
	sprite.sprite_column = -1;


    struct Clunky_Button button;
    unsigned long bid = clunky_button_init(&button, &sprite, 100, 200, "foo");
    printf("%ld\n", bid);
   

    int k;
    int cont = 1;
	while(cont){
        clunky_event(&event);
        if (event.num_input != 0 || event.lc || event.rc){
            printf("(%d, %d) %d %d\n", event.mx,event.my, event.lc, event.rc);
            for(k = 0; k < event.num_input; k++){
                printf(">>%c\n", event.input[k]);
                if (event.input[k] == 'q') cont = 0;
            }
        }

        if (bid == clunky_button_check(&button, 1, &event)){
            printf("CLICKED THE BUTTON\n");
        }

		clunky_render_sprite(button.x, button.y, 0, 0, button.s, &window);

		clunky_present_window(&window);
		clunky_update_renderer(&window);

        SDL_Delay(10);
    }


	

	//Quit SDL subsystems
	SDL_Quit();

	return 0;

}

