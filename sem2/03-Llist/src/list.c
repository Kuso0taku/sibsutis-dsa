#include "list.h"

void INIT_LIST_HEAD(struct list_head *list) {
    list->next = list;
    list->prev = list;
}

void list_add(struct list_head *new, struct list_head *head) {
    struct list_head *next = head->next;
    next->prev = new;
    new->next = next;
    new->prev = head;
    head->next = new;
}

void list_add_tail(struct list_head *new, struct list_head *head) {
    struct list_head *prev = head->prev;
    prev->next = new;
    new->prev = prev;
    new->next = head;
    head->prev = new;
}

void list_del(struct list_head *entry) {
    struct list_head *prev = entry->prev;
    struct list_head *next = entry->next;
    prev->next = next;
    next->prev = prev;   
}
