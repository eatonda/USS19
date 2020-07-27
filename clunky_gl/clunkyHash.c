#include <stdlib.h>
#include <stdio.h>
#include "clunkyHash.h"

unsigned long clunky_hash_gen(const char *key){
        //convert the key string into the indicy
        //mathamaticle plan: 
        //loop through the entire string
        //multiply the total by a large prime (we'll use 97)
        //for each character, add its ascii-value to the total
        // 
        // I'm using this tutorial as an example:
        // https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%2528CategoryAlgorithmNotes%2529


        unsigned long total = 0;
        const char *pntr;

        for (pntr = (const char *) key; *pntr; pntr++){
                total = total*97 + *pntr;
        }

        return total;
}

int clunky_hash_grow(struct Clunky_Hash *table){
        //first, we need to have a temporary pointer to hold the memory of the initial table
        struct Clunky_Hash *hold = table;

        //now, we need to reallocate memory to hold the bigger table
        //growth factor of 2 -> doubling
        table = (struct Clunky_Hash *)malloc((table->size) * (table->length) * 2);

        //now we need to copy over all of the old data into the new table
        for ( int i = 0; i < table->length; i++){
                //insert the old data into the new table
               // clunky_hash_input(hold->table[i], table);
	       (table->table)[i] = (hold->table)[i];
        }
	for ( int i = table->length; i < (table->length*2); i++){
		table->table[i] = NULL;
	}

        //now we can get rid of the old data
        clunky_hash_free(hold);

        //need to amke srue we note the new size
	table->length = table->length * 2;

	//now we are done!
        return 0;
}

int clunky_hash_input(void *data, const char *key, struct Clunky_Hash *table){
        //we need to insert the new data
        //first, we need to get the index via hashing
        unsigned long hash = clunky_hash_gen(key);

        //now we need to convert it to a index vida modulo
        int index = hash % (table->length);

        //now we can add!
        //we should probably check to make sure its NULL first
        if ( table->table[index] == NULL ){
                table->table[index] = data;
                table->used++;
        }
        else{
                fprintf(stderr, "ERROR HASHING! COMPETING INDEX\n");
                exit(1);
        }

        //now we need to check to make shure we dont need to grow the table
        if ( table->used >= table->length ){
                //time to increase the table!
                clunky_hash_grow(table);
        }

        //i think thats it
        return 0;
}

void *clunky_hash_get(char *key, struct Clunky_Hash *table){
	//need to return the element at the key
	//first, we need to get the index via hasing
	unsigned long hash = clunky_hash_gen(key);
	int index = hash % table->length;

	//return the address of the element
	return table->table[index];
}

int clunky_hash_delete(char *key, struct Clunky_Hash *table){
	//just delete the information held at the index key
	//get the hash
	unsigned long hash = clunky_hash_gen(key);
	int index = hash % table->length;

	//just overwrite the data
	table->table[index] = NULL;
	return 0;
}

int clunky_hash_free(struct Clunky_Hash *table){
	//free the entire chunk of memory
	//reset all fo the variables
	table->length = 0;
	table->size = 0;
	table->used = 0;

	free(table->table);
	return 0;
}

int clunky_hash_init(struct Clunky_Hash *table, int mem_size){
	//initilize the memory
	//first check to make sure that memsize > 0
	if (mem_size <= 0){
		fprintf(stderr, "Uh oh! non valide sizeof for hash init!\n");
		exit(1);
	}

	table->length = 1024;
	table->size = mem_size;
	table->used = 0;

	table->table = (void **)malloc(1024*mem_size);
	
	//set all the mem to NULL
	for (int i = 0; i < 1024; i++){
		table->table[i] = NULL;
	}

	return 0;
}

int clunky_spacial_init(struct Clunky_Spacial_Map *map, int mem_size, int length){
	//we need to allocate all of the dynamic memory.
	//we will initally allocate 256x64 buckets (x/y)
	//we can dynamicly grow them if we exceed our range
	map->width = 256;
	map->height = 64;

	//the length is the size of the bucket in tersm of pixles (square)
	map->length = length;

	//the size of the memory held in the buckets
	map->size = mem_size;

	//dunamicly allocate the x direction memory
	map->map = (struct Clunky_Spacial_Bucket **) malloc(sizeof(struct Clunky_Spacial_Bucket *) * map->width);

	//now allocate the Y direction memory (the actual buckets)
	for (int i = 0; i < map->width; i++){
		map->map[i] = (struct Clunky_Spacial_Bucket *) malloc(sizeof(struct Clunky_Spacial_Bucket) * map->height);
		//now we need to initilize each bucket
		for (int j = 0; j < map->height; j++){
				//allocate 128 spots in the bucket at first. this can be grown if needed
				map->map[i][j].length = 128;
				map->map[i][j].num_used = 0;
				map->map[i][j].bucket = (void **)malloc(map->size * 128);
		}
	}

	return 0;
}

