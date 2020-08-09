#include <SDL2/SDL.h>

#ifndef CLUNKYCORE_H
#define CLUNKYCORE_H

struct Clunky_Window{
	SDL_Window *window;
	SDL_Renderer *render;
        int width;
        int height;

	int animation_counter;
	int sub_counter;

    struct Clunky_Sprite *sprite;
};

struct Clunky_Event{
        SDL_Event e;

        int num_input;
        //just going to hold the character that was entered, capital letters are going to represtn command keypresses
        char input[5];

        int mx; //mouse x position
        int my; //mouse y position
        int dx; //mouse delta x
        int dy; //mouse delta y

        int lc; //left click
        int lcs; //left click sustained
        int rc; //right click
};

struct Clunky_Texture{
	SDL_Texture *texture;
	SDL_Rect render_area;
	int width;
	int height;
	float scale;
};

struct Clunky_Sprite{
    SDL_Texture *texture;
    SDL_Rect render_area;
	SDL_Rect cell;

    int max_row;
    int max_col;

    float scale;

    //the actual width and height of the sprite cell
    int w;
    int h;

    //the aparent width and height
    int ap_w;
    int ap_h;

	int sprite_row;
	int sprite_column; //if we are using an animated sprite, this value is negitive, oteherwise it specifiese which column to use on the sheet
};

struct Clunky_Text{
    struct Clunky_Sprite *s;

    int x;
    int y;
    int w;
    int h;

    float scale;

    char *str;
    int *str_row; //used to reduce the ammount of proccessing, so we dont
    int *str_col; //need to recalculate the sprite cels at each render
    int str_len;
    int str_used;
};

struct Clunky_HitBox{
	//the course hitbox to check before the fine hitbox
	int width;
	int height;
	//the fine details of the hitbox
	int slope;
	int x_offset;
	int y_offset;
};

struct Clunky_Entity{
	int UID;

	int interactable;

	int x;
	int y;
	int delta_x;
	int delta_y;

	int solid;
	int flamible;

	int falling;
	int immobile;

	struct Clunky_Sprite *sprite;
	struct Clunky_HitBox *hb;

};


//====================
//core functionality
int clunky_event(struct Clunky_Event *event);
int clunky_init(struct Clunky_Window *window, struct Clunky_Event *e, int width_p, int height_p);
int clunky_update_renderer(struct Clunky_Window *window);
int clunky_update_window(struct Clunky_Window *window);
int clunky_present_window(struct Clunky_Window *window);

//=====================
//sprites and textures
int clunky_load_texture(char *path, struct Clunky_Texture *texture, struct Clunky_Window *window);
int clunky_init_sprite(int rows, int cols, char *path, struct Clunky_Sprite *sprite, struct Clunky_Window *window);
int clunky_free_texture(struct Clunky_Texture *texture);
int clunky_render_texture(int x, int y, struct Clunky_Texture *texture, struct Clunky_Window *window);
int clunky_render_sprite(int x, int y, int row, int col, struct Clunky_Sprite *sprite, struct Clunky_Window *window);
int clunky_animate_sprite(int x, int y, struct Clunky_Sprite *sprite, struct Clunky_Window *window);
int clunky_sprite_scale(float scale, struct Clunky_Sprite *sprite);

//====================
//clunky entity
int clunky_entity_init(int UID, int width, int height, int solid, int flamible, int interactable, struct Clunky_Sprite *sprite, struct Clunky_Entity *entity);
int clunky_entity_free(struct Clunky_Entity *entity);
int clunky_hitbox_init(int width, int height, int slope, int x_offset, int y_offset, struct Clunky_HitBox *hb);

//=====================
//collions
int clunky_collision_core(struct Clunky_Entity *check, struct Clunky_Entity *mate, int *dir);
int clunky_entity_collision(struct Clunky_Entity *check, struct Clunky_Entity **bucket, int length, int *dir); //return -1 (no collisions), 0 (cant fall), 1 (can fall)
int clunky_entity_update_positions(struct Clunky_Entity **bucket, int length);

//=====================
//Clunky Text
struct Clunky_Text *clunky_get_text(int x, int y, int w, int h, float scale, Clunky_Window *);
int clunky_text_free(struct Clunky_Text *txt);
int clunky_text_grow(struct Clunky_Text *txt);
int clunky_replace_text(struct Clunky_Text *txt, const char *new_str);
int clunky_add_text(struct Clunky_Text *txt, const char *new_str);
int clunky_remove_text(struct Clunky_Text *txt, int cnt);
int clunky_str_to_int(struct Clunky_Text *txt);
int clunky_render_text(struct Clunky_Text *txt, struct Clunky_Window *w);

#endif
