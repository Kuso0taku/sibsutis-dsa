# Search.

## Task 
Make algorithms:
- linear search
- binary search  
- exponential (galloping) search  
Use `int` number.  
Check RAM requirment (example):  
```
<number of data> * <data type>
Array:
    max nubmer of elements 5000000
    data type int 
Merge sort:
    needs n memory
Max number of search elements:
    1000
    data type int 
Sum:
    5000000 * 4 * 2 + 1000 * 4 =  
    40004000 byte = 39 MB
```

## Experemntal research
- Memory allocates with `malloc`:  
`int* arr = (int*)malloc(sizeof(int) * n);`  
- fill in array with pseudorandom uniformly distributed numbers between `[0, 10'000'000]`  
- It's necessary to measure work time of every algorithm with different number of array elements - fill in table 1 for each algorithm, make a graph based on the table 1.  
- Before **binary** and **exponential** search, an array must be *sorted* using **merge sort**. To fill in table 1, don't take the sorting time into account.  
- Based on the results, determine which algorithm works faster and why (table 1).  
- To fill in table 2, measure the sum of the search time for the specified number of random elements for different number of array elements. Sorting is performed once.  
- Determine the approximate threshold for the "playback" of overhead costs for sorting when performing a binary search.  

## Table 1. Time to search for an element in an array  
```
#  ---Array elements---Linear search, μs---Binary search, μs---Exponential search, μs
1   ---    250 000 
2   ---    500 000
3   ---    750 000 
... ---      ...
20  ---   5 000 000

```

## Table2. Research results 
```
#  ---Array elements---Search elements---Linear search, μs---Binary search, μs---Binary search with sort, μs---Sort, μs
1   ---  1 000 000 --- 50
2   ---  1 000 000 --- 100
... ---      ...   --- ...
10  ---  1 000 000 --- 500
11  ---  1 000 000 --- 100
12  ---  1 000 000 --- 200
... ---      ...   --- ...
20  ---  5 000 000 --- 1000

```

## Review questions
- What is computational complexity?
- Main classes of computational complexity.
- How search algorithms work?
- Computational compexity of search algorithms.
- Demonstrate how search algorithms work.
- Determine the computational complexity of search algorithms based on the source code.
- At what number of elements do the overhead costs of sorting the array "pay off" for the binary search algorithm?