int clunky_spacial_grow_map(struct Clunky_Spacial_Map *map){
    printf("GROWING SPACIAL MAP\n");
    //this function is to grow the the map, increasing the number of buckets. It doesnt affect the size of the buckets
	//make a temporary pointer to the old memory
	struct Clunky_Spacial_Bucket **hold = map->map;
	
	//now we need to allocate the new memory -> double
	map->map = (struct Clunky_Spacial_Bucket **) malloc(sizeof(struct Clunky_Spacial_Bucket *) * map->width * 2);

	//now that the memory is allocated, we must copy over all of the old values, and init
	//all of the new ones
	for (int i = 0; i < map->width; i++){
		map->map[i] = hold[i];
	}
	for (int i = map->width; i < (map->width * 2); i++){
		map->map[i] = (struct Clunky_Spacial_Bucket *) malloc(sizeof(struct Clunky_Spacial_Bucket) * map->height * 2);
                //now we need to initilize each bucket
                for (int j = 0; j < (map->height * 2); j++){
                                //allocate 128 spots in the bucket at first. this can be grown if needed
                                map->map[i][j].length = 128;
                                map->map[i][j].num_used = 0;
                                map->map[i][j].bucket = (void **)malloc(map->size * 128);
                }
	}

//WE DONT WANT TO FREE THE HOLD MEMORY, SINCE THE HOLD MEMORY IS THE SAME MEMORY AS MAP
//WE ARENT COPYING DATA, JUST SHARING POINTERS

	//now we can free the old memory
//	for(int i = 0; i < map->width; i++){
//		for (int j = 0; j < map->height; j++){
//			free(hold[i][j].bucket);
//		}
//		free(hold[i]);
//	}
//	free(hold);
	
	//take noew of the new dimensions
	map->width = map->width * 2;
	map->height = map->height * 2;

	return 0;
}

int clunky_spacial_grow_bucket(struct Clunky_Spacial_Bucket *bucket, int mem_size){
	//this function will dynamicly grow a single bucket
	struct Clunky_Spacial_Bucket *hold = bucket;

	//allocate the new memeory
	bucket->bucket = (void **)malloc(mem_size * bucket->length * 2);

	//transfer over all of the old memory
	for (int i = 0; i < bucket->length; i++){
		bucket->bucket[i] = hold->bucket[i];
	}

	//take note of the new length
	bucket->length = bucket->length * 2;

	return 0;
}

int clunky_spacial_free(struct Clunky_Spacial_Map *map){
	//free ALL of the memory!
	for(int i = 0; i < map->width; i++){
        	for (int j = 0; j < map->height; j++){
                      free(map->map[i][j].bucket);
              	}
	        free(map->map[i]);
        }
    //    free(map);	

	return 0;
}

int clunky_spacial_reset(struct Clunky_Spacial_Map *map){
	//reset all of the buckets so they can be re-used
	//this can simply be done by setting the bucket's num_used to 0;
	
	for(int i = 0; i < map->width; i++){
		for(int j = 0; j < map->height; j++){
			map->map[i][j].num_used = 0;
		}
	}

	return 0;
}

int clunky_spacial_get_used(int x, int y, struct Clunky_Spacial_Map *map){
	//will return the length of the bucket used
	//we need to figure out which bucket is being specified from the x/y coords
	//C integer division truncates towards zero
	int x_bucket = x / map->length;
	int y_bucket = y / map->length;

	return map->map[x_bucket][y_bucket].num_used;
}

void **clunky_spacial_get_bucket(int x, int y, struct Clunky_Spacial_Map *map){
	//will return the bucket array
        //we need to figure out which bucket is being specified from the x/y coords
        //C integer division truncates towards zero
        int x_bucket = x / map->length;
        int y_bucket = y / map->length;
 
        return map->map[x_bucket][y_bucket].bucket;
}

int clunky_spacial_insert(int x, int y, struct Clunky_Spacial_Map *map, void *data){
	//insert new data into the map!
	//we need to figure out which bucket is being specified from the x/y coords
        //C integer division truncates towards zero
        int x_bucket = x / map->length;
        int y_bucket = y / map->length;

	//if need be, we need to grow the map and the bucket if we are out of bounds on the map
	//or out of space in the bucket
	//first, if the x/y is out of range, expand!
	if (x >= map->width*map->length || y >= map->height*map->length){
		//grow the map, then recursivly call insert!
		clunky_spacial_grow_map(map);
		clunky_spacial_insert(x, y, map, data);

		return 1;
	}
	else{
		//ok, the map is big enough!
		//now we need to check to see if the bucket is long enough
		if (map->map[x_bucket][y_bucket].length <= map->map[x_bucket][y_bucket].num_used){
			clunky_spacial_grow_bucket(&(map->map[x_bucket][y_bucket]), map->size);
		}

		//now we can safly insert the data

		map->map[x_bucket][y_bucket].bucket[map->map[x_bucket][y_bucket].num_used] = data;

		//incriment the used count
		map->map[x_bucket][y_bucket].num_used++;

		return 0;
	}
}

int clunky_spacial_stitch_used(int x, int y, int w, int h, struct Clunky_Spacial_Map *map){
    //first, we need to get the total ammount of objects in all fo the buckets we need to pull from
    int total = 0;
    int i, j;
    int w_off = w / map->width;
    int h_off = h / map->height;
    for (i = -1*w_off; i <= w_off; i++){
        for (j = -1 * h_off; j <= h_off; j++){
            total += clunky_spacial_get_used(x + i * map->width, y + j * map->height, map);
        }
    }

    printf("$%d, $%d, $%d\n", total, w_off, h_off);

    return total;
}


void **clunky_spacial_stitch_bucket(int x, int y, int w, int h, struct Clunky_Spacial_Map *map){

    return NULL;
}
