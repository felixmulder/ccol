#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t node_t;
struct node_t {
        node_t *succ;
        void *key;
        void *val;
};

typedef struct hashmap_t {
        int (*hash_func)(void *);
        int (*comp_key)(void *, void *);
        size_t len;
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
 * Free the contents of the map
 * Params:      map
 * Post:        all elements pointers in the map will have been freed
 */
void free_map(hashmap_t *);

/* 
 * Inserts an element in the hash map using the previously supplied function.
 * Will return a new pointer to the array, this function should thus always
 * be used in this fashion:
 *      map = put_elem(key, value, map);
 *
 * Params:      key, value, map
 * Returns:     a pointer to the updated map
 * Post:        the map passed as argument should be viewed as invalid (freed),
 *              see usage above
 */ 
hashmap_t *put_elem(void *, void *, hashmap_t *);

/*
 * Concatenate two hash maps, should be used in this fashion:
 *      dest = put_map(src, dest);
 * Params:      src, dest
 * Returns:     a pointer to the concatenated map
 * Post:        only the returned pointer will be valid
 */
hashmap_t *put_map(hashmap_t *, hashmap_t *);

/*
 * Will attempt to fetch an element with the specified key, from the specified
 * map. Returns a void pointer to the value or NULL if the key doesn't exist in
 * the map.
 */
void *get_elem(void *, hashmap_t *);


/*
 * Will attempt to remove the element with the specified key from the supplied
 * hash map. Returns NULL if it fails to remove the specified key.
 */
void *remove_elem(void *, hashmap_t *);

