# Red-black tree.  

Information about BSTrees research avaliable here [04-BST_hashtable]().  
This research uses BSTree from that.  

## Constraints
- `type(key) == int`
- `10'000 <= N <= 1'000'000`
- for worst case add **ascending** elements into trees  
for each case and number of element:
    - use `rbtree_lookup` and `bstree_lookup` to fiil [Table 1](##table-1). search element = last added element  
    - use `rbtree_max` and `bstree_max` to fill [Table 2](##table-2)  
- after the research compute complexity of called funtions, explain results.  

## Functions

BST functions in `bstree.{h,c}`:
- `struct rbtree *rbtree_add(struct rbtree *root, int key, char *value);`
- `struct rbtree *rbtree_lookup(struct rbtree *root, int key);`
- `struct rbtree *rbtree_delete(struct rbtree *root, int key);`
- `struct rbtree *rbtree_min(struct rbtree *root);`
- `struct rbtree *rbtree_max(struct rbtree *root);`
- `void rbtree_free(struct rbtree *root);`
- `void rbtree_print_dfs(struct rbtree *root, int level);`

## Table 1  
```
#,n,bstree_lookup_avg,rbtree_lookup_avg,bstree_lookup_worst,rbtree_lookup_worst
1,20'000,_,_,_,_
2,40'000,_,_,_,_
...,...,...,...,...,...
10,200'000,_,_,_,_
```

## Table 6  
```
#,n,bstree_max_avg,rbtree_max_avg,bstree_max_worst,bstree_max_worst
1,20'000,_,_,_,_
2,40'000,_,_,_,_
...,...,...,...,...,...
10,200'000,_,_,_,_
```

## Rewiew questions
- What is a balanced search tree? Which balanced search trees are you familiar with?
- Red-black tree node structure.
- Explain the operating principle of a red-black tree.
- Computational complexity of red-black tree operations.
- Explain and demonstrate the algorithm for inserting nodes into a red-black tree.
- Explain and demonstrate the algorithm for deleting nodes from a red-black tree.
- Compare the computational complexity of red-black tree operations with those of a binary search tree; explain the result.
- Prove the statement regarding the height of a red-black tree.
- Analysis of the computational complexity of red-black tree and binary search tree operations.
