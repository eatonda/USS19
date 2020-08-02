#include "ship.h"
#include <stdio.h>
#include <stdlib.h>

//struct Ship_Assets{

    //struct Clunky_Sprite *sprite;
  //  struct Clunky_Texture *texture;


//};

int init_ship(struct Ship_Assets *s, struct Clunky_Window *w){

    s->texture = (struct Clunky_Texture *) malloc (sizeof(struct Clunky_Texture));
    s->sprite = (struct Clunky_Sprite *) malloc (sizeof(struct Clunky_Sprite));

    clunky_load_texture("./clunky_assets/Ships.bmp", s->texture, w);
    clunky_init_sprite(10, 2, s->texture, s->sprite);

    return 0;
}

struct Clunky_Event_Element **generate_ship(int length, int color, struct Clunky_Event_Element_Container *eec, struct Ship_Assets s){
    printf("STARTING SHIP GEN\n");
    //first, if we dont have a length of at least 2, quit
    if (length < 2) return NULL;


    struct Clunky_Event_Element **ships = (struct Clunky_Event_Element **) malloc(sizeof(struct Clunky_Event_Element *) * length);

    //the first and last element are end caps
    ships[0] = clunky_dragable_element_init(s.sprite, 0, 0, 2, "ship\0");//2

    int x, cnt = 1;

    for (x = s.sprite->ap_w; x < (length-1)*s.sprite->ap_w; x += s.sprite->ap_w){
        ships[cnt++] = clunky_dragable_element_init(s.sprite, x, 0, 8, "ship\0");//8
        
    }


    ships[length-1] = clunky_dragable_element_init(s.sprite, x, 0, 4, "ship\0");//4

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

