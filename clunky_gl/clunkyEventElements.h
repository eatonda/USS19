#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYEVENTELEMENTS_H
#define CLUNKYEVENTELEMENTS_H

struct Clunky_Movement_Group{
    int calling_uid;
    int gx;
    int gy;
    int num_ele;
};

struct Clunky_Event_Summary{

    char *str;
    int str_len;
    int str_used;
    int collect_string;

    unsigned long eid_one;
    unsigned long eid_two;

    int uid_one;
    int uid_two;
    char event_type;

};

//Idea: have a handler for all of the clunky specific event objects (buttons, etc)
//that are rendered to the screen and interacted with the mouse or keyboard
struct Clunky_Event_Element_Container{

    struct Clunky_Event_Element **elements;
    int len_ele;
    int num_ele;

    struct Clunky_Event_Element **snaps;
    int num_snaps;
    int len_snaps;

    int uid_mstr;

    struct Clunky_Movement_Group groups[16];
    int num_groups;

    struct Clunky_Event_Summary sum;

};

struct Clunky_Event_Element{
    struct  Clunky_Sprite *s;


    char type; //what type of element we have: 
                //[B]utton
                //[T]extbox
                //[D]raggable
                //[S]nap-To

    char effect; //what type of cosmetic effect to add to the element's 
                //rendering
                //[T]oggle
                //[N]othing / regular
                //[A]nimate
                //[H]over
                //[R] -> Hover + Toggle

    unsigned long eid;
    int uid;
    char name[256];
    int x;
    int y;

    //the z coordinate for use with rendering on top of other sprites
    //and for selecting only the top element
    int z;
    int z_init;

    int w;
    int h;

    int interact; // 0: No, 1: Hover, 2: Clicked
    int misc; //a misc variable to be used differently depending on the type
              //of element. EX: draging status
    int ignore; 

    int row;
    int col_max;

    int gid;
    int gx_off;
    int gy_off;

};

//clunky event elements
unsigned long clunky_element_init(struct Clunky_Event_Element *b, struct Clunky_Sprite *s, int x, int y, int row, const char *b_name, char type, char effect);

int clunky_element_render(struct Clunky_Event_Element *b, struct Clunky_Window *w);

//Make some helper functions to simplify the element creation proccess
struct Clunky_Event_Element *clunky_standard_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);
struct Clunky_Event_Element *clunky_toggle_button_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);
struct Clunky_Event_Element *clunky_dragable_element_init(struct Clunky_Sprite *s, int x, int y, int row, const char *e_name);
int clunky_event_element_update_z(struct Clunky_Event_Element *ele, int z, struct Clunky_Event_Element_Container *eec);

//clunky event element container
int clunky_eec_init(struct Clunky_Event_Element_Container *eec);
int clunky_eec_add_elements(struct Clunky_Event_Element_Container *eec, struct Clunky_Event_Element **ele, int num_ele);
int clunky_eec_update(struct Clunky_Event_Element_Container *eec, struct Clunky_Event *e, struct Clunky_Window *w);
int clunky_eec_grow(struct Clunky_Event_Element_Container *eec);
int clunky_eec_free(struct Clunky_Event_Element_Container *eec);
int clunky_eec_remove(int indx, struct Clunky_Event_Element_Container *eec);
int clunky_eec_mergesort(struct Clunky_Event_Element_Container *eec);
int helper_eec_mergesort(struct Clunky_Event_Element **arr, int l, int r);
int helper_eec_text_grow(struct Clunky_Event_Summary *sum);
int clunky_capture_text(struct Clunky_Event_Summary *sum, struct Clunky_Event *e);
int clunky_clear_text(struct Clunky_Event_Summary *sum);
int clunky_indx_from_uid(int uid, struct Clunky_Event_Element_Container *eec);

//EEC groups functions
int clunky_create_group(int x, int y, struct Clunky_Event_Element_Container *eec); //allocates space, returns GID
int eec_addto_group(struct Clunky_Event_Element *ele, int gid, int x_off, int y_off, struct Clunky_Event_Element_Container *eec);
int eec_update_group(struct Clunky_Event_Element *ele,struct Clunky_Event_Element_Container *eec);
int group_element_update(struct Clunky_Event_Element *ele,struct Clunky_Event_Element_Container *eec);

#endif
