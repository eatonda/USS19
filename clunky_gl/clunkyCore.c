#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "clunkyCore.h"


int clunky_event(struct Clunky_Event *event){
	//check to see how many, and what type, of events have occured since the last time we checked
	//set the number of inputs to zero
	event->num_input = 0;
    event->lc = 0;
    event->rc = 0;

	//now we loop for all events
	while(SDL_PollEvent(&(event->e)) && event->num_input < 25){
		if (event->e.type == SDL_QUIT){
			event->input[event->num_input++] = 'q';
		}
        else if (event->e.type == SDL_KEYDOWN){
            //user has pressed a key
            //figure out which key it is
            //first check to see if it was the spacebar
            if (event->e.key.keysym.sym == SDLK_SPACE) event->input[event->num_input++] = ' ';

            //now check to see if it was alpha-numeric
            //we do this by seeing if [1] == '\0', indicitive that its a single
            //character key name
            if (SDL_GetKeyName(event->e.key.keysym.sym)[1] == '\0'){
                event->input[event->num_input++] = SDL_GetKeyName(event->e.key.keysym.sym)[0];
            }
        }
        else if (event->e.type == SDL_MOUSEMOTION){
            //get the new mouse position
            event->mx = event->e.motion.x;
            event->my = event->e.motion.y;
        }
        else if (event->e.type == SDL_MOUSEBUTTONDOWN){
            //one of the mouse buttons has been pressed!
            switch ( event->e.button.button){
                case SDL_BUTTON_LEFT:
                    event->lc = 1;
                    event->lcs = 1;
                    break;
                case SDL_BUTTON_RIGHT:
                    event->rc = 1;
                    break;
                default:
                    break;
            }
        }
        else if (event->e.type ==SDL_MOUSEBUTTONUP){
            //one of the mouse buttons is no longer  being pressed!
            if ( event->e.button.button == SDL_BUTTON_LEFT){
                    event->lcs = 0;
            }
        }
	}

	return 0;
}

int clunky_init(struct Clunky_Window *window, struct Clunky_Event *e, int width_p, int height_p){

    printf("+++++====+++++\n");
	//we need to initilizse SDL
	//use SDL's fucntions to do so
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
		//there was an issue setting up the window
		fprintf(stderr, "Issue initing window!\n");
		exit(1);
	}

	
	//now we can init the window
	window->window = NULL;
	window->window = SDL_CreateWindow( "USS-19 Presents: Battleship!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_p, height_p, SDL_WINDOW_SHOWN );

	 //check to see if the window was made properly
	 if (window->window == NULL){
	 	fprintf(stderr, "Uh oh! Window coudlnt be made!\n");
                exit(1);
	}


	//now lets create the rederer
	window->render = NULL;
	window->render = SDL_CreateRenderer( window->window, -1, SDL_RENDERER_ACCELERATED );
    //set the background color to white
    SDL_SetRenderDrawColor(window->render, 255, 255, 255, 255);


	if (window->render == NULL){
		fprintf(stderr, "Uh oh! renderer couldnt be made!\n");
                exit(1);
	}


	 //remember the width and height
	 window->width = width_p;
	 window->height = height_p;

	 //set the animation coutners
	 window->animation_counter = 0;
	 window->sub_counter = 0;

     //set the sustained click to 0
     e->lcs = 0;
    

    //===========================================================
    //create the text texture and sprite
    //first, allocate the memory for the text object, the texture, and the sprite
    //struct Clunky_Texture *texture = (struct Clunky_Texture *) malloc(sizeof(struct Clunky_Texture));
    window->sprite = (struct Clunky_Sprite *) malloc(sizeof(struct Clunky_Sprite));

    //load the alpha-numeric texture
    //clunky_load_texture("./clunky_assets/AlphaNumeric.bmp", texture, window);

    //now convert it into a sprite 
    //7 rows, 6 columns
    clunky_init_sprite(7, 6, "./clunky_assets/AlphaNumeric.bmp", window->sprite, window);
	
	 return 0;
}

