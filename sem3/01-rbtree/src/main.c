#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bstree.h"
#include "rbtree.h"
#include <utils.h>

// generate n random lowercase words (length 6..30)
static void generate_random_words(char **words, int n) {
    srand(42);
    for (int i = 0; i < n; i++) {
        int len = 6 + rand() % 25;
        char *w = malloc(len + 1);
        for (int j = 0; j < len; j++) *(w + j) = 'a' + rand() % 26;
        *(w + len) = '\0';
        *(words + i) = w;
    }
}

// generate n strictly increasing words for worst-case BST
static void generate_sorted_words(char **words, int n) {
    for (int i = 0; i < n; i++) {
        char *w = malloc(12);
        sprintf(w, "w%09d", i);
        *(words + i) = w;
    }
}

// generate n random int keys for rbtree average case
static void generate_random_ints(int *keys, int n) {
    srand(42);
    for (int i = 0; i < n; i++) *(keys + i) = rand();
}

// generate n strictly increasing int keys for worst case (rbtree still balances)
static void generate_sorted_ints(int *keys, int n) {
    for (int i = 0; i < n; i++) *(keys + i) = i;
}

#define N       100000      // total number of elements
#define STEP    10000       // measurement step
#define ITERS   100         // iterations for time averaging

// average BST lookup time (seconds)
static double measure_bst_lookup(bstree *tree, char *key) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (bstree_lookup(tree, key) != NULL);
    return (wtime() - start) / ITERS;
}

// average rbtree lookup time (seconds)
static double measure_rbtree_lookup(rbtree *tree, int key) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (rbtree_lookup(tree, key) != NULL);
    return (wtime() - start) / ITERS;
}

// average BST max search time (seconds)
static double measure_bst_max(bstree *tree) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (bstree_max(tree) != NULL);
    return (wtime() - start) / ITERS;
}

// average rbtree max search time (seconds)
static double measure_rbtree_max(rbtree *tree) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (rbtree_max(tree) != NULL);
    return (wtime() - start) / ITERS;
}

// Experiment 1: lookup avg/worst case (BST vs rbtree), Table 1
static void run_exp1(char **random_words, char **sorted_words, int *random_ints, int *sorted_ints) {
    bstree *bst_avg = bstree_create(*random_words, 0);
    bstree *bst_worst = bstree_create(*sorted_words, 0);
    rbtree *rb_avg = rbtree_create(*random_ints, "");
    rbtree *rb_worst = rbtree_create(*sorted_ints, "");

    printf("Table 1. Experiment 1\n");
    printf("#,n,bstree_lookup_avg,rbtree_lookup_avg,bstree_lookup_worst,rbtree_lookup_worst\n");
    int point = 1;
    for (int i = 1; i < N; i++) {
        bst_avg = bstree_add(bst_avg, *(random_words + i), i);
        bst_worst = bstree_add(bst_worst, *(sorted_words + i), i);
        rb_avg = rbtree_add(rb_avg, *(random_ints + i), "");
        rb_worst = rbtree_add(rb_worst, *(sorted_ints + i), "");
        if ((i + 1) % STEP == 0) {
            double t_bst_avg = measure_bst_lookup(bst_avg, *(random_words + i));
            double t_rb_avg = measure_rbtree_lookup(rb_avg, *(random_ints + i));
            double t_bst_worst = measure_bst_lookup(bst_worst, *(sorted_words + i));
            double t_rb_worst = measure_rbtree_lookup(rb_worst, *(sorted_ints + i));
            printf("%d,%d,%.9f,%.9f,%.9f,%.9f\n", point, i+1, t_bst_avg, t_rb_avg, t_bst_worst, t_rb_worst);
            fflush(stdout);
            point++;
        }
    }
    printf("\n");
    rbtree_free(rb_avg);
    rbtree_free(rb_worst);
}

// Experiment 2: max avg/worst case (BST vs rbtree), Table 2
static void run_exp2(char **random_words, char **sorted_words, int *random_ints, int *sorted_ints) {
    bstree *bst_avg = bstree_create(*random_words, 0);
    bstree *bst_worst = bstree_create(*sorted_words, 0);
    rbtree *rb_avg = rbtree_create(*random_ints, "");
    rbtree *rb_worst = rbtree_create(*sorted_ints, "");

    printf("Table 2. Experiment 2\n");
    printf("#,n,bstree_max_avg,rbtree_max_avg,bstree_max_worst,rbtree_max_worst\n");
    int point = 1;
    for (int i = 1; i < N; i++) {
        bst_avg = bstree_add(bst_avg, *(random_words + i), i);
        bst_worst = bstree_add(bst_worst, *(sorted_words + i), i);
        rb_avg = rbtree_add(rb_avg, *(random_ints + i), "");
        rb_worst = rbtree_add(rb_worst, *(sorted_ints + i), "");
        if ((i + 1) % STEP == 0) {
            double t_bst_avg = measure_bst_max(bst_avg);
            double t_rb_avg = measure_rbtree_max(rb_avg);
            double t_bst_worst = measure_bst_max(bst_worst);
            double t_rb_worst = measure_rbtree_max(rb_worst);
            printf("%d,%d,%.9f,%.9f,%.9f,%.9f\n", point, i+1, t_bst_avg, t_rb_avg, t_bst_worst, t_rb_worst);
            fflush(stdout);
            point++;
        }
    }
    printf("\n");
    rbtree_free(rb_avg);
    rbtree_free(rb_worst);
}

int main(void) {
    char **random_words = malloc(N * sizeof(char *));
    char **sorted_words = malloc(N * sizeof(char *));
    int *random_ints = malloc(N * sizeof(int));
    int *sorted_ints = malloc(N * sizeof(int));

    generate_random_words(random_words, N);
    generate_sorted_words(sorted_words, N);
    generate_random_ints(random_ints, N);
    generate_sorted_ints(sorted_ints, N);

    run_exp1(random_words, sorted_words, random_ints, sorted_ints);
    run_exp2(random_words, sorted_words, random_ints, sorted_ints);

    for (int i = 0; i < N; i++) { free(*(random_words + i)); free(*(sorted_words + i)); }
    free(random_words);
    free(sorted_words);
    free(random_ints);
    free(sorted_ints);
    return 0;
}
