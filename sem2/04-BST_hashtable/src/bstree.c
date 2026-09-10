#include <stdlib.h>
#include <string.h>
#include "bstree.h"

// allocate and initialize a single node
static bstree *new_node(char *key, uint32_t value) {
    bstree *n = malloc(sizeof(bstree));
    if (n) {
        n->key = strdup(key ? key : "");
        n->value = value;
        n->left = n->right = NULL;
    }
    return n;
}

// create root
bstree *bstree_create(char *key, uint32_t value) {
    return new_node(key, value);
}

// iterative add using double pointer (handles worst-case without stack overflow)
bstree *bstree_add(bstree *tree, char *key, uint32_t value) {
    bstree **link = &tree;
    while (*link) {
        int cmp = strcmp(key, (*link)->key);
        if (cmp == 0) {
            (*link)->value = value;   // update existing key
            return tree;
        }
        link = (cmp < 0) ? &(*link)->left : &(*link)->right;
    }
    *link = new_node(key, value);
    return tree;
}

// lookup
bstree *bstree_lookup(bstree *tree, char *key) {
    while (tree) {
        int cmp = strcmp(key, tree->key);
        if (cmp == 0) return tree;
        tree = (cmp < 0) ? tree->left : tree->right;
    }
    return NULL;
}

// min
bstree *bstree_min(bstree *tree) {
    if (!tree) return NULL;
    while (tree->left) tree = tree->left;
    return tree;
}

// max
bstree *bstree_max(bstree *tree) {
    if (!tree) return NULL;
    while (tree->right) tree = tree->right;
    return tree;
}

// delete (not used in experiments, kept for completeness)
bstree *bstree_delete(bstree *tree, char *key) {
    if (!tree) return NULL;
    int cmp = strcmp(key, tree->key);
    if (cmp < 0) tree->left = bstree_delete(tree->left, key);
    else if (cmp > 0) tree->right = bstree_delete(tree->right, key);
    else {
        if (!tree->left) { bstree *r = tree->right; free(tree->key); free(tree); return r; }
        if (!tree->right) { bstree *l = tree->left; free(tree->key); free(tree); return l; }
        bstree *min = tree->right;
        while (min->left) min = min->left;
        free(tree->key);
        tree->key = strdup(min->key);
        tree->value = min->value;
        tree->right = bstree_delete(tree->right, min->key);
    }
    return tree;
}
