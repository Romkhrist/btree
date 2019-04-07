#include <stdio.h>
#include <stdlib.h>

#define BTREE_KEY_TYPE   int
#define BTREE_KEY_FORMAT "%d"

typedef struct btree_node
{
    BTREE_KEY_TYPE     key;
    struct btree_node *parent;
    struct btree_node *left;
    struct btree_node *right;
} btree_node;

btree_node* btree_alloc(BTREE_KEY_TYPE key);
void        btree_free(btree_node **root);
btree_node* btree_search(btree_node *root, BTREE_KEY_TYPE key);
void        btree_print_inorder(btree_node *root);
void        btree_print_preorder(btree_node *root);
void        btree_print_postorder(btree_node *root);
btree_node* btree_min(btree_node *root);
btree_node* btree_max(btree_node *root);
btree_node* btree_successor(btree_node *node);
btree_node* btree_predecessor(btree_node *node);
void        btree_insert(btree_node **root, btree_node *newnode);
void        btree_transplant(btree_node **root, btree_node *first, btree_node *second);
void        btree_delete(btree_node **root, btree_node *node);
