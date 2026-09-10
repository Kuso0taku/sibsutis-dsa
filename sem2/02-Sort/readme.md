# Sort.  

## Task 
Make algorithms:
- Radix Sort - O(n*k)
- Merge Sort - O(n log n)
- Heap Sort - O(n log n) - extra one
- Selection Sort - O(n^2)
  
## Experementa Research
- Measure the running time of each algorithm with different numbers of an array elements - fill the Table 2 for each algorithm, plot a graph based on the table.
- If one of the algorithms takes longer than the others, use a log scale when plotting a graph, or plot a seperate graph w/o result of this sorting.
- Based on the results, determind which algorithm takes faster and why.
- In experements use `uint32_t` arrays (enable `inttypes.h`).
- Fill arrays with random number from **0 to 100000**.
- Memory allocates using `malloc`: `int* arr = (int*)malloc(sizeof(int) * n)`

## Table 2. Experents results.
```
#   array_len   alg1, s   alg2, s     alg3, s     alg4, s 
1     50000
2     100000
3     150000
..     ...
20     1000000
```

## Review questions
- What do the notations f(n) = O(g(n)), f(n) = Θ(g(n)), f(n) = Ω(g(n)) mean?
- Computational complexity of implemented sorting algorithms in average and worst cases, reasons for the worst case or its absence.
- Spatial complexity (“memory complexity”) of the implemented sorting algorithms.
- What is “stable” sorting?
- What is “in-place sorting”?
- Properties of sorting by variant.
- Determining the computational complexity of sorting by source code.
- Sorting algorithms with computational complexity (n log n) for the worst case.
- Sorting algorithms that run faster than (n log n) for the worst case.
- Explanation of the behavior of curves on graphs.
