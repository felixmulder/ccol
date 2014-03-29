#include "binary_heap.h"

bheap_t *create_bheap(int (*comp_func)(void *elem, void *other), size_t s)
{
        bheap_t *heap = malloc(sizeof(bheap_t) + sizeof(void *) * s);

        if (!heap) {
                fprintf(stderr,
                        "<%s:%d>\tCould not allocate space for heap.\n",
                        __func__,
                        __LINE__);
        } else {
                heap->size      = s;
                heap->index     = 0;
                heap->comp_func = comp_func;
        }

        return heap;
}

bheap_t *add_elem(void *elem, bheap_t *heap)
{
        if (heap->index >= heap->size) {
                bheap_t *old = heap;
                heap = create_bheap(heap->comp_func, heap->size * 2);

                for (int i = 0; i < old->index; i++)
                        heap->elems[i] = old->elems[i];

                heap->index = old->index;
                free(old);
        }

        //TODO: implement bubble-up
        heap->elems[heap->index++] = elem;

        return heap;
}

int rm_elem(void *elem, bheap_t *heap)
{
        //TODO: Implement this sucker...
        return 0;
}

void free_bheap(bheap_t *heap)
{
        if (heap->index > 0)
                for (int i = 0; i < heap->index; i++)
                        free(heap->elems[i]);

        free(heap);
}