int clunky_update_renderer(struct Clunky_Window *window){
	//redner the window, then clear the renderer
	SDL_RenderPresent(window->render);
	SDL_RenderClear(window->render);

	return 0;
}

int clunky_update_window(struct Clunky_Window *window){
	SDL_RenderPresent(window->render);

	if (window->animation_counter >= 4){
		window->animation_counter = 0;
	}
	if (window->sub_counter >= 80){
		window->animation_counter++;
		window->sub_counter = 0;
	}
	else{
		window->sub_counter++;
	}

	return 0;
}

int clunky_present_window(struct Clunky_Window *window){
    clunky_update_window(window);
    clunky_update_renderer(window);

    //incriment the animation counter
    if (window->sub_counter++ >= 25){
        window->sub_counter = 0;
        window->animation_counter++;
    }

    if ( window->animation_counter >= 10 ){
        window->animation_counter = 0;
    }


    SDL_Delay(10);
    return 0;
}

int clunky_load_texture(char *path, struct Clunky_Texture *texture, struct Clunky_Window *window){
	//alright, lets see how to do this
	//Load image into a surface, then convert the surface into a texture
	SDL_Surface* loadedSurface = SDL_LoadBMP( path );
	if( loadedSurface == NULL ){
		fprintf(stderr, "Uh oh! could load image: %s\n", path);
		exit(1);
	}
	
	//now convert that surface into a texture
	texture->texture = NULL;
	texture->texture = SDL_CreateTextureFromSurface( window->render, loadedSurface );
	
	if(texture->texture == NULL){
		fprintf(stderr, "Uh oh! couldnt convert surface to texture! %s\n", path);
		exit(1);
	}

	SDL_FreeSurface( loadedSurface );

	//get the dimensions of the texture
	SDL_QueryTexture(texture->texture, NULL, NULL, &(texture->width), &(texture->height));

	//create the rendering rectangle
	texture->render_area.w = texture->width;
	texture->render_area.h = texture->height;	
	texture->render_area.x = 0;
	texture->render_area.y = 0;
	texture->scale = 1.0;
	
	return 0;
}

int clunky_render_texture(int x, int y, struct Clunky_Texture *texture, struct Clunky_Window *window){
	texture->render_area.x = x;
	texture->render_area.y = y;
	texture->render_area.w = texture->render_area.w * texture->scale;
	texture->render_area.h = texture->render_area.h * texture->scale;

	SDL_RenderCopy(window->render, texture->texture, NULL, &(texture->render_area));

	return 0;
}


int clunky_free_texture(struct Clunky_Texture *texture){
	//free the texture memory
	SDL_DestroyTexture(texture->texture);
	texture->texture = NULL;
	
	//set the width/height to 0 
	texture->width = 0;
	texture->height = 0;
	texture->scale = 1;;

	return 0;
}

int clunky_init_sprite(int rows, int cols, char *path, struct Clunky_Sprite *sprite, struct Clunky_Window *window){
     //alright, lets see how to do this
    //Load image into a surface, then convert the surface into a texture
    SDL_Surface* loadedSurface = SDL_LoadBMP( path );
    if( loadedSurface == NULL ){
        fprintf(stderr, "Uh oh! could load image: %s\n", path);
        exit(1);
    }

    //now convert that surface into a texture
    sprite->texture = NULL;
    sprite->texture = SDL_CreateTextureFromSurface( window->render, loadedSurface );

    if(sprite->texture == NULL){
        fprintf(stderr, "Uh oh! couldnt convert surface to texture! %s\n", path);
        exit(1);
    }

    SDL_FreeSurface( loadedSurface );


    int w, h;
    //get the dimensions of the texture
    SDL_QueryTexture(sprite->texture, NULL, NULL, &(w), &(h));

    sprite->render_area.w = w;
    sprite->render_area.h = h;
    sprite->render_area.x = 0;
    sprite->render_area.y = 0;

	//setup the sprite rendering rect
	sprite->cell.x = 0;
	sprite->cell.y = 0;
	sprite->cell.w = w/cols;
	sprite->cell.h = h/rows;

    sprite->max_row = rows;
    sprite->max_col = cols;

    sprite->w = sprite->cell.w;
    sprite->h = sprite->cell.h;
    sprite->ap_w = sprite->cell.w;
    sprite->ap_h = sprite->cell.h;
    sprite->scale = 1.;

	return 0;
}

