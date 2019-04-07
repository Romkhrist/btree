#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

int main ()
{
    btree_node *btree_root = NULL;

    btree_insert(&btree_root, btree_alloc(4));
    btree_insert(&btree_root, btree_alloc(7));
    btree_insert(&btree_root, btree_alloc(3));
    btree_insert(&btree_root, btree_alloc(5));
    btree_insert(&btree_root, btree_alloc(1));
    btree_insert(&btree_root, btree_alloc(3));

    printf("btree_print_inorder(): ");
    btree_print_inorder(btree_root);
    puts("");

    printf("btree_print_preorder(): ");
    btree_print_preorder(btree_root);
    puts("");

    printf("btree_print_postorder(): ");
    btree_print_postorder(btree_root);
    puts("");

    printf("btree_print_inorder()\nafter deletion of 4 and 3: ");
    btree_delete(&btree_root, btree_search(btree_root, 4));
    btree_delete(&btree_root, btree_search(btree_root, 3));
    btree_print_inorder(btree_root);
    puts("");
    
    btree_free(&btree_root);

    return 0;
}
