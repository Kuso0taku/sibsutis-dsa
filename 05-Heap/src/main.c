#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minheap.h"
#include <utils.h>   // provides wtime()

// generate n random keys in [10000, 1000000]
static void generate_keys(int *arr, int n) {
    srand(42);
    for (int i = 0; i < n; i++)
        *(arr + i) = rand() % (1000000 - 10000 + 1) + 10000;
}

#define MAX_N  400000
#define STEP    50000
#define POINTS  8       // 50000,100000,...,400000
#define REPEAT  1000    // averaging for extractmin/decrkey

// Experiment 1: insert vs build
static void run_table1(int *all_keys) {
    printf("Table 1. Insert and Build\n");
    printf("#,Elements,minheap_insert(s),build_minheap(s)\n");
    for (int i = 0; i < POINTS; i++) {
        int n = (i + 1) * STEP;
        minheap *h = minheap_create(n);
        double t1 = wtime();
        for (int j = 0; j < n; j++)
            minheap_insert(h, *(all_keys + j), NULL);
        t1 = wtime() - t1;
        minheap_free(h);

        double t2 = wtime();
        minheap *h2 = build_minheap(all_keys, n);
        t2 = wtime() - t2;
        minheap_free(h2);

        printf("%d,%d,%.9f,%.9f\n", i+1, n, t1, t2);
    }
    printf("\n");
}

// Experiment 2: extractmin and decreasekey
static void run_table2(int *all_keys) {
    printf("Table 2. ExtractMin and DecreaseKey\n");
    printf("#,Elements,minheap_extractmin(s),minheap_decreasekey(s)\n");
    for (int i = 0; i < POINTS; i++) {
        int n = (i + 1) * STEP;
        minheap *heap = build_minheap(all_keys, n);

        // --- extractmin measurement ---
        double t_extract = 0.0;
        int min_key = *(heap->keys);
        for (int r = 0; r < REPEAT; r++) {
            double start = wtime();
            minheap_extractmin(heap);
            t_extract += wtime() - start;
            minheap_insert(heap, min_key, NULL);
            min_key = *(heap->keys);  // new minimum for next iteration
        }
        t_extract /= REPEAT;

        // --- decreasekey measurement ---
        // first, do one extractmin as required by the task (size becomes n-1)
        minheap_extractmin(heap);
        // find a leaf with a large key (last element is often large, but let's find max)
        int max_idx = 0;
        for (int k = 1; k < heap->size; k++)
            if (*(heap->keys + k) > *(heap->keys + max_idx)) max_idx = k;
        int old_key = *(heap->keys + max_idx);
        int small_key = 10;   // new smaller key (less than any generated)
        double t_decrease = 0.0;
        for (int r = 0; r < REPEAT; r++) {
            double start = wtime();
            minheap_decrease_key(heap, old_key, small_key);
            double elapsed = wtime() - start;
            t_decrease += elapsed;
            // restore: increase key back to old_key (sift_down)
            int idx = -1;
            for (int m = 0; m < heap->size; m++)
                if (*(heap->keys + m) == small_key) { idx = m; break; }
            if (idx != -1) {
                *(heap->keys + idx) = old_key;
                minheap_sift_down(heap, idx);
            }
        }
        t_decrease /= REPEAT;

        printf("%d,%d,%.9f,%.9f\n", i+1, n, t_extract, t_decrease);
        minheap_free(heap);
    }
    printf("\n");
}

int main(void) {
    int *keys = (int *)malloc(MAX_N * sizeof(int));
    generate_keys(keys, MAX_N);

    run_table1(keys);
    run_table2(keys);

    free(keys);
    return 0;
}