int clunky_render_sprite(int x, int y, int row, int col, struct Clunky_Sprite *sprite, struct Clunky_Window *window){
	//first, we need to verify that the specified row/column fits within the texture!
	if (col > sprite->max_col){
		//uh oh! we are running out of the sprite sheet!
		fprintf(stderr, "Sprite render out of bounds! column: %d\n", col);
		return -1;
	}
	else if (row > sprite->max_row){
		//uh oh! we are running out of the sprite sheet!
                fprintf(stderr, "Sprite render out of bounds! row: %d\n", row);
                return -1;
	}

	//set up the source rect
	sprite->cell.x = col * sprite->cell.w;
	sprite->cell.y = row *sprite->cell.h;
	//now we need to set up the destination rect
	sprite->render_area.x = x;
    sprite->render_area.y = y;
    sprite->render_area.w = sprite->ap_w;
    sprite->render_area.h = sprite->ap_h;

        //now we can finally render
    SDL_RenderCopy(window->render, sprite->texture, &(sprite->cell), &(sprite->render_area));

	return 0;
}

int clunky_animate_sprite(int x, int y, struct Clunky_Sprite *sprite, struct Clunky_Window *window){
	//check to see if the sprite desired animation or not
	if (sprite->sprite_column >= 0){
		//we arent animating the sprite, 
		//render using designated col value
		clunky_render_sprite(x, y, sprite->sprite_row, sprite->sprite_column, sprite, window);
	}
	else{
		//render using the windows' animation counter
		clunky_render_sprite(x, y, sprite->sprite_row, window->animation_counter, sprite, window);
	}

	return 0;
}

int clunky_entity_init(int UID, int width, int height, int solid, int flamible, int interactable, struct Clunky_Sprite *sprite, struct Clunky_Entity *entity){
	//just initilize the entity
	//honestly this only exists so i can one-line create entities
	
	entity->UID = UID;
	entity->interactable = interactable;
	entity->x = 0;
	entity->y = 0;
	entity->delta_x = 0;
	entity->delta_y = 0;
	entity->solid = solid;
	entity->flamible = flamible;
	entity->sprite = sprite;

	entity->hb = (struct Clunky_HitBox *)malloc(sizeof(struct Clunky_HitBox));
	clunky_hitbox_init(width, height, 0, 0, 0, entity->hb);

	return 0;
}

int clunky_entity_free(struct Clunky_Entity *entity){
	//just free the sprite memory
	free(entity->sprite);
	 return 0 ;
}

int clunky_hitbox_init(int width, int height, int slope, int x_offset, int y_offset, struct Clunky_HitBox *hb){
	hb->width = width;
	hb->height = height;
	hb->slope = slope;
	hb->x_offset = x_offset;
	hb->y_offset = y_offset;

	return 0;
}

