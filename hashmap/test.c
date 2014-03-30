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

void test_create_del();
void test_hash();
void test_put();
void test_get();
void test_concat();

int main(void)
{
        test_create_del();
        test_hash();
        test_put();
        test_get();
        test_concat();
        printf("----------------\nall tests passed\n----------------\n");
        return 0;
}


void test_create_del()
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        if (!map) {
                fprintf(stderr,
                        "<%s:%d>\tCould not create map\n",
                        __func__, __LINE__);
                exit(1);
        }

        free_map(map);
        printf("passed %s\n",__func__);
}

void test_hash()
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        if (!map) {
                fprintf(stderr,
                        "<%s:%d>\tCould not create map\n",
                        __func__, __LINE__);
                exit(1);
        }

        int i = 1;
        if (map->hash_func(&i) != stupid_hash(&i)) {
                fprintf(stderr,
                        "<%s:%d>\tSomething wrong with hash function\n",
                        __func__, __LINE__);
                exit(1);
        }

        printf("passed %s\n",__func__);
}

void test_put()
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        if (!map) {
                fprintf(stderr,
                        "<%s:%d>\tCould not create map\n",
                        __func__, __LINE__);
                exit(1);
        }

        for (int i = 1; i <= 16; i++) {
                int *key = malloc(sizeof(int));
                int *val = malloc(sizeof(int));
                *key = i;
                *val = -i;
                map = put_elem(key, val, map);
        }

        
        printf("passed %s\n",__func__);
}

void test_get()
{
        hashmap_t *map = create_map(stupid_hash, stupid_comp, 16);
        if (!map) {
                fprintf(stderr,
                        "<%s:%d>\tCould not create map\n",
                        __func__, __LINE__);
                exit(1);
        }

        for (int i = 1; i <= 16; i++) {
                int *key = malloc(sizeof(int));
                int *val = malloc(sizeof(int));
                *key = i;
                *val = -i;
                map = put_elem(key, val, map);
        }


        for (int i = -4; i <= 16; i++) {
                int *elem = (int *)get_elem(&i, map);
                
                if (i < 1) {
                        if (elem) {
                                fprintf(stderr,
                                        "<%s:%d>\terr, found elem w key: %d\n",
                                        __func__,__LINE__,i);
                                exit(1);
                        }
                        
                }
                else if (!elem) {
                        fprintf(stderr,
                                "<%s:%d\tshould've found elem with key: %d\n",
                                __func__,__LINE__,i);
                        exit(1);

                }
        }

        printf("passed %s\n",__func__);
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

        for (int i = 1; i <=32; i ++) {
                int val = *(int *)get_elem(&i, dest);
                if (!val || val != i) {
                        fprintf(stderr,
                                "<%s:%d>\tCouldn't find elem w key: %d\n",
                                __func__,__LINE__,i);
                        exit(1);
                }
        }

        free_map(dest);
        printf("passed %s\n",__func__);
}
