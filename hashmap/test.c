#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"

/* An example of a hash function to use with hashmap */
int stupid_hash(void *elem)
{
        int e = *(int *)elem;
        return 5741 * e;
}

/* An example of a comparison function to use with the hashmap */
int stupid_comp(void *key, void *other) {
        return *(int *)key == *(int *)other;
}

hashmap_t *test_create();
void test_hash(hashmap_t *);
hashmap_t *test_put(hashmap_t *);
void test_get(hashmap_t *);
void test_free(hashmap_t *);
void test_concat();

int main(void)
{
        hashmap_t *map = test_create();
        test_hash(map);
        map = test_put(map);
        test_get(map);
        test_free(map);
        test_concat();
        return 0;
}


hashmap_t *test_create()
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        if (!map) {
                fprintf(stderr, "<%s:%d>\tCould not create map\n", __func__, __LINE__);
                exit(1);
        }

        return map;
}

void test_hash(hashmap_t *map)
{
        int i = 1;
        if (map->hash_func(&i) != stupid_hash(&i)) {
                fprintf(stderr, "<%s:%d>\tSomething wrong with hash function\n", __func__, __LINE__);
                exit(1);
        }
}

hashmap_t *test_put(hashmap_t *map)
{

        for (int i = 1; i <= 16; i++) {
                int *key = malloc(sizeof(int));
                int *val = malloc(sizeof(int));
                *key = i;
                *val = -i;
                printf("put_elem(%d,%d,map)\n", *key,*val);
                map = put_elem(key, val, map);
        }

        return map;
}

void test_get(hashmap_t *map)
{
        for (int i = -4; i <= 16; i++) {
                int *elem = (int *)get_elem(&i, map);
                if (elem)
                        printf("found elem %d = %d!\n", i, *elem);
                else
                        printf("couldn't find %d = ?\n", i);
        }
}

void test_concat()
{
        hashmap_t *src  = create_map(stupid_hash, stupid_comp, 16);
        hashmap_t *dest = create_map(stupid_hash, stupid_comp, 16);

        for (int i = 1; i <= 16; i++) {
                int *key = malloc(sizeof(int));
                int *val = malloc(sizeof(int));
                *key = i;
                *val = i;
                src = put_elem(key, val, src);
        }

        for (int i = 17; i <= 32; i++) {
                int *key = malloc(sizeof(int));
                int *val = malloc(sizeof(int));
                *key = i;
                *val = i;
                dest = put_elem(key, val, dest);
        }

        dest = put_map(src, dest);
        printf("managed to concat maps\n");

        for (int i = 1; i <=32; i ++) {
                int val = *(int *)get_elem(&i, dest);
                if (!val || val != i)
                        printf("couldn't find element in concat map\n");
        }

        free_map(dest);
}

void test_free(hashmap_t *map)
{
        free_map(map);
        printf("freed map using free_map function\n");
}
