#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

btree_node* btree_alloc(BTREE_KEY_TYPE key)
{
    btree_node *newnode = (btree_node*)malloc(sizeof(btree_node));

    newnode->key    = key;
    newnode->parent = NULL;
    newnode->left   = newnode->right = NULL;

    return newnode;
}

void btree_free(btree_node **root)
{
    if (!root || !(*root))
    {
        return;
    }
    
    if ((*root)->left)
    {
        btree_free(&(*root)->left);
    }
    
    if ((*root)->right)
    {
        btree_free(&(*root)->right);
    }
    
    free(*root);
}

btree_node* btree_search(btree_node *root, BTREE_KEY_TYPE key)
{
    if (!root || root->key == key)
    {
        return root;
    }

    while (root && root->key != key)
    {
        if (root->key > key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return root;
}

void btree_print_inorder(btree_node *root)
{
    if (!root)
    {
        return;
    }

    btree_print_inorder(root->left);
    printf(BTREE_KEY_FORMAT" ", root->key);
    btree_print_inorder(root->right);
}

void btree_print_preorder(btree_node *root)
{
    if (!root)
    {
        return;
    }

    printf(BTREE_KEY_FORMAT" ", root->key);
    btree_print_preorder(root->left);
    btree_print_preorder(root->right);
}

void btree_print_postorder(btree_node *root)
{
    if (!root)
    {
        return;
    }

    btree_print_postorder(root->left);
    btree_print_postorder(root->right);
    printf(BTREE_KEY_FORMAT" ", root->key);
}

btree_node* btree_min(btree_node *root)
{
    if (root)
    {
        while (root->left)
        {
            root = root->left;
        }
    }

    return root;
}

btree_node* btree_max(btree_node *root)
{
    if (root)
    {
        while (root->right)
        {
            root = root->right;
        }
    }

    return root;
}

btree_node* btree_successor(btree_node *node)
{
    if (!node)
    {
        return NULL;
    }

    if (node->right)
    {
        return btree_min(node->right);
    }

    btree_node *tmp = node->parent;

    while (tmp && node == tmp->right)
    {
        node = tmp;
        tmp  = tmp->parent;
    }

    return tmp;
}

btree_node* btree_predecessor(btree_node *node)
{
    if (!node)
    {
        return NULL;
    }

    if (node->left)
    {
        return btree_max(node->left);
    }

    btree_node *tmp = node->parent;

    while (tmp && node == tmp->left)
    {
        node = tmp;
        tmp  = tmp->parent;
    }

    return tmp;
}

void btree_insert(btree_node **root, btree_node *newnode)
{
    btree_node *parent  = NULL;
    btree_node *current = *root;

    while (current)
    {
        parent = current;
        if (newnode->key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    newnode->parent = parent;

    if (!parent)
    {
        *root = newnode;
    }
    else if(newnode->key < parent->key)
    {
        parent->left = newnode;
    }
    else
    {
        parent->right = newnode;
    }
}

void btree_transplant(btree_node **root, btree_node *first, btree_node *second)
{
    if (!root || !(*root) || !first)
    {
        return;
    }

    if (!first->parent)
    {
        free(first);
        *root = second;

        return;
    }
    else if (first == first->parent->left)
    {
        first->parent->left = second;
    }
    else
    {
        first->parent->right = second;
    }

    if(second)
    {
        second->parent = first->parent;
    }
}

void btree_delete(btree_node **root, btree_node *node)
{
    if (!root || !(*root) || !node)
    {
        return;
    }

    if (!node->left)
    {
        btree_transplant(root, node, node->right);
    }
    else if (!node->right)
    {
        btree_transplant(root, node, node->left);
    }
    else
    {
        btree_node *tmp = btree_min(node->right);

        if(tmp->parent != node)
        {
            btree_transplant(root, tmp, tmp->right);
            tmp->right         = node->right;
            tmp->right->parent = tmp;
        }

        btree_transplant(root, node, tmp);

        tmp->left         = node->left;
        tmp->left->parent = tmp;
    }
}
