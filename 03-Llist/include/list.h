// libs

#include <stddef.h>

// structures

// list node
struct list_head {
  struct list_head *next, *prev;
};

// macroses

// init list head (empty list)
#define LIST_HEAD_INIT(name) {&(name), &(name)}
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

// get a pointer on a structure with the list_head 
#define container_of(ptr, type, member) \
  ((type *)((void *)(ptr) - offsetof(type, member)))

// for each element in list_head 
#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head); pos = pos->next)

// safe clear list
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
         pos = n, n = pos->next)

// functions

// init list head with nothing
void INIT_LIST_HEAD(struct list_head* list);

// add to the beggining of the list
void list_add(struct list_head* new, struct list_head* head);

// add to the end of the list 
void list_add_tail(struct list_head* new, struct list_head* head);

// remove the link to the entry
void list_del(struct list_head *entry);