int clunky_collision_core(struct Clunky_Entity *check, struct Clunky_Entity *mate, int *dir){
	//a simple subroutine program to do the X Y overlap checks
	//first we check to see if they overlap in the X direction
                        if ( (check->x + check->hb->width) >= mate->x && check->x <= (mate->x + mate->hb->width) ){
				//alright, lets quickly populate the direction array
				//make sure there is proper Y overlap
				if (check->y <= (mate->y + mate->hb->height) && (check->y + check->hb->height) >= mate->y){
					if (  (check->x + check->hb->width) == mate->x && dir != NULL){
						//hitting on the east side of check
						//[N, E, S, W]
						dir[1] = 1;
					}
					else if ( check->x <= (mate->x + mate->hb->width) && dir != NULL){
						//hitting on the west side
						dir[3] = 1;
					}
				}

				//we now know that there is overlap in the x direction, 
				//we can now check the y
				if (check->y == (mate->y + mate->hb->height) ){
					//ok, we know that check is touching the bottom of mate
					//thus, the object is falling
					//set the DIR array
					if (dir != NULL) dir[0] = 1;
					//return -1 -> collision, but can fall
					return -1;
				}
				else if ( (check->y + check->hb->height) == mate->y ){
					//check is resting ontop of mate
					if (dir != NULL) dir[2] = 1;
					//return 1 -> collision, cannot fall
					return 1;
				}
			}

			//if all else, the entities arent touching
			//return 0 -> no collisions, can fall
			return 0;
}
				


int clunky_entity_collision(struct Clunky_Entity *check, struct Clunky_Entity **bucket, int length, int *dir){
	//return negitive (can fall), 0 (no collions), positive (cant fall)
	//number returned = number of collisions
	//alrighty, we just need to loop and check against all entities in the bucket
	//first, we can check for the trivial solution: length of one (the check entity is
	//the only entity in the bucket)
	if (length <= 1){
		//if there are no entities to check
		return 1;
	}

	//reset the direction array, if applicable
        if (dir != NULL){
                for (int i = 0; i < 4; i++){
                        dir[i] = 0;
                }
        }

	//now we need to loop through all of the other entities in the bucket
	//we also t=need to comapare UIDs to make sure we dont cross-check an entity
	//with itself
	int count = 0;
	int fall = -1;
	for (int i = 0; i < length; i++){
		//first, check to make sure the UIDs dont match, if they match, skip it
		if(check->UID != (bucket[i])->UID){
			//we are looking at two different entitites, 
			//we can now check for a collision
			//if theres a collision: count++
			//if you can fall: fall=-1
			int collision_test = clunky_collision_core(check, bucket[i], dir);
			//if we have a collsiion (+- 1), incriment the coutner
			if (collision_test != 0){
				count++;
			}
			//if something will prohibit us from falling, make falling false
			if (collision_test > 0){
				fall = 1;
			}

		}
	}

	return fall*count;
}



