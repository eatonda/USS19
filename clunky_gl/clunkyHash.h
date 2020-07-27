#ifndef CLUNKYHASH_H
#define CLUNKYHASH_H

struct Clunky_Hash{
        int length;
        int used;
        int size;
        void **table;
};

struct Clunky_Spacial_Map{
	int width;
	int height;
	int length;

	int size;

	struct Clunky_Spacial_Bucket **map;
};

struct Clunky_Spacial_Bucket{
	int length;

	int num_used;


	void **bucket;
};

unsigned long clunky_hash_gen(const char *key);//
int clunky_hash_input(void *data, const char *key, struct Clunky_Hash *table);//
void *clunky_hash_get(char *key, struct Clunky_Hash *table);//
int clunky_hash_delete(char *key, struct Clunky_Hash *table);//
int clunky_hash_free(struct Clunky_Hash *table);//
int clunky_hash_init(struct Clunky_Hash *table, int mem_size);//
int clunky_hash_grow(struct Clunky_Hash *table);//

int clunky_spacial_init(struct Clunky_Spacial_Map *map, int mem_size, int length);
int clunky_spacial_grow_map(struct Clunky_Spacial_Map *map);
int clunky_spacial_grow_bucket(struct Clunky_Spacial_Bucket *bucket, int mem_size);
int clunky_spacial_free(struct Clunky_Spacial_Map *map);
int clunky_spacial_reset(struct Clunky_Spacial_Map *map);
int clunky_spacial_get_used(int x, int y, struct Clunky_Spacial_Map *map); //will return the length of the bucket used
void **clunky_spacial_get_bucket(int x, int y, struct Clunky_Spacial_Map *map); //will return the array/bucket
int clunky_spacial_stitch_used(int x, int y, int w, int h, struct Clunky_Spacial_Map *map);
void **clunky_spacial_stitch_bucket(int x, int y, int w, int h, struct Clunky_Spacial_Map *map);

int clunky_spacial_insert(int x, int y, struct Clunky_Spacial_Map *map, void *data);


#endif
