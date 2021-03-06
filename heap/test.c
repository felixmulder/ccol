#include "binary_heap.h"

#include <stdio.h>

void test_create_del();
void test_insert_one();
void test_insert_many();
void test_peek_poll();
void test_heap_sort();
void test_add_heap();

int silly_comp(void *elem, void *other)
{
        return *(int *)elem - *(int *)other;
}

int main(void)
{
        test_create_del();
        test_insert_one();
        test_insert_many();
        test_peek_poll();
        test_heap_sort();
        test_add_heap();
        printf("----------------\nall tests passed\n----------------\n");
        return 0;
}

void test_create_del()
{
        bheap_t *heap = create_heap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr, "<%s:%d>\tFailed in creating heap\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        free_heap(heap);
        printf("passed %s\n",__func__);
}

void test_insert_one()
{
        bheap_t *heap = create_heap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        int *elem = malloc(sizeof(int));
        *elem = 1;
        heap = add_elem(elem, heap);

        if(*(int *)heap->elems[0] != 1) {
                fprintf(stderr,
                        "<%s:%d>\tWrong elem, expected \"%d\", found \"%d\"\n",
                        __func__,__LINE__,
                        1, *(int *)heap->elems[0]);
                exit(1);
        }

        free_heap(heap);
        printf("passed %s\n",__func__);
}

void test_insert_many()
{
        bheap_t *heap = create_heap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        for (int i = 1; i <= 32; i++) {
                int *elem = malloc(sizeof(int));
                *elem = i;
                heap = add_elem(elem, heap);
        }

        int *largest = malloc(sizeof(int));
        *largest = 33;
        heap = add_elem(largest, heap);

        if (*(int *)heap->elems[0] != 33) {
                fprintf(stderr,
                        "Expected \"%d\", found \"%d\"\n",
                        33, *(int *)heap->elems[0]);
                exit(1);
        }

        free_heap(heap);
        printf("passed %s\n",__func__);
}

void test_peek_poll()
{
        bheap_t *heap = create_heap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        for (int i = 1; i <= 32; i++) {
                int *elem = malloc(sizeof(int));
                *elem = i;
                heap = add_elem(elem, heap);
        }

        int *largest = malloc(sizeof(int));
        *largest = 33;
        heap = add_elem(largest, heap);

        if(*(int *)peek_root(heap) != 33) {
                fprintf(stderr,
                        "<%s:%d>\tOMG, Cannot believe this failed seriously.\n",
                        __func__,__LINE__);
                exit(1);
        }


        int root = *(int *)poll_root(heap);
        if(root != 33) {
                fprintf(stderr,
                        "<%s:%d>\tWrong value of root, expected \"%d\", found \"%d\"\n",
                        __func__,
                        __LINE__,
                        33,
                        root);
                exit(1);
        }


        free_heap(heap);
        printf("passed %s\n",__func__);
}

void test_heap_sort()
{
        bheap_t *heap = create_heap(silly_comp, 16);
        if (!heap) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }


        for (int i = 1; i <= 32; i++) {
                int *elem = malloc(sizeof(int));
                *elem = i;
                heap = add_elem(elem, heap);
        }

        for (int i = 32; i > 0; i--) {
                int elem = *(int *)poll_root(heap);
                if (elem != i) {
                        fprintf(stderr,
                                "<%s:%d>\tExpected \"%d\", found \"%d\"\n",
                                __func__,__LINE__,i,elem);
                        exit(1);
                }
        }

        free_heap(heap);
        printf("passed %s\n",__func__);
}

void test_add_heap()
{
        bheap_t *src    = create_heap(silly_comp, 16);
        bheap_t *dest   = create_heap(silly_comp, 16);
        if (!src || !dest) {
                fprintf(stderr,
                        "Couldn't create heap in %s:%d\n",
                        __func__,
                        __LINE__);
                exit(1);
        }

        for (int i = 1; i <= 20; i++) {
                int *e1 = malloc(sizeof(int));
                int *e2 = malloc(sizeof(int));
                *e1 = i;
                *e2 = i+20;
                src     = add_elem(e1, src);
                dest    = add_elem(e2, dest);
        }

        dest = add_heap(src, dest);

        if (dest->index != 40)
                fprintf(stderr,
                        "<%s:%d>\t Expected size of heap %d, actual: %zu\n",
                        __func__,__LINE__, 40, dest->index);

        for (int i = 40; i > 0; i--) {
                int elem = *(int *)poll_root(dest);
                if (elem != i) {
                        fprintf(stderr,
                                "<%s:%d>\tExpected \"%d\", found \"%d\"\n",
                                __func__,__LINE__,i,elem);
                        exit(1);
                }
        }

        printf("passed %s\n",__func__);
}