int clunky_entity_update_positions(struct Clunky_Entity **bucket, int length){
	//alright alright alrught alright!
	//we need to:
	//loop through each entity
	//run clunky_collision core
	//check to see if we can move in the direction we wish
	//if we can, move by one, decriment delta, check next entity
	//repeat until no deltas remain
	
	if (length <= 1){
                //if there are no entities to check
                return 1;
        }

	//reset all of the fall flags
	for (int i = 0; i < length; i++){
		(bucket[i])->falling = 0;
	}

	int dir[4];
	int cont = 1;

	while(cont){
		cont = 0;

		for (int i = 0; i < length; i++){
			//alright, now we check entity 'i'
			clunky_entity_collision(bucket[i], bucket, length, dir);
			
			//check to see if we need to fall
			//south
			if (dir[2]){
				//ok, we cannot fall
				//and we cannot move downward
				//stop moving downward if we are
				if ((bucket[i])->delta_y > 0){
					(bucket[i])->delta_y = 0;
				}
			}
			//check to see if we need to have the entity fall
			//only if they are designated immobile
			else if((bucket[i])->immobile == 0){
				//ok, we can fall
				//check to see if we're already falling
				if ((bucket[i])->falling){
					//ok, we know we are falling, and we CAN fall
					//if we still have delta, and the delta is positive, 
					//move the entity
					if ((bucket[i])->delta_y > 0){
						//incriment y position
						(bucket[i])->y++;
					}
				}
				else{
					//ok, so we need to fall
					//but we FIRST MUST MAKE SURE that the player isnt 
					//already moving upwards! (negitive delta y)
					if ((bucket[i])->delta_y <= 0){
						//ok, we arent moving up, we need to fall now
						//for now, lets just move by one pixle
						(bucket[i])->falling = 1;
						(bucket[i])->y++;
						cont = 1;
					}
				}
			}
			else if ((bucket[i])->delta_y > 0){
				//even if we are immobile, the entitiy wants to move
				(bucket[i])->delta_y--;
				(bucket[i])->y++;
				cont = 1;
			}

			//now lets check the north side
			if (dir[0]){
				//alright, we cannot move upwards
				//if we have a delta_y thats negitive (moving northwards) set it to zero
				if ((bucket[i])->delta_y < 0){
					(bucket[i])->delta_y = 0;
				}
			}
			else{
				//ok, we can move upwards
				//check to see if delta_y < 0
				//if so, move the entity up one pixle (--)
				if ((bucket[i])->delta_y < 0){
					(bucket[i])->y--;
					(bucket[i])->delta_y++;
					cont = 1;
				}
			}

			//west
			if (dir[3]){
				//alright, we cannot move westwards
				//check to see if we had westward (negitive) delta_x
				if((bucket[i])->delta_x < 0){
					(bucket[i])->delta_x = 0;
				}
			}
			else{
				//ok, we can move westwards
				//move the entity and decriment delta
				//(if applicable)
				if((bucket[i])->delta_x < 0){
					(bucket[i])->delta_x++;
					(bucket[i])->x--;
					cont = 1;
				}
			}

			//east
			if (dir[1]){
				//we cannot move eastward
				//if we had eastward movment, cancle it
				if((bucket[i])->delta_x > 0){
					(bucket[i])->delta_x = 0;
				}
			}
			else{
				//we can move!
				if((bucket[i])->delta_x > 0){
					(bucket[i])->delta_x--;
					(bucket[i])->x++;
					cont = 1;
				}
			}
		}
	}

	return 0;
}

struct Clunky_Text *clunky_get_text(int x, int y, int w, int h, float scale, struct Clunky_Window *win){
    //first, allocate the memory for the text object
    struct Clunky_Text *txt = (struct Clunky_Text *) malloc(sizeof(struct Clunky_Text));

    //copy the sprite addr from the window
    txt->s = win->sprite;

    //set the x, y, w, h, and scale values
    txt->x = x;
    txt->y = y;
    txt->w = w;
    txt->h = h;
    txt->scale = scale;

    //initilize 32 characters for the string
    txt->str = (char*) malloc (sizeof(char) * 32);
    
    //initilize an equal ammount of memory for the str_row/col arrays
    //these arrays are used to stro the cell row/column to construct the string, so the math
    //doesnt need to be done each time the text is rendered
    txt->str_row = (int *) malloc (sizeof(int) * 32);
    txt->str_col = (int *) malloc (sizeof(int) * 32);

    txt->str_len = 32;
    txt->str_used = 0;

    //return the text object
    return txt;
}

int clunky_text_free(struct Clunky_Text *txt){
    //free all of the dynamic memory allocated towards this specific text object
    free(txt->str);
    free(txt->str_row);
    free(txt->str_col);

    //note we dont need to free the sprite since it belongs to the window
    return 0;
}

int clunky_text_grow(struct Clunky_Text *txt){
    //double the size of the str_* arrays
    txt->str_len *= 2;

    //we need a temporary hold for the character array
    char *hold_arr = txt->str;

    //free the str_col/row memory
    free(txt->str_row);
    free(txt->str_col);

    //re-allocate memory
    txt->str = (char*) malloc (sizeof(char) * txt->str_len);
    txt->str_row = (int *) malloc (sizeof(int) * txt->str_len);
    txt->str_col = (int *) malloc (sizeof(int) * txt->str_len);

    //copy over the character string
    for (int i = 0; i < txt->str_used; i++) txt->str[i] = hold_arr[i];

    //free the old character array
    free(hold_arr);

    return 0;
}

