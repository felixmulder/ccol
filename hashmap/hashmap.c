#include "hashmap.h"

hashmap_t *create_map(int (*hash_func)(void *),
                      int (*comp_key)(void *,void *),
                      size_t s)
{
        hashmap_t *map = malloc(sizeof(hashmap_t) + s * sizeof(node_t));
        if (map) {
                map->hash_func  = hash_func;
                map->comp_key   = comp_key;
                map->cap        = s;
                map->size       = 0;
                map->threshold  = 0.75;
        }
        return map;
}

/*
 * This function will rehash the map, doubling its size and thus the spread
 * of elements in the map
 */
static void *rehash(hashmap_t *map)
{
        hashmap_t *old_map = map;
        map = create_map(old_map->hash_func,
                         old_map->comp_key,
                         old_map->cap * 2);
        if (!map) {
                fprintf(stderr, "couldn't allocate memory for rehash\n");
                /* Should return zero value instead? Hmm... */
                exit(1);
        }

        for (int i = 0; i < map->cap; i++) {
                node_t *node = old_map->nodes[i];
                while (node) {
                        put_elem(node->key, node->value, map);
                        node = node->succ;
                }
        }

        free(old_map);
        return map;
}

hashmap_t *put_elem(void *key, void *value, hashmap_t *map)
{
        int i = map->hash_func(key) % map->cap;

        node_t *node = malloc(sizeof(node_t));

        if (!node) {
                fprintf(stderr, "could not allocate memory for node\n");
                return map;
        }

        node->key = key;
        node->value = value;

        if (!map->nodes[i])
                map->nodes[i] = node;
        else {
                node_t *temp = map->nodes[i];
                while (!temp->succ)
                        temp = temp->succ;
                temp->succ = node;
        }
        
        map->size++;
        if (map->size > map->threshold * map->cap) {
                map = rehash(map);
        }
        return map;
}

void *get_elem(void *key, hashmap_t *map)
{
        int i = map->hash_func(key) % map->cap;
        node_t *node = map->nodes[i];
        while(node) {
                if (map->comp_key(key, node->key))
                        return node->value;
                else
                        node = node->succ;
        }

        return NULL;
}
