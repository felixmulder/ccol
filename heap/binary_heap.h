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
bheap_t *create_heap(int (*)(void *, void *), size_t);

/*
 * Insert an element into the binary heap
 * Params:      elem, heap
 * Returns:     a pointer to the updated heap, since it potentially allocates
 *              a new array is should thus be used as:
 *              heap = add_elem(elem, heap);
 */
bheap_t *add_elem(void *, bheap_t *);

/*
 * Removes the root and returns it
 * Params:      heap
 */
void const *peek_root(bheap_t *);

/*
 * Removes and returns the root element of the heap
 * Returns:     root element
 */
void *poll_root(bheap_t *);

/*
 * Adds the elements from src to dest
 * Params:      src, dest
 * Returns:     pointer to concatenated heap, 
 * Post:        the src heap will be freed, all pointers to it should thus be
 *              considered invalid. The dest heap will be freed if the bounds of
 *              its array would have been overwritten by src. Thus a usage such
 *              as this is recommended:
 *
 *              dest = add_heap(src, dest);
 */
bheap_t *add_heap(bheap_t *, bheap_t *);

/*
 * Will free the entire heap with all its elements from memory
 * Post:        all pointers into the heap are considered invalid
 */
void free_heap(bheap_t *);
