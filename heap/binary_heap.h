#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct bheap_t {
        size_t size;
        size_t index;
        int (*comp_func)(void *, void *);
        void *elems[];
} bheap_t;

/*
 * Creates a binary heap and returns a pointer to the datastructure
 * Params:      takes a function which should be able to compare elements
 *              inserted into the heap. The function __MUST__ return a non-zero
 *              value for all elements that are not considered equal. A zero
 *              value indicates that the elements are the same, this is utilized
 *              in the remove function.
 *
 *              s, initial size
 * Returns:     a pointer to the binary heap
 */
bheap_t *create_bheap(int (*)(void *, void *), size_t);

/*
 * Insert an element into the binary heap
 * Params:      elem, heap
 * Returns:     a pointer to the updated heap, since it potentially allocates
 *              a new array is should thus be used as:
 *              heap = add_elem(elem, heap);
 */
bheap_t *add_elem(void *, bheap_t *);

/*
 * Removes a specified element from the heap.
 * Params:      elem, heap
 * Post:        the elem for which comp_func returns zero is removed
 */
int rm_elem(void *, bheap_t *);

/*
 * Will free the entire heap with all its elements from memory
 * Post:        all pointers into the heap are considered invalid
 */
void free_bheap(bheap_t *);