int clunky_replace_text(struct Clunky_Text *txt, const char *new_str){
    int i;
    for (i = 0; new_str[i] != '\0'; i++){
        txt->str[i] = new_str[i];

        if ( i >= txt->str_len) clunky_text_grow(txt);
    }

    txt->str_used = i;

    clunky_str_to_int(txt);

    return 0;
}

int clunky_add_text(struct Clunky_Text *txt, const char *new_str){
     int i;
    for (i = 0; new_str[i] != '\0'; i++){
        txt->str[txt->str_used++] = new_str[i];

        if ( (txt->str_used) >= txt->str_len) clunky_text_grow(txt);
    }


    clunky_str_to_int(txt);

    return 0;
}

int clunky_remove_text(struct Clunky_Text *txt, int cnt){
    if ((txt->str_used - cnt) < 0) txt->str_used = 0;
    else txt->str_used -= cnt;

    return 0;
}

int clunky_str_to_int(struct Clunky_Text *txt){
    //convert the character string into an array of row and column numbers
    //Order of cells: 0-9, A-Z, . ! ? : ( ) 
    //7 rows, 6 columns
    //0-9: 48-57
    //A-Z: 65-90  (note the capitals!)
    //Space: 32
    //.:46
    //!:33
    //?:63
    //::58
    //(:40
    //):41
    
    //Lowest Ascii value: Space, 32

    int i, cell;
    for (i = 0; i < txt->str_used; i++){
        if (txt->str[i] >= 48 && txt->str[i] <= 57){
           //we have a value between 0 and 9
           //the digits are directly mapped to their cell number
           cell = txt->str[i] - 48;
        }
        else if (txt->str[i] >= 65 && txt->str[i] <= 90){
           //we have a value between A-Z
           //these digits are mapped to their cell number + 10
           cell = txt->str[i] - 65 + 10;
        }
        else{
            //now we are dealing with individual characters
            //use a switch statement
            switch (txt->str[i] - 32){
                case 0:
                    //space
                    //ID with -1
                    cell = -1;
                    break;
                case 46-32:
                    //.
                    //cell 37
                    cell = 36;
                    break;
                case 33-32:
                    //!
                    //cell 38
                    cell = 37;
                    break;
                case 63-32:
                    //?
                    //cell 39
                    cell = 38;
                    break;
                case 58 - 32:
                    //:
                    //cell 40
                    cell = 39;
                    break;
                case 40-32:
                    //(
                    //cell 41
                    cell = 40;
                    break;
                case 41-32:
                    //)
                    //cell 42
                    cell = 41;
                    break;
                default:
                    //unsupported character
                    cell = -2;
                    break;
            }
        }

        //now convert the cell to row/column
        txt->str_row[i] = cell/6;
        txt->str_col[i] = cell%6;
    }


    return 0;
}

int clunky_render_text(struct Clunky_Text *txt, struct Clunky_Window *w){
    int i, w_offset, h_offset;

    //scale the sprite
    clunky_sprite_scale(txt->scale, txt->s);

    for (i = 0; i < txt->str_used; i++){
        //calculate where to put the character in the defined region
        w_offset = (txt->s->ap_w * i) % txt->w;
        h_offset = (txt->s->ap_w * i) / txt->w;

        //if the row/col is >= 0, then render it to the screen
        if (txt->str_row[i] >= 0 && txt->str_col[i] >= 0){
            clunky_render_sprite((txt->x + w_offset), txt->y + txt->s->ap_h * (1 +  h_offset), txt->str_row[i], txt->str_col[i], txt->s, w);
        }
    }

    return 0;
}

int clunky_sprite_scale(float scale, struct Clunky_Sprite *sprite){
    //update the scale, width, and height of the sprite
    sprite->scale = scale;
    sprite->ap_w = sprite->w * scale;
    sprite->ap_h = sprite->h * scale;

    return 0;
}




