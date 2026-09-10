#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

// sentinel leaf, always black, replaces every NULL leaf
static rbtree nil_node = { 0, NULL, 'B', NULL, NULL, NULL };
static rbtree *const NIL = &nil_node;

// allocate and initialize a single red node with sentinel children
static rbtree *new_node(int key, char *value) {
    rbtree *n = malloc(sizeof(rbtree));
    if (n) {
        n->key = key;
        n->value = strdup(value ? value : "");
        n->color = 'R';
        n->left = n->right = n->parent = NIL;
    }
    return n;
}

// create root (black)
rbtree *rbtree_create(int key, char *value) {
    rbtree *n = new_node(key, value);
    if (n) n->color = 'B';
    return n;
}

// left rotation around x, y = x->right must be a real node
static void rotate_left(rbtree **root, rbtree *x) {
    rbtree *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// right rotation around x, y = x->left must be a real node
static void rotate_right(rbtree **root, rbtree *x) {
    rbtree *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// restore red-black properties after insert
static void insert_fixup(rbtree **root, rbtree *z) {
    while (z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            rbtree *y = z->parent->parent->right;   // uncle
            if (y->color == 'R') {                  // case 1: red uncle
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {        // case 2: triangle
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = 'B';             // case 3: line
                z->parent->parent->color = 'R';
                rotate_right(root, z->parent->parent);
            }
        } else {
            rbtree *y = z->parent->parent->left;    // uncle
            if (y->color == 'R') {                  // case 1: red uncle
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {         // case 2: triangle
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = 'B';             // case 3: line
                z->parent->parent->color = 'R';
                rotate_left(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

// add node (iterative), returns root (changes after rotations)
rbtree *rbtree_add(rbtree *root, int key, char *value) {
    rbtree *y = NIL;
    rbtree *x = root ? root : NIL;
    while (x != NIL) {
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else {
            free(x->value);
            x->value = strdup(value ? value : "");
            return root;
        }
    }
    rbtree *z = new_node(key, value);
    z->parent = y;
    if (y == NIL) root = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    insert_fixup(&root, z);
    return root;
}

// find node by key, returns node or NULL
rbtree *rbtree_lookup(rbtree *root, int key) {
    while (root && root != NIL) {
        if (key < root->key) root = root->left;
        else if (key > root->key) root = root->right;
        else return root;
    }
    return NULL;
}

// return node with minimum key (leftmost)
rbtree *rbtree_min(rbtree *root) {
    if (!root || root == NIL) return NULL;
    while (root->left != NIL) root = root->left;
    return root;
}

// return node with maximum key (rightmost)
rbtree *rbtree_max(rbtree *root) {
    if (!root || root == NIL) return NULL;
    while (root->right != NIL) root = root->right;
    return root;
}

// minimum of non-empty subtree (internal)
static rbtree *tree_minimum(rbtree *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

// move subtree v into place of subtree u
static void transplant(rbtree **root, rbtree *u, rbtree *v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

// restore red-black properties after delete
static void delete_fixup(rbtree **root, rbtree *x) {
    while (x != *root && x->color == 'B') {
        if (x == x->parent->left) {
            rbtree *w = x->parent->right;           // brother
            if (w->color == 'R') {                  // case 1: red brother
                w->color = 'B';
                x->parent->color = 'R';
                rotate_left(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B') {
                w->color = 'R';                     // case 2: both black
                x = x->parent;
            } else {
                if (w->right->color == 'B') {       // case 3: right black
                    w->left->color = 'B';
                    w->color = 'R';
                    rotate_right(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;        // case 4: right red
                x->parent->color = 'B';
                w->right->color = 'B';
                rotate_left(root, x->parent);
                x = *root;
            }
        } else {
            rbtree *w = x->parent->left;            // brother
            if (w->color == 'R') {                  // case 1: red brother
                w->color = 'B';
                x->parent->color = 'R';
                rotate_right(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';                     // case 2: both black
                x = x->parent;
            } else {
                if (w->left->color == 'B') {        // case 3: left black
                    w->right->color = 'B';
                    w->color = 'R';
                    rotate_left(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;        // case 4: left red
                x->parent->color = 'B';
                w->left->color = 'B';
                rotate_right(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = 'B';
}

// delete node by key (CLRS), returns root
rbtree *rbtree_delete(rbtree *root, int key) {
    if (!root) return NULL;
    rbtree *z = root;
    while (z != NIL && z->key != key) z = (key < z->key) ? z->left : z->right;
    if (z == NIL) return root;

    rbtree *y = z;
    rbtree *x;
    char y_orig_color = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(&root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(&root, z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z->value);
    free(z);

    if (y_orig_color == 'B') delete_fixup(&root, x);
    return root;
}

// free all nodes (postorder)
void rbtree_free(rbtree *root) {
    if (!root || root == NIL) return;
    rbtree_free(root->left);
    rbtree_free(root->right);
    free(root->value);
    free(root);
}

// print tree sideways, right subtree first, level is indentation
void rbtree_print_dfs(rbtree *root, int level) {
    if (!root || root == NIL) return;
    rbtree_print_dfs(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("  ");
    printf("%d (%c)\n", root->key, root->color);
    rbtree_print_dfs(root->left, level + 1);
}