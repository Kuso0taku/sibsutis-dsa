#include <stddef.h> // size_t
#include <inttypes.h> // uint32_t

// heap sort
void counting_sort(uint32_t*, size_t, uint32_t*, uint8_t);
void radix_sort(uint32_t*, size_t);

// merge sort
void merge(uint32_t*, size_t, size_t, size_t, uint32_t*);
void merge_sort(uint32_t*, size_t);

// heap sort
void heapify(uint32_t*, size_t, size_t);
void build_heap(uint32_t*, size_t);
void heap_sort(uint32_t*, size_t);

// selection sort
void selection_sort(uint32_t*, size_t);
