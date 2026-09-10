// libs

#include "list.h"

// struct for data
struct data {
  int key;
  double value;
  struct list_head list;
};

// functions

// add data to the beggining of the list
void data_add_front(struct list_head* head, int key, double value);

// add data to the end of the list
void data_add_tail(struct list_head* head, int key, double value);

// find an element by the key
double data_lookup(struct list_head* head, int key);

// delete an element by the key
int data_delete(struct list_head* head, int key);

// clear the list 
void list_clear(struct list_head* head);
