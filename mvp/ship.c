#include "ship.h"
#include <stdio.h>
#include <stdlib.h>

//struct Ship_Assets{

    //struct Clunky_Sprite *sprite;
  //  struct Clunky_Texture *texture;


//};

int init_ship(float scale, struct Ship_Assets *s, struct Clunky_Window *w){

    // s->textureL = (struct Clunky_Texture *) malloc (sizeof(struct Clunky_Texture));
    s->spriteL = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));

    // clunky_load_texture("./clunky_assets/LightShip.bmp", s->textureL, w);
    clunky_init_sprite(10, 1, "./clunky_assets/LightShip.bmp", s->spriteL, w);

    // s->textureD = (struct Clunky_Texture *) malloc (sizeof(struct Clunky_Texture));
    s->spriteD = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));

    // clunky_load_texture("./clunky_assets/DarkShip.bmp", s->textureD, w);
    clunky_init_sprite(10, 1,"./clunky_assets/DarkShip.bmp", s->spriteD, w);

    clunky_sprite_scale(scale, s->spriteD);
    clunky_sprite_scale(scale, s->spriteL);

    return 0;
}

struct Clunky_Event_Element **generate_ship(int length, int color,  struct Clunky_Event_Element_Container *eec, struct Ship_Assets s){
    printf("STARTING SHIP GEN\n");
    //first, if we dont have a length of at least 2, quit
    if (length < 2) return NULL;

    //depending on the color selection chose one of the two sprites in ship assets
    struct Clunky_Sprite *sprite = NULL;

    if (color) sprite = s.spriteL;
    else sprite = s.spriteD;


    struct Clunky_Event_Element **ships = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * length);

    char name[3] = {'0', '0' + length, '\0'};

    //the first and last element are end caps
    ships[0] = clunky_dragable_element_init(sprite, 0, 0, 2, name);//2

    int x, cnt = 1;

    for (x = sprite->ap_w; x < (length-1)*sprite->ap_w; x += sprite->ap_w){
        name[0] += 1;
        ships[cnt++] = clunky_dragable_element_init(sprite, x, 0, 8, name);//8
        
    }

    name[0] += 1;
    ships[length-1] = clunky_dragable_element_init(sprite, x, 0, 4, name);//4

    //make the movement group
    int gid = clunky_create_group(0, 0, eec);
    //add to the eec
    clunky_eec_add_elements(eec,ships, length);
    for (int i = 0; i < length; i++){
        eec_addto_group(ships[i], gid, ships[i]->x, ships[i]->y, eec);
    }

    printf("GENERATED SHIP\n");

    return ships;
}

