#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t node_t;
struct node_t {
        node_t *succ;
        void *key;
        void *value;
};

typedef struct hashmap_t {
        int (*hash_func)(void *);
        int (*comp_key)(void *, void *);
        size_t cap;
        size_t size;
        double threshold;
        node_t *nodes[];
} hashmap_t;

/* 
 * Creates a generic hash map of size s with a hashing function
 * Params:
 *      first function, hash function to be used by the map
 *      second function, key comp function, should return non-zero for true
 *      size_t, initial size of hash map
 *
 * Returns: a pointer to a hashmap_t
 */ 
hashmap_t *create_map(int (*)(void *),int (*)(void *,void *), size_t s);

/* 
 * Inserts an element in the hash map using the previously supplied function.
 * Will return a non-zero value if insert successful
 */ 
int put_elem(void *, void *, hashmap_t *);

/*
 * Will attempt to fetch an element with the specified key, from the specified
 * map. Returns a void pointer to the value or NULL if the key doesn't exist in
 * the map.
 */
void *get_elem(void *, hashmap_t *);
