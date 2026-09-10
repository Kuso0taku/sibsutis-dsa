#ifndef BSTREE_H
#define BSTREE_H
#include <stdint.h>

// binary search tree node
typedef struct bstree {
    char *key;              // string key
    uint32_t value;         // integer value
    struct bstree *left;    // left subtree
    struct bstree *right;   // right subtree
} bstree;

// create root node with given key and value
bstree *bstree_create(char *key, uint32_t value);

// add node (iterative, no recursion), returns root
bstree *bstree_add(bstree *tree, char *key, uint32_t value);

// find node by key, returns node or NULL
bstree *bstree_lookup(bstree *tree, char *key);

// delete node by key (Hibbard), returns new root
bstree *bstree_delete(bstree *tree, char *key);

// return node with minimum key (leftmost)
bstree *bstree_min(bstree *tree);

// return node with maximum key (rightmost)
bstree *bstree_max(bstree *tree);

#endif
