#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

static void **array;
static int (*hash_func)(void *);

/* Creates a generic hashmap of size s with a hashing function */
void create_map(int (*func)(void *), size_t s);

/* 
 * Inserts an element in the hash map using the previously supplied function.
 * Will return a non-zero value if insert successful
 */ 
int insert_elem(void *);

#endif
