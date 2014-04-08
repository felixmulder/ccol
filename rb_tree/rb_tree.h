#pragma once

#include <stdlib.h>
#include <stdio.h>

#define RED   (1)
#define BLACK (0)

typedef struct node_t node_t;
struct node_t {
        unsigned char color;
        node_t *parent;
        node_t *left;
        node_t *right;
        void *elem;
};

/* Create a tree containing a single node */
node_t *rb_tree_create(void *);

/* Insert node into tree */
void rb_tree_insert(void *, node_t *, int (*comp_func)(void *, void *));

/* Returns the size of the (sub) tree starting from the supplied node
 * Params:      root
 * Returns:     number of nodes in tree
 */
int rb_tree_size(node_t *);
