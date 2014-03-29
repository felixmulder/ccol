#include "binary_heap.h"

#include <stdio.h>

void test_create_del();
void test_insert_one();
void test_insert_many();

int silly_comp(void *elem, void *other)
{
        return *(int *)elem - *(int *)other;
}

int main(void)
{
        test_create_del();
        test_insert_one();
        return 0;
}

void test_create_del()
{
        bheap_t *heap = create_bheap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr, "<%s:%d>\tFailed in creating heap\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        free_bheap(heap);
        printf("passed %s\n",__func__);
}

void test_insert_one()
{
        bheap_t *heap = create_bheap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        int *elem = malloc(sizeof(int));
        *elem = 1;
        add_elem(elem, heap);

        if(*(int *)heap->elems[0] != 1) {
                fprintf(stderr,
                        "<%s:%d>\tWrong elem, expected \"%d\", found \"%d\"\n",
                        __func__,__LINE__,
                        1, *(int *)heap->elems[0]);
                exit(1);
        }

        printf("passed %s\n",__func__);
}

void test_insert_many()
{
        fprintf(stderr, "<%s:%d> Not yet implemented\n",__func__,__LINE__);
        exit(1);
}
