#include "rb_tree.h"

void test_create();
void test_size();

int main(void)
{
        test_create();
        test_size();
        printf("----------\nAll tests passed\n----------\n");
        return 0;
}

static void printe(const char *msg, const char *func, int line)
{
        printf("<%s:%d>\t%s\n", func, line, msg);
}

void test_create()
{
        int *e = malloc(sizeof(int));
        *e = 1337;
        node_t *tree = rb_tree_create(e);

        if(!tree) {
                printe("failed to create tree", __func__, __LINE__);
                exit(1);
        }

        printf("passed %s\n", __func__);
}

void test_insert()
{
        int *e = malloc(sizeof(int));
        *e = 1337;
        node_t *tree = rb_tree_create(e);

        if(!tree) {
                printe("failed to create tree", __func__, __LINE__);
                exit(1);
        }


        //TODO insert_elem here
        
}

void test_size()
{
        printe("not yet implemented", __func__, __LINE__);
        exit(1);
}
