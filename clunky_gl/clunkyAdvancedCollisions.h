#include "clunkyCore.h"
#include "clunkyHash.h"

#ifndef CLUNKYADVANCEDCOLLISIONS_H
#define CLUNKYADVANCEDCOLLISIONS_H

struct Clunky_Entity_Map{
	//we need an array of all activly updated entities
	//we will actually store the entities information IN THIS array
	struct Clunky_Entity *active;
	int num_active;
	int length_active;

	//the spacial map that we will use to store relitive positions
	struct Clunky_Spacial_Map *map;
}




#endif
