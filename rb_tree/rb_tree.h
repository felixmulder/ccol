#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct node_t node_t;
struct node_t {
        /* Is set to one if red, else black  */
        unsigned int red : 1;
        node_t *left;
        node_t *right;
        void *elem;
};
