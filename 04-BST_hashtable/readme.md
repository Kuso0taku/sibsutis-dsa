# Binary Search trees. Hashtables.  

- Two libs to work with BST and hashtable. 
- `key = char[] string`, `value = uint32_t`. 
- Hashtable size = **20000**. 
- Random word length (6 to 30 chars).  

## Functions

BST functions in `bstree.{h,c}`:
- `struct bstree *bstree_create(char* key, int value)`
- `void bstree_add(struct bstree *tree, char *key, int value)`
- `struct bstree *bstree_lookup(struct bstree *tree, char *key)`
- `struct bstree *bstree_delete(struct bstree *tree, char *key)`
- `struct bstree *bstree_min(struct bstree *tree)`
- `struct bstree *bstree_max(struct bstree *tree)`

Hashtable functions in `hashtab.{h,c}`:
- `unsigned int hashtab_hash(char *key)`
- `void hashtab_init(struct listnode **hashtab)`
- `void hashtab_add(struct listnode **hashtab, char *key, int value)`
- `struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)`
- `void hashtab_delete(struct listnode **hashtab, char *key)`
  
## The purpose
- Experimental research of BST and hashtables efficiency.  
- Result - functions.  
- Graphs.  

## Variant №4 (mine)
- [Experiment 1](##experiment-1-lookup-efficiency-comparing-avg-case).
- [Experiment 5](##experiment-5-lookup-efficiency-best-avg-and-worst-cases).
- [Experiment 6](##experiment-6-hash-functions) - Hash-functions KP, Jenkins.

## Experiment 1. Lookup efficiency comparing (avg case).  
- Fill [Table 2](##table-2)  
- Plot graphs `t = lookup(n)`

## Table 2  
```
#,n,bstree_lookup(s),hashtab_lookup(s)
1,20000,_,_
2,40000,_,_
...,...,_,_
20,400000,_,_
```

## Experiment 5. Lookup efficiency best, avg and worst cases.  
- Fill [Table 6](##table-6)
- Plot graphs `t = lookup()` best, avg and worst cases.  

## Table 6  
```
#,n,bstree_max(s)-worst,bstree_max(s)-avg
1,20000,_,_
2,40000,_,_
...,...,_,_
20,400000,_,_
```

## Experiment 6. Hash functions.  
- Fill [Table 7](##table-7)  
- Plot graphs `t = lookup(n)` for X and Y functions, where X = KP, Y = Jenkins.  
- Graphs `q = f(n)`

## Table 7  
```
#,n,hashtab_lookup(s)-KP,collisions-KP,hashtab_lookup(s)-Jenkins,collisions-Jenkins
1,20000,_,_
2,40000,_,_
...,...,_,_
20,400000,_,_
```

## Rewiew questions
- What is a dictionary, an associative array?
- What is a binary search tree? Carry out an analysis of the complexity of
operations.
- What is a hash table? Conduct an analysis of the complexity of the basic operations.
- What is a hash function? Which hash function is “good”?
- Methods for resolving collisions in hash tables.
