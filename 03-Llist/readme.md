# Double-linked list 

Make a double-linked list.  
All the functions for it must be in `list.h` and `list.c`   
  
Realize a program-user interaction:  
- output avaliable operations
- operation choose
- input while adding/searching/deleting
- possibility input several elements for operations w/o choosing the operation again
- add all elements from a file
- output search result
- output all elements of a double-linked list 
- clear a double-linked list
- terminate the program
- experemental research, table 1 
Realize errors handler with a message ouput for a user or with logs ouput.  

## Variant 2. Cycle double-linked list as it made in the Linux core (Kernel)
```
struct list_head {
    struct list_head *next;
    struct list_head *prev;
};

struct data {
    int key;
    double value;
    struct list_head list;
};

// Get a current structure address with a field `member`
#define container_of(ptr, type, member) ({ 
void *__mptr = (void *)(ptr); 
((type *)(__mptr - offsetof(type, member))); })

#define LIST_HEAD(name)...
#define LIST_HEAD_INIT(name)...
#define list_for_each(pos, head)...

// Add an element to the beggining of a list, O(1)
void data_add_front(struct list_head *head, int key, double
value);

// Add an element to the end of a list, O(1)
void data_add_tail(struct list_head* head, int key, double value);

// Delete an element from a list by a key
void data_delete(struct list_head *head, int key);

// Search an element in a list by a key
double data_lookup(struct list_head *head, int key);
```

## Experemental research  
- use the `int` as a key  
- generate a data using the **generator of pseudo-random numbers**
- fill the table 1 with results
  
### Table 1. Results of experements  
```
#----------N----------list_add_tail, ms----------list_lookup, ms 
1--------50000-------------...------------------------...-------
2-------100000-------------...------------------------...-------
3-------150000-------------...------------------------...-------
4-------200000-------------...------------------------...-------
...-------...--------------...------------------------...-------
10------500000-------------...------------------------...-------
```

## Review questions
- What is a dictionary or an associative array?
- What is a “linked list”?
- What are the different implementations of linked lists?
- Explain how linked list functions work and their
computational complexity.
- Print all elements of a list `list_for_each` containing 10 random
elements. Demonstrate the operation of all functions.
- Show that all functions work correctly when removing
an element that does not exist in the data structure and in other similar cases.
- Areas of application for linked lists.
- In which data structures are linked lists used?
- How is a doubly linked list implemented in the Linux kernel?
- What macros exist for iterating over a linked list from the Linux kernel,
and how do they differ?
