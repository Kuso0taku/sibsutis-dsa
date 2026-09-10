#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bstree.h"
#include "hashtab.h"
#include <utils.h>   // provides wtime()

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

#define N_WORDS  400000      // total number of words
#define STEP     20000       // measurement step
#define POINTS   (N_WORDS / STEP)   // 20 points (not used as array size now)
#define ITERS    1000        // iterations for time averaging

// average BST lookup time (seconds)
static double measure_bst_lookup(bstree *tree, char *key) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (bstree_lookup(tree, key) != NULL);
    return (wtime() - start) / ITERS;
}

// average hash table lookup time (seconds)
static double measure_ht_lookup(listnode **ht, char *key) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (hashtab_lookup(ht, key) != NULL);
    return (wtime() - start) / ITERS;
}

// average BST max search time (seconds)
static double measure_bst_max(bstree *tree) {
    volatile int found = 0;
    double start = wtime();
    for (int i = 0; i < ITERS; i++) found += (bstree_max(tree) != NULL);
    return (wtime() - start) / ITERS;
}

// Experiment 1: lookup in average case (BST vs hash table)
static void run_exp1(char **random_words) {
    bstree *bst = bstree_create(*random_words, 0);
    listnode **ht = malloc(HASHTAB_SIZE * sizeof(listnode *));
    hashtab_init(ht);
    hashtab_set_hash(KRHash);
    hashtab_add(ht, *random_words, 0);

    printf("Table 2. Experiment 1\n");
    printf("#,Elements,bstree_lookup(s),hashtab_lookup(s)\n");
    int point = 1;
    for (int i = 1; i < N_WORDS; i++) {
        bst = bstree_add(bst, *(random_words + i), i);
        hashtab_add(ht, *(random_words + i), i);
        if ((i + 1) % STEP == 0) {
            double t_bst = measure_bst_lookup(bst, *(random_words + i));
            double t_ht = measure_ht_lookup(ht, *random_words);
            printf("%d,%d,%.9f,%.9f\n", point, i+1, t_bst, t_ht);
            point++;
        }
    }
    printf("\n");
    free(ht);
}

// Experiment 5: BST max in worst/average case (parallel build + measure)
static void run_exp5(char **random_words, char **sorted_words) {
    bstree *bst_worst = bstree_create(*sorted_words, 0);
    bstree *bst_avg = bstree_create(*random_words, 0);

    printf("Table 6. Experiment 5\n");
    printf("#,Elements,bstree_max_worst(s),bstree_max_avg(s)\n");
    int point = 1;
    for (int i = 1; i < N_WORDS; i++) {
        bst_worst = bstree_add(bst_worst, *(sorted_words + i), i);
        bst_avg = bstree_add(bst_avg, *(random_words + i), i);
        if ((i + 1) % STEP == 0) {
            double t_worst = measure_bst_max(bst_worst);
            double t_avg = measure_bst_max(bst_avg);
            printf("%d,%d,%.9f,%.9f\n", point, i+1, t_worst, t_avg);
            point++;
        }
    }
    printf("\n");
}

// Experiment 6: compare KRHash vs JenkinsHash
static void run_exp6(char **random_words) {
    listnode **ht_kr = malloc(HASHTAB_SIZE * sizeof(listnode *));
    hashtab_init(ht_kr);
    hashtab_set_hash(KRHash);
    listnode **ht_jen = malloc(HASHTAB_SIZE * sizeof(listnode *));
    hashtab_init(ht_jen);
    hashtab_set_hash(JenkinsHash);

    hashtab_add(ht_kr, *random_words, 0);
    hashtab_add(ht_jen, *random_words, 0);
    int collisions_kr = 0, collisions_jen = 0;

    printf("Table 7. Experiment 6\n");
    printf("#,Elements,KR_lookup(s),KR_collisions,Jenkins_lookup(s),Jenkins_collisions\n");
    int point = 1;
    for (int i = 1; i < N_WORDS; i++) {
        char *word = *(random_words + i);
        // count collision if bucket not empty before adding
        if (*(ht_kr + (KRHash(word) % HASHTAB_SIZE))) collisions_kr++;
        hashtab_add(ht_kr, word, (uint32_t)i);
        if (*(ht_jen + (JenkinsHash(word) % HASHTAB_SIZE))) collisions_jen++;
        hashtab_add(ht_jen, word, (uint32_t)i);

        if ((i + 1) % STEP == 0) {
            double t_kr = measure_ht_lookup(ht_kr, word);
            double t_jen = measure_ht_lookup(ht_jen, word);
            printf("%d,%d,%.9f,%d,%.9f,%d\n", point, i+1, t_kr, collisions_kr, t_jen, collisions_jen);
            point++;
        }
    }
    printf("\n");
    free(ht_kr);
    free(ht_jen);
}

int main(void) {
    char **random_words = malloc(N_WORDS * sizeof(char *));
    char **sorted_words = malloc(N_WORDS * sizeof(char *));
    generate_random_words(random_words, N_WORDS);
    generate_sorted_words(sorted_words, N_WORDS);

    run_exp1(random_words);
    run_exp5(random_words, sorted_words);
    run_exp6(random_words);

    for (int i = 0; i < N_WORDS; i++) { free(*(random_words + i)); free(*(sorted_words + i)); }
    free(random_words);
    free(sorted_words);
    return 0;
}
