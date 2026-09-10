# Min-heap

## Functions:
```
struct minheap *minheap_insert(struct minheap *heap,
int key, char *value);

void *build_minheap(int *arr, int n)
struct minheap *minheap_min(struct minheap *heap);
struct minheap *minheap_union(struct minheap *heap1,
struct minheap *heap2);
struct minheap *minheap_extractmin(struct minheap *heap);
struct minheap *minheap_decrease_key(struct minheap *heap,
int key, int newkey);
struct minheap *minheap_delete(struct minheap *heap, int key);
```

## Experimental research
- key is `int`
- generate numbers [10'000, 1'000'000]
- while fil [table 1](##table-1) it's necessary to change overall add data time.  
- for [table 2](##table-2): all elements is added to min-heap.  
- while fil [table 2](##table-2) it's necessary to `extractmin` after element have been added it's necessary to `decreasekey`.  

## Table 1 
```
#,n,minheap_insert,build_minheap
1,50000,...,...
2,100000,...,...
...,...,...,...
8,400000,...,...
```

## Table 2 
```
#,n,minheap_extractmin,build_decreasekey
1,50000,...,...
2,100000,...,...
...,...,...,...
8,400000,...,...
```

## Rewiew questions
- What is a priority queue?
- Priority queue implementation options.
- Explanation of how binary heap functions work.
- Computational complexity of binary heap operations.
- Merge two heaps.
- How to add elements to a binary heap?
- Applications of a binary heap.
