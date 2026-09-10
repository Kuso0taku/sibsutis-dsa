#ifndef RBTREE_H
#define RBTREE_H

// red-black tree node
typedef struct rbtree {
    int key;                // integer key
    char *value;            // string value
    char color;             // 'R' (red) or 'B' (black)
    struct rbtree *left;    // left subtree
    struct rbtree *right;   // right subtree
    struct rbtree *parent;  // parent node
} rbtree;

// create root node with given key and value (black)
rbtree *rbtree_create(int key, char *value);

// add node (iterative, with balancing), returns root
rbtree *rbtree_add(rbtree *root, int key, char *value);

// find node by key, returns node or NULL
rbtree *rbtree_lookup(rbtree *root, int key);

// delete node by key, returns root
rbtree *rbtree_delete(rbtree *root, int key);

// return node with minimum key (leftmost)
rbtree *rbtree_min(rbtree *root);

// return node with maximum key (rightmost)
rbtree *rbtree_max(rbtree *root);

// free all nodes (postorder)
void rbtree_free(rbtree *root);

// print tree sideways, right subtree first, level is indentation
void rbtree_print_dfs(rbtree *root, int level);

#endif