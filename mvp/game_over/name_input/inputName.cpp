#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include "../clunky_gl/clunkyCore.h"
#include "../clunky_gl/clunkyHash.h"
#include "../clunky_gl/clunkyEventElements.h"

String inputName(struct Clunky_Window* window, struct Clunky_Event* event){

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
    clunky_init(&window, &event, 640, 480);


    //now lets declare our Event Element Container (EEC)
    struct Clunky_Event_Element_Container *eec = (struct Clunky_Event_Element_Container *) malloc(sizeof(struct Clunky_Event_Element_Container));

    //init the eec
    clunky_eec_init(eec);

    
    //now we can begin our main loop!
    cont = 1;
    unsigned long bid;

    //Title
    struct Clunky_Text *text1 = clunky_get_text(225, 25, 512, 64, 1., &window);
    clunky_replace_text(text1, "New High Score!\0");
      for (int i = 0; i < text1->str_used; i++){
          printf("%c, (%d, %d)\n", text1->str[i], text1->str_row[i], text1->str_col[i]);
      }
    
    struct Clunky_Text *text2 = clunky_get_text(130, 125, 512, 64, 1., &window);
    clunky_replace_text(text2, "PLEASE ENTER YOUR NAME\0");
    for (int i = 0; i < text2->str_used; i++){
        printf("%c, (%d, %d)\n", text2->str[i], text2->str_row[i], text2->str_col[i]);
    }

    struct Clunky_Text *text3 = clunky_get_text(130, 200, 512, 64, 1., &window);
    clunky_replace_text(text3, "NAME:\0");
    for (int i = 0; i < text3->str_used; i++){
        printf("%c, (%d, %d)\n", text3->str[i], text3->str_row[i], text3->str_col[i]);
    }

    while(cont){
        //first thing: check to see if there have been any new events!
        clunky_event(&event);
        clunky_eec_update(eec, &event, &window);
        clunky_render_text(text1, &window);
        clunky_render_text(text2, &window);
        clunky_render_text(text3, &window);

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

                // Prints input into console
                if (event.input[k] == '`') printf("Name: %s\n", eec->sum.str);
                
                // Enter key pressed
                if (event.input[k] == 'r' ) {
                    printf("Enter was Pressed, returning name");
                    cont = 0;   // Break main loop
                    break;
                }
            }
        }

        char* name = eec->sum.str;

        // Create text
        struct Clunky_Text *text4 = clunky_get_text(225, 200, 512, 64, 1., &window);
        clunky_replace_text(text4, name);

        // Render name to window
        clunky_render_text(text4, &window);

        //Update the window!
        clunky_present_window(&window);
    }

    //Quit SDL subsystems
    //SDL_Quit();
    return name;

    return 0;
}


        

            
