#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"

/* This silly hash function takes an int pointer */
int stupid_hash(void *elem)
{
        int e = *((int *)elem);
        return 5741 * e;
}

int stupid_comp(void *key, void *other) {
        return *((int *)key) == *((int *)other);
}

int main(void)
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        int elem = 1;
        if (map) {
                printf("not NULL!\n");
                printf("hash function: %d\n", map->hash_func(&elem));
                printf("insert elem (non-zero == sucess): %d\n",
                       put_elem(&elem,&elem,map));
                printf("find elem 1: %d\n", *(int *)get_elem(&elem, map));
        } else
                printf("null :(\n");

        return 0;
}
