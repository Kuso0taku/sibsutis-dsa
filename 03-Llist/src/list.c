#include <list.h>

// init list head with nothing
void INIT_LIST_HEAD(struct list_head* list) {
  list->next = list;
  list->prev = list;
}

// add to the beggining of the list
void list_add(struct list_head* new, struct list_head* head) {
  struct list_head* next = head->next;
  next->prev = new;
  new->next = next;
  new->prev = prev;
  head->next = new;
}

// add to the end of the list 
void list_add_tail(struct list_head* new, struct list_head* head) {
  struct list_head* prev = head->prev;
  prev->next = new;
  new->prev = prev;
  new->next = next;
  head->prev = new;
}

// remove the link to the entry
void list_del(struct list_head *entry) {
  struct list_head* prev = entry->prev;
  struct list_head* next = entry->next;
  prev->next = next;
  prev->prev = prev;
}
