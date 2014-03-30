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

        heap->elems[heap->index] = elem;

        /* While parent node is smaller, bubble elem up */
        if (heap->index > 0) {
                size_t  index   = heap->index;
                size_t  pindex  = (heap->index - 1) / 2;
                void    *parent = heap->elems[pindex];

                while (index > 0 && heap->comp_func(parent,elem) < 0) {
                        void *temp = parent;
                        heap->elems[pindex] = elem;
                        heap->elems[index] = temp;
                        
                        index = pindex;
                        pindex = (pindex - 1) / 2;
                        parent = heap->elems[pindex];
                }
        }

        heap->index++;
        return heap;
}

void const *peek_root(bheap_t *heap)
{
        return heap->elems[0];
}

void *poll_root(bheap_t *heap)
{
        if (!heap || heap->index == 0)
                return NULL;
        
        void *elem = heap->elems[0];
        if (heap->index == 1)  {
                heap->index     = 0;
                heap->elems[0]  = NULL;
        } else {
                heap->elems[0] = heap->elems[--heap->index];

                /* Bubble up elements larger than the replaced node */
                size_t index    = 0;
                size_t child    = 1;
                while (child < heap->index) {

                        void *parent_p  = heap->elems[index];
                        void *child_p   = heap->elems[child];

                        if (child + 1 < heap->index &&
                            heap->comp_func(child_p, heap->elems[child+1]) < 0)
                                child++;

                        child_p = heap->elems[child];

                        if (heap->comp_func(parent_p, child_p) < 0) {
                                heap->elems[index] = child_p;
                                heap->elems[child] = parent_p;
                                index = child;
                                child = index * 2 + 1;
                        } else /* Bubble up finished! */
                                break;
                }
        }

        return elem;
}

bheap_t *add_heap(bheap_t *src, bheap_t *dest)
{
        //TODO: Implement...
        fprintf(stderr, "<%s:%d>\tNot yet implemented.\n",__func__,__LINE__);
        exit(1);
        return NULL;
}

void free_bheap(bheap_t *heap)
{
        if (heap->index > 0)
                for (int i = 0; i < heap->index; i++)
                        free(heap->elems[i]);

        free(heap);
}
