#include <stdio.h>
#include <stdlib.h>
#include "data_list.h"

void data_add_front(struct list_head *head, int key, double value) {
    struct data *new_data = malloc(sizeof(struct data));
    if (!new_data) {
        fputs("Memory allocation error!\n", stderr);
        return;
    }
    new_data->key = key;
    new_data->value = value;
    list_add(&new_data->list, head);
}

void data_add_tail(struct list_head *head, int key, double value) {
    struct data *new_data = malloc(sizeof(struct data));
    if (!new_data) {
        fputs("Memory allocation error!\n", stderr);
        return;
    }
    new_data->key = key;
    new_data->value = value;
    list_add_tail(&new_data->list, head);
}

double data_lookup(struct list_head *head, int key) {
    struct list_head *pos;
    list_for_each(pos, head) {
        struct data *entry = container_of(pos, struct data, list);
        if (entry->key == key)
            return entry->value;
    }
    return -1.0;
}

int data_delete(struct list_head *head, int key) {
    struct list_head *pos, *tmp;
    list_for_each_safe(pos, tmp, head) {
        struct data *entry = container_of(pos, struct data, list);
        if (entry->key == key) {
            list_del(pos);
            free(entry);
            return 1;
        }
    }
    return 0;
}

void list_clear(struct list_head *head) {
    struct list_head *pos, *tmp;
    list_for_each_safe(pos, tmp, head) {
        struct data *entry = container_of(pos, struct data, list);
        list_del(pos);
        free(entry);
    }
}
