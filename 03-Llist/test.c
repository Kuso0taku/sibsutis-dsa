#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data_list.h"
#include "utils.h"

// Helper: count elements in list
static int count_elements(struct list_head *head) {
    struct list_head *pos;
    int count = 0;
    list_for_each(pos, head) {
        count++;
    }
    return count;
}

// Helper: get value by key
static double get_value(struct list_head *head, int key) {
    return data_lookup(head, key);
}

void test_add_front_and_tail(void) {
    struct list_head head;
    INIT_LIST_HEAD(&head);

    data_add_front(&head, 1, 10.0);
    data_add_front(&head, 2, 20.0);
    data_add_tail(&head, 3, 30.0);
    data_add_tail(&head, 4, 40.0);

    int expected_keys[] = {2, 1, 3, 4};
    double expected_values[] = {20.0, 10.0, 30.0, 40.0};
    int i = 0;
    struct list_head *pos;
    list_for_each(pos, &head) {
        struct data *entry = container_of(pos, struct data, list);
        assert(entry->key == expected_keys[i]);
        assert(entry->value == expected_values[i]);
        i++;
    }
    assert(i == 4);
    assert(count_elements(&head) == 4);

    list_clear(&head);
    printf("test_add_front_and_tail PASSED\n");
}

void test_lookup(void) {
    struct list_head head;
    INIT_LIST_HEAD(&head);

    data_add_tail(&head, 5, 55.5);
    data_add_tail(&head, 6, 66.6);

    assert(get_value(&head, 5) == 55.5);
    assert(get_value(&head, 6) == 66.6);
    assert(get_value(&head, 99) == -1.0);

    list_clear(&head);
    printf("test_lookup PASSED\n");
}

void test_delete(void) {
    struct list_head head;
    INIT_LIST_HEAD(&head);

    data_add_tail(&head, 10, 100.0);
    data_add_tail(&head, 20, 200.0);
    data_add_tail(&head, 30, 300.0);

    int ret = data_delete(&head, 20);
    assert(ret == 1);
    assert(count_elements(&head) == 2);
    assert(get_value(&head, 10) == 100.0);
    assert(get_value(&head, 30) == 300.0);
    assert(get_value(&head, 20) == -1.0);

    ret = data_delete(&head, 10);
    assert(ret == 1);
    assert(count_elements(&head) == 1);
    assert(get_value(&head, 30) == 300.0);

    ret = data_delete(&head, 30);
    assert(ret == 1);
    assert(count_elements(&head) == 0);

    ret = data_delete(&head, 100);
    assert(ret == 0);
    assert(count_elements(&head) == 0);

    list_clear(&head);
    printf("test_delete PASSED\n");
}

void test_clear(void) {
    struct list_head head;
    INIT_LIST_HEAD(&head);

    data_add_tail(&head, 1, 1.0);
    data_add_tail(&head, 2, 2.0);
    assert(count_elements(&head) == 2);
    list_clear(&head);
    assert(count_elements(&head) == 0);
    data_add_tail(&head, 3, 3.0);
    assert(count_elements(&head) == 1);
    assert(get_value(&head, 3) == 3.0);
    list_clear(&head);
    printf("test_clear PASSED\n");
}

void test_multiple_lists(void) {
    struct list_head **lists = NULL;
    size_t cnt = 0;

    struct list_head *list1 = malloc(sizeof(struct list_head));
    assert(list1 != NULL);
    INIT_LIST_HEAD(list1);
    lists = realloc(lists, (cnt+1) * sizeof(struct list_head*));
    lists[cnt++] = list1;

    struct list_head *list2 = malloc(sizeof(struct list_head));
    assert(list2 != NULL);
    INIT_LIST_HEAD(list2);
    lists = realloc(lists, (cnt+1) * sizeof(struct list_head*));
    lists[cnt++] = list2;

    data_add_tail(list1, 100, 1000.0);
    data_add_tail(list1, 200, 2000.0);
    data_add_front(list2, 300, 3000.0);
    data_add_tail(list2, 400, 4000.0);

    assert(count_elements(list1) == 2);
    assert(get_value(list1, 100) == 1000.0);
    assert(get_value(list1, 200) == 2000.0);
    assert(get_value(list1, 300) == -1.0);

    assert(count_elements(list2) == 2);
    struct list_head *pos = list2->next;
    struct data *first = container_of(pos, struct data, list);
    assert(first->key == 300);
    assert(get_value(list2, 400) == 4000.0);

    list_clear(list1);
    list_clear(list2);
    free(list1);
    free(list2);
    free(lists);
    printf("test_multiple_lists PASSED\n");
}

int main(void) {
    printf("Starting data_list tests...\n");
    test_add_front_and_tail();
    test_lookup();
    test_delete();
    test_clear();
    test_multiple_lists();
    // run_experiment is not included because it requires main's context
    printf("All tests passed!\n");
    return 0;
}
