#include "hashmap.h"

hashmap_t *create_map(int (*hash_func)(void *),
                      int (*comp_key)(void *,void *),
                      size_t s)
{
        hashmap_t *map = malloc(sizeof(hashmap_t) + s * sizeof(node_t));
        if (map) {
                map->hash_func  = hash_func;
                map->comp_key   = comp_key;
                map->len        = s;
                map->size       = 0;
                map->threshold  = 0.75;
        }
        return map;
}

static void free_node(node_t *node)
{
        free(node->key);
        free(node->val);
        free(node);
}

void free_map(hashmap_t *map)
{
        for (int i = 0; i < map->len; i++) {
                node_t *node = map->nodes[i];
                while(node) {
                        node_t *old = node;
                        node = node->succ;
                        free_node(old);
                }
                map->nodes[i] = NULL;
        }

        free(map);
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
                         old_map->len * 2);
        if (!map) {
                fprintf(stderr, "couldn't allocate memory for rehash\n");
                /* Should return zero value instead? Hmm... */
                exit(1);
        }

        for (int i = 0; i < old_map->len; i++) {
                node_t *node = old_map->nodes[i];
                while (node) {
                        put_elem(node->key, node->val, map);
                        node_t *old = node;
                        node = node->succ;
                        free(old);
                }
        }

        /* Only free old hashmap_t but not the elements contained within */
        free(old_map);
        return map;
}

static int index(void *key, hashmap_t *map)
{
        return map->hash_func(key) % map->len;
}

static node_t *get_node(void *key, hashmap_t *map)
{
        int i = index(key, map);
        node_t *node = map->nodes[i];

        while(node) {
                if (map->comp_key(key, node->key))
                        return node;
                else
                        node = node->succ;
        }

        return NULL;
}

hashmap_t *put_elem(void *key, void *val, hashmap_t *map)
{
        node_t *n = get_node(key, map);

        /* If an element with the same key exists, replace its val */
        if(n) {
                n->val = val;
                return map;
        }

        /* Else create and insert a new node */
        node_t *node = malloc(sizeof(node_t));
        int i = index(key, map);

        if (!node) {
                fprintf(stderr, "could not allocate memory for node\n");
                return map;
        }

        node->key = key;
        node->val = val;
        node->succ = NULL;

        node->succ = map->nodes[i];
        map->nodes[i] = node;
        
        map->size++;
        if (map->size > map->threshold * map->len)
                map = rehash(map);

        return map;
}

hashmap_t *put_map(hashmap_t *src, hashmap_t *dest)
{
        for (int i = 0; i < src->len; i++) {
                node_t *node = src->nodes[i];
                while(node) {
                        dest = put_elem(node->key, node->val, dest);
                        node_t *old = node;
                        node = node->succ;
                        free(old);
                }
                src->nodes[i] = NULL;
        }

        free_map(src);
        return dest;
}

void *get_elem(void *key, hashmap_t *map)
{
        node_t *n = get_node(key, map);

        if(n) return n->val;

        return NULL;
}

void *remove_elem(void *key, hashmap_t *map)
{
        int i = index(key, map);
        node_t *node = map->nodes[i];

        if (map->comp_key(key, node->key)) {
                map->nodes[i] = node->succ;
                void *elem = node->val;
                free(node);
                return elem;
        }
        
        while (node->succ) {
                if (map->comp_key(key, node->succ->key)) {
                        void *elem = node->succ->val;
                        node->succ = node->succ->succ;
                        free_node(node->succ);
                        return elem;
                }
        }

        return NULL;
}
