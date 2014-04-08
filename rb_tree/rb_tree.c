#include "rb_tree.h"

/* return the node's grand daddy node */
static node_t *grandparent(node_t *n)
{
        if (n && n->parent)
                return n->parent->parent;
        else
                return NULL;
}

/* find the corresponding "uncle" to the supplied node */
static node_t *uncle(node_t *n)
{
        node_t *g = grandparent(n);
        if (!g)
                return NULL;
        if (n->parent == g->left)
                return g->right;
        else
                return g->left;
}

node_t *rb_tree_create(void *elem)
{
        node_t *r = malloc(sizeof(node_t));
        
        if (r) {
                r->color        = BLACK;
                r->elem         = elem;
                r->parent       = NULL;
                r->left         = NULL;
                r->right        = NULL;
        }

        return r;
}

int rb_tree_size(node_t *r)
{
        if (r)
                return 1 + rb_tree_size(r->left) + rb_tree_size(r->right);

        return 0;
}

void rb_tree_insert(void *elem, node_t *root, int (*comp_func)(void *,void*))
{
       //TODO real implementation
}
